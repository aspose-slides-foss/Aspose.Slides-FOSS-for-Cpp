#!/usr/bin/env python3
"""Build the four MSVC configurations and pack them into one NuGet package.

    python packaging/nuget/pack.py --work build/nuget-pack

The package carries x64 and Win32, Debug and Release. That is four builds, and it
is why this is a script rather than a workflow step: the same command has to run
on a developer's machine and in CI, or the thing CI publishes is not the thing
anyone has ever tested.

WHAT IS DELIBERATE HERE

  * The version comes from project(... VERSION ...) in CMakeLists.txt and from
    nowhere else. The .nuspec is a template with @VERSION@ in it.

  * CMAKE_MSVC_RUNTIME_LIBRARY is passed explicitly. /MD and /MDd are already
    CMake's default, so this changes nothing today -- it makes the C runtime a
    decision that is written down rather than a default that could move under us
    and produce a package that fails to link for every consumer at once.

  * FETCH_DEPENDENCIES is ON, unlike the vcpkg and Conan recipes, which turn it
    OFF. Those hand the build a dependency their own package manager resolved.
    NuGet has no such mechanism for native C++ dependencies, so this package has
    to carry pugixml and miniz itself -- pugixml's headers included, because they
    are in our public interface.

  * The headers are staged from one platform's install tree, after asserting the
    two trees are identical. Shipping them twice would double a 260-file tree for
    no reason; shipping one of them without checking would be an assumption.
"""
import argparse
import filecmp
import os
import re
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))

PACKAGE_ID = "Aspose.Slides.Cpp.FOSS"

# MSBuild's name for the platform -> the directory name inside the package.
PLATFORMS = [("x64", "win_x86_64"), ("Win32", "win_x86")]
CONFIGS = ["Release", "Debug"]
LIBS = ["aspose_slides_foss.lib", "pugixml.lib", "miniz.lib"]


def run(cmd, **kw):
    print("  $ " + " ".join(cmd), flush=True)
    subprocess.run(cmd, check=True, **kw)


def read_version():
    """The one place a version is written. Anything else is a copy."""
    text = open(os.path.join(REPO, "CMakeLists.txt"), encoding="utf-8").read()
    m = re.search(r"project\s*\(\s*AsposeSlidesFoss\s+VERSION\s+([0-9]+\.[0-9]+\.[0-9]+)",
                  text, re.S)
    if not m:
        sys.exit("could not read project(... VERSION ...) from CMakeLists.txt")
    return m.group(1)


def read_commit():
    try:
        out = subprocess.run(["git", "-C", REPO, "rev-parse", "HEAD"],
                             stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, check=True)
        return out.stdout.decode().strip()
    except Exception:
        return ""


def build(work, platform, generator, skip_build):
    build_dir = os.path.join(work, "build-" + platform)
    prefixes = {}
    if not skip_build:
        configure = ["cmake", "-S", REPO, "-B", build_dir, "-A", platform,
                     "-DASPOSE_SLIDES_FOSS_BUILD_TESTS=OFF",
                     "-DASPOSE_SLIDES_FOSS_INSTALL=ON",
                     "-DASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES=ON",
                     "-DASPOSE_SLIDES_FOSS_WARNINGS_AS_ERRORS=ON",
                     "-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"]
        if generator:
            configure += ["-G", generator]
        run(configure)
    for config in CONFIGS:
        prefix = os.path.join(work, "install-%s-%s" % (platform, config))
        if not skip_build:
            run(["cmake", "--build", build_dir, "--config", config, "--parallel", "4"])
            run(["cmake", "--install", build_dir, "--config", config, "--prefix", prefix])
        if not os.path.isdir(os.path.join(prefix, "lib")):
            sys.exit("no install tree at %s -- run without --skip-build" % prefix)
        prefixes[config] = prefix
    return prefixes


