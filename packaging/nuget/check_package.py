#!/usr/bin/env python3
"""Assert on the produced .nupkg, and lint the README it carries.

    python packaging/nuget/check_package.py <path to .nupkg> [--version 26.9.0]

It exits non-zero and prints every failure. It reads nothing from the build that
produced the package -- the point is to examine the file that would be uploaded,
not to ask the build whether it did the right thing.

THE ASSERTION THIS FILE EXISTS FOR is the location of the .targets. NuGet imports
`build/native/<PackageId>.targets` and nothing else. The sibling
Aspose.Cells.Cpp.FOSS package ships its targets at
`build/native/Aspose.Cells.Cpp.FOSS/aspose.cells.cpp.foss.targets` -- one
directory too deep and lower-cased -- so that file is carried in the package and
never read: installing it gives the consumer no include path and no library, and
the failure appears in their code as a missing header. Nothing about the package
looks wrong. It packs, it pushes, it installs, and it does nothing.

Every other assertion here is one that would otherwise be silent: a platform whose
libraries were not built, a configuration directory carrying two of the three
archives, a header tree missing pugixml's headers even though pugixml is in our
public interface, a readme whose images nuget.org drops without telling anyone but
the owner.
"""
import argparse
import posixpath
import re
import sys
import xml.etree.ElementTree as ET
import zipfile

PACKAGE_ID = "Aspose.Slides.Cpp.FOSS"

# The nuspec XML namespace is NOT fixed. It has had at least four values --
# .../packaging/2010/07/, /2011/08/, /2012/06/ and /2013/05/nuspec.xsd -- and
# which one comes out depends on the schema the manifest declared and on the
# tool that packed it. Hardcoding one is a silent failure and not a loud one:
# every find() returns None, so a perfectly good package reads as having no
# metadata at all, and a broken one is never reached to be reported. Measured
# rather than reasoned about: the sibling Aspose.Cells.Cpp.FOSS package on
# nuget.org declares 2011/08, and against a hardcoded 2013/05 this checker
# reported "no <metadata>" and exited before testing anything.
#
# So it is read from the manifest that is actually in the package.
NS = ""

PLATFORM_DIRS = ["win_x86_64", "win_x86"]
CONFIGS = ["Release", "Debug"]
LIBS = ["aspose_slides_foss.lib", "pugixml.lib", "miniz.lib"]

# Headers that must be present because a consumer's first #include reaches them.
# pugixml's two are not ours and are the ones most likely to be dropped by
# mistake, because nothing in this repository includes them by that path.
REQUIRED_HEADERS = [
    "build/native/include/pugixml.hpp",
    "build/native/include/pugiconfig.hpp",
    "build/native/include/Aspose/Slides/Foss/presentation.h",
    "build/native/include/Aspose/Slides/Foss/version.h",
]

# nuget.org renders an image only if its host is on this list; everything else is
# dropped with a warning only the package owner ever sees. products.aspose.org is
# deliberately absent -- it is not on nuget.org's list, which is why the banner is
# mirrored into this repository and served from raw.githubusercontent.com.
IMAGE_HOSTS = {
    "api.codacy.com", "api.codeclimate.com", "api.dependabot.com", "api.reuse.software",
    "api.travis-ci.com", "app.codacy.com", "app.deepsource.com", "avatars.githubusercontent.com",
    "badgen.net", "badges.gitter.im", "camo.githubusercontent.com", "caniuse.bitsofco.de",
    "cdn.jsdelivr.net", "cdn.syncfusion.com", "ci.appveyor.com", "circleci.com", "cloudback.it",
    "codecov.io", "codefactor.io", "coveralls.io", "dev.azure.com", "devpod.sh", "flat.badgen.net",
    "github.com", "gitlab.com", "i.imgur.com", "img.shields.io", "infragistics.com",
    "isitmaintained.com", "media.githubusercontent.com", "opencollective.com", "raw.github.com",
    "raw.githubusercontent.com", "snyk.io", "sonarcloud.io", "travis-ci.com", "travis-ci.org",
    "user-images.githubusercontent.com",
}