def stage(work, version, commit, prefixes):
    staging = os.path.join(work, "staging")
    if os.path.isdir(staging):
        shutil.rmtree(staging)
    native = os.path.join(staging, "build", "native")
    os.makedirs(native)

    # The targets file, at the ONLY path NuGet imports automatically:
    # build/native/<PackageId>.targets. check_package.py asserts this.
    shutil.copy2(os.path.join(HERE, PACKAGE_ID + ".targets"),
                 os.path.join(native, PACKAGE_ID + ".targets"))

    include_trees = []
    for platform, platform_dir in PLATFORMS:
        for config in CONFIGS:
            prefix = prefixes[platform][config]
            dest = os.path.join(native, "lib", platform_dir, config)
            os.makedirs(dest)
            for lib in LIBS:
                src = os.path.join(prefix, "lib", lib)
                if not os.path.isfile(src):
                    sys.exit("missing %s in %s" % (lib, prefix))
                shutil.copy2(src, os.path.join(dest, lib))
        include_trees.append(os.path.join(prefixes[platform]["Release"], "include"))

    # Assert before deduplicating. If the two platforms ever produce different
    # headers -- a generated version.h that embedded an architecture, say -- one
    # of the two audiences gets headers that do not describe their library.
    left, right = include_trees
    diff = filecmp.dircmp(left, right)

    def differences(d, path=""):
        out = [path + n for n in d.left_only + d.right_only + d.diff_files]
        for name, sub in d.subdirs.items():
            out += differences(sub, path + name + "/")
        return out

    found = differences(diff)
    if found:
        sys.exit("the x64 and Win32 header trees differ, so they cannot be shipped "
                 "once: %s" % found[:10])
    shutil.copytree(left, os.path.join(native, "include"))

    shutil.copy2(os.path.join(REPO, "docs", "nuget", "README.md"),
                 os.path.join(staging, "README.md"))
    shutil.copy2(os.path.join(REPO, "docs", "nuget", "icon.png"),
                 os.path.join(staging, "icon.png"))
    shutil.copy2(os.path.join(REPO, "LICENSE"), os.path.join(staging, "LICENSE"))
    shutil.copy2(os.path.join(REPO, "THIRD_PARTY_NOTICES"),
                 os.path.join(staging, "THIRD_PARTY_NOTICES"))

    template = open(os.path.join(HERE, PACKAGE_ID + ".nuspec.in"), encoding="utf-8").read()
    nuspec = os.path.join(staging, PACKAGE_ID + ".nuspec")
    with open(nuspec, "w", encoding="utf-8") as f:
        f.write(template.replace("@VERSION@", version).replace("@COMMIT@", commit))
    return staging, nuspec


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("--work", default=os.path.join(REPO, "build", "nuget-pack"))
    ap.add_argument("--output", default=None, help="where the .nupkg is written")
    ap.add_argument("--generator", default=os.environ.get("ASPOSE_SLIDES_FOSS_CMAKE_GENERATOR"),
                    help="CMake generator; omit to let CMake pick the newest Visual Studio")
    ap.add_argument("--nuget", default="nuget", help="path to nuget.exe")
    ap.add_argument("--skip-build", action="store_true",
                    help="reuse the install trees already in --work")
    ap.add_argument("--print-version", action="store_true",
                    help="print the version from CMakeLists.txt and exit, so that a caller "
                         "never has to re-implement the one that is read here")
    args = ap.parse_args(argv[1:])

    # Before the Windows check: reading the version is not a Windows operation, and
    # the release workflow's guard job asks for it on Linux.
    if args.print_version:
        print(read_version())
        return 0

    if os.name != "nt":
        sys.exit("this package carries MSVC static libraries and can only be built on Windows")

    work = os.path.abspath(args.work)
    output = os.path.abspath(args.output or os.path.join(work, "package"))
    os.makedirs(work, exist_ok=True)
    os.makedirs(output, exist_ok=True)

    version = read_version()
    commit = read_commit()
    print("%s %s" % (PACKAGE_ID, version), flush=True)

    prefixes = {}
    for platform, _ in PLATFORMS:
        print("\n=== %s ===" % platform, flush=True)
        prefixes[platform] = build(work, platform, args.generator, args.skip_build)

    print("\n=== staging ===", flush=True)
    staging, nuspec = stage(work, version, commit, prefixes)

    print("\n=== pack ===", flush=True)
    run([args.nuget, "pack", nuspec, "-BasePath", staging, "-OutputDirectory", output,
         "-NonInteractive", "-Verbosity", "quiet"])

    produced = os.path.join(output, "%s.%s.nupkg" % (PACKAGE_ID, version))
    if not os.path.isfile(produced):
        sys.exit("nuget pack did not produce %s" % produced)
    print("\n%s  (%.1f MB)" % (produced, os.path.getsize(produced) / 1e6))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