def lint_readme(text, problems):
    if "```mermaid" in text:
        problems.append("readme: a ```mermaid fence. nuget.org parses CommonMark through Markdig, "
                        "which has no Mermaid, so the diagram renders as a wall of code.")

    for _alt, target in re.findall(r"!\[([^\]]*)\]\(([^)\s]+)", text):
        if not target.startswith("http"):
            problems.append("readme: image %r has a relative path; nuget.org does not resolve "
                            "relative images." % target)
            continue
        host = target.split("/")[2].lower()
        if host not in IMAGE_HOSTS:
            problems.append("readme: image host %r is not on the nuget.org allow-list, so %r will "
                            "not render." % (host, target))

    for label, target in re.findall(r"(?<!!)\[([^\]]*)\]\(([^)\s]+)", text):
        if not target.startswith("http"):
            problems.append("readme: link %r -> %r is relative. The package is not a repository; "
                            "relative links resolve to nothing on the package page."
                            % (label, target))

    installs = re.findall(r"Install-Package\s+(\S+)", text)
    if not installs:
        problems.append("readme: no `Install-Package` line. The page has to say how to install the "
                        "thing it is the page for, and for a native package that is not "
                        "`dotnet add package`.")
    for got in installs:
        if got != PACKAGE_ID:
            problems.append("readme: install command says %r, the package id is %r. One of the two "
                            "is wrong and the reader will copy the wrong one." % (got, PACKAGE_ID))


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("package")
    ap.add_argument("--version", default=None,
                    help="the version this package is expected to be, cross-checked against the manifest")
    args = ap.parse_args(argv[1:])

    problems = []
    with zipfile.ZipFile(args.package) as z:
        names = z.namelist()
        flat = set(n.replace("\\", "/") for n in names)

        specs = [n for n in names if n.endswith(".nuspec")]
        if len(specs) != 1:
            sys.stderr.write("expected exactly one .nuspec, found %d\n" % len(specs))
            return 2
        global NS
        root = ET.fromstring(z.read(specs[0]))
        NS = root.tag[:root.tag.index("}") + 1] if root.tag.startswith("{") else ""
        meta = root.find(NS + "metadata")
        if meta is None:
            sys.stderr.write("the .nuspec has no <metadata> (namespace read as %r)\n" % NS)
            return 2

        def field(tag):
            el = meta.find(NS + tag)
            return None if el is None else (el.text or "")

        package_id = field("id")
        version = field("version")

        if package_id != PACKAGE_ID:
            problems.append("nuspec: <id> is %r, expected %r. The casing is what nuget.org displays "
                            "for ever." % (package_id, PACKAGE_ID))
        if specs[0] != PACKAGE_ID + ".nuspec":
            problems.append("nuspec: the manifest file is %r; it must be %r"
                            % (specs[0], PACKAGE_ID + ".nuspec"))
        if args.version and version != args.version:
            problems.append("nuspec: <version> is %r but this release is for %r"
                            % (version, args.version))
        if version and not re.match(r"^[0-9]+\.[0-9]+\.[0-9]+$", version):
            problems.append("nuspec: <version> %r is not a plain three-part release version" % version)

        for tag in ("title", "authors", "description", "projectUrl", "icon", "readme",
                    "copyright", "tags", "releaseNotes"):
            if not field(tag):
                problems.append("nuspec: <%s> is missing or empty" % tag)

        # The manifest is generated from a template, and every field check above passes just as
        # happily on `@VERSION@` as on a version: they test for emptiness, not for meaning. A
        # placeholder that survived substitution would be published verbatim and is immutable
        # afterwards, so it is worth its own assertion.
        raw_spec = z.read(specs[0]).decode("utf-8-sig", "replace")
        leftovers = sorted(set(re.findall(r"@[A-Z][A-Z0-9_]*@", raw_spec)))
        if leftovers:
            problems.append("nuspec: unsubstituted template placeholders %r -- pack.py did not "
                            "replace them, and package metadata cannot be edited after upload"
                            % leftovers)

        lic = meta.find(NS + "license")
        if lic is None or lic.get("type") != "expression" or (lic.text or "") != "MIT":
            problems.append("nuspec: <license> must be the MIT expression")
        if (field("requireLicenseAcceptance") or "false").lower() != "false":
            problems.append("nuspec: requireLicenseAcceptance must be false for an MIT package")
        if meta.find(NS + "dependencies") is not None:
            problems.append("nuspec: a native package must declare no <dependencies>; pugixml and "
                            "miniz are carried inside it, not resolved by NuGet")

        # The assertion this file exists for.
        targets = "build/native/%s.targets" % PACKAGE_ID
        if targets not in flat:
            deeper = [n for n in flat if n.lower().endswith(".targets")]
            problems.append("package: %s is missing -- NuGet imports that exact path and nothing "
                            "else, so the package would install and do nothing. Found instead: %r"
                            % (targets, deeper))
        else:
            body = z.read(targets).decode("utf-8", "replace")
            for needed in ("AdditionalIncludeDirectories", "AdditionalDependencies"):
                if needed not in body:
                    problems.append("targets: no <%s>, so the package sets no %s"
                                    % (needed, "include path" if "Include" in needed else "link input"))

        for platform_dir in PLATFORM_DIRS:
            for config in CONFIGS:
                for lib in LIBS:
                    entry = "build/native/lib/%s/%s/%s" % (platform_dir, config, lib)
                    if entry not in flat:
                        problems.append("package: %s is missing" % entry)
                    elif z.getinfo(entry).file_size == 0:
                        problems.append("package: %s is empty" % entry)

        for header in REQUIRED_HEADERS:
            if header not in flat:
                problems.append("package: %s is missing. pugixml is in this library's public "
                                "interface, so its headers are part of the package." % header)

        for required in (field("icon"), field("readme"), "LICENSE", "THIRD_PARTY_NOTICES"):
            if required and required.replace("\\", "/") not in flat:
                problems.append("package: %r is named in the manifest or required, but is not in "
                                "the package" % required)

        strays = [n for n in flat if posixpath.splitext(n)[1].lower()
                  in (".obj", ".pdb", ".exe", ".ilk", ".exp", ".tlog")]
        if strays:
            problems.append("package: build leftovers are in the package: %r" % strays[:10])

        readme_name = (field("readme") or "").replace("\\", "/")
        if readme_name and readme_name in flat:
            lint_readme(z.read(readme_name).decode("utf-8"), problems)

        # The version the headers declare must be the version the manifest sells.
        vh = "build/native/include/Aspose/Slides/Foss/version.h"
        if version and vh in flat:
            text = z.read(vh).decode("utf-8", "replace")
            m = re.search(r'ASPOSE_SLIDES_FOSS_VERSION_STRING\s+"([^"]+)"', text)
            if not m:
                problems.append("package: %s declares no ASPOSE_SLIDES_FOSS_VERSION_STRING" % vh)
            elif m.group(1) != version:
                problems.append("package: the manifest says %r and the shipped version.h says %r"
                                % (version, m.group(1)))

        libs = sorted(n for n in flat if n.endswith(".lib"))
        print("%s %s" % (package_id, version))
        print("  entries      : %d" % len(names))
        print("  libraries    : %d across %d platform/config pairs"
              % (len(libs), len(PLATFORM_DIRS) * len(CONFIGS)))
        print("  headers      : %d" % sum(1 for n in flat if n.endswith((".h", ".hpp"))))
        print("  targets at   : %s" % (targets if targets in flat else "MISSING"))

    for problem in problems:
        print("FAIL " + problem)
    print("%d assertion(s) failed" % len(problems))
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
