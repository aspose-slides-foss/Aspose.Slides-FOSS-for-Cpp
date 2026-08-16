#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Aspose Pty Ltd
"""Validate produced .pptx files from outside the process that wrote them.

Two checks that cannot run inside the C++ test binary:

* **Structural assertions** on the raw ZIP — every relationship reference
  resolves, every part has a content type, every content-type Override names a
  part that exists, every slide relationship is registered in ``p:sldIdLst``
  and nothing under ``ppt/slides/`` is unreferenced.  These duplicate the
  in-process rules on purpose: an independent implementation of the same rule
  is what catches a harness that agrees with the writer by accident.

* **Third-party read-back** with ``python-pptx``, if it is installed.  A
  different reader with a different tolerance.  A package the writer's own
  reader loads and a foreign reader refuses is a defect in the package, not in
  the reader.

Neither check calls the library under test, which is the whole point: a reader
that shares the writer's misunderstanding of the format confirms nothing.

Usage::

    python tests/conformance/validate.py <directory-or-file> [...]
    python tests/conformance/validate.py out/ --require-python-pptx

Exit status is 0 when every file passes and 1 otherwise, so CI can run it as
its own step.
"""

from __future__ import annotations

import argparse
import pathlib
import re
import sys
import zipfile
from xml.etree import ElementTree as ET

NS_REL_TYPES = "http://schemas.openxmlformats.org/officeDocument/2006/relationships"
NS_REL_PART = "http://schemas.openxmlformats.org/package/2006/relationships"
NS_CT = "http://schemas.openxmlformats.org/package/2006/content-types"
NS_P = "http://schemas.openxmlformats.org/presentationml/2006/main"

PML = "application/vnd.openxmlformats-officedocument.presentationml."

# Part-name conventions ECMA-376 fixes, and the content type each requires.
ECMA_CONTENT_TYPES: list[tuple[re.Pattern[str], str]] = [
    (re.compile(r"^ppt/slides/slide\d+\.xml$"), PML + "slide+xml"),
    (re.compile(r"^ppt/slideLayouts/slideLayout\d+\.xml$"), PML + "slideLayout+xml"),
    (re.compile(r"^ppt/slideMasters/slideMaster\d+\.xml$"), PML + "slideMaster+xml"),
    (re.compile(r"^ppt/notesSlides/notesSlide\d+\.xml$"), PML + "notesSlide+xml"),
    (re.compile(r"^ppt/notesMasters/notesMaster\d+\.xml$"), PML + "notesMaster+xml"),
    (re.compile(r"^ppt/comments/.*\.xml$"), PML + "comments+xml"),
    (re.compile(r"^ppt/media/.*\.png$"), "image/png"),
    (re.compile(r"^ppt/media/.*\.jpe?g$"), "image/jpeg"),
    (re.compile(r"^ppt/media/.*\.gif$"), "image/gif"),
    (
        re.compile(r"^ppt/theme/theme\d+\.xml$"),
        "application/vnd.openxmlformats-officedocument.theme+xml",
    ),
]

# Attribute local names in the relationships namespace that hold a rel id.
REL_ID_ATTRS = {"id", "embed", "link", "pict", "dm", "lo", "qs", "cs"}


def rels_name_for(part: str) -> str:
    """`ppt/slides/slide1.xml` -> `ppt/slides/_rels/slide1.xml.rels`."""
    head, _, tail = part.rpartition("/")
    return f"{head}/_rels/{tail}.rels" if head else f"_rels/{tail}.rels"


def declared_rel_ids(zf: zipfile.ZipFile, rels_part: str) -> dict[str, str]:
    if rels_part not in zf.namelist():
        return {}
    root = ET.fromstring(zf.read(rels_part))
    out = {}
    for rel in root.findall(f"{{{NS_REL_PART}}}Relationship"):
        out[rel.get("Id", "")] = rel.get("Target", "")
    return out


def content_type_map(zf: zipfile.ZipFile) -> tuple[dict[str, str], dict[str, str]]:
    """Return (overrides by part name without slash, defaults by extension)."""
    if "[Content_Types].xml" not in zf.namelist():
        return {}, {}
    root = ET.fromstring(zf.read("[Content_Types].xml"))
    overrides = {
        ov.get("PartName", "").lstrip("/"): ov.get("ContentType", "")
        for ov in root.findall(f"{{{NS_CT}}}Override")
    }
    defaults = {
        d.get("Extension", "").lower(): d.get("ContentType", "")
        for d in root.findall(f"{{{NS_CT}}}Default")
    }
    return overrides, defaults


def resolve_content_type(
    part: str, overrides: dict[str, str], defaults: dict[str, str]
) -> str:
    if part in overrides:
        return overrides[part]
    _, _, ext = part.rpartition(".")
    return defaults.get(ext.lower(), "")


def check_relationship_references(zf: zipfile.ZipFile) -> list[str]:
    problems = []
    for part in zf.namelist():
        if not part.endswith(".xml") or part == "[Content_Types].xml":
            continue
        try:
            root = ET.fromstring(zf.read(part))
        except ET.ParseError as exc:
            problems.append(f"{part}: not well-formed XML: {exc}")
            continue

        declared = declared_rel_ids(zf, rels_name_for(part))
        for element in root.iter():
            for name, value in element.attrib.items():
                if not name.startswith(f"{{{NS_REL_TYPES}}}"):
                    continue
                if name.rpartition("}")[2] not in REL_ID_ATTRS or not value:
                    continue
                if value not in declared:
                    problems.append(
                        f"{part}: {name.rpartition('}')[2]}=\"{value}\" does not "
                        f"resolve in {rels_name_for(part)}"
                    )
    return problems


def check_content_types(zf: zipfile.ZipFile) -> list[str]:
    problems = []
    overrides, defaults = content_type_map(zf)
    names = set(zf.namelist())

    for part in zf.namelist():
        if part == "[Content_Types].xml":
            continue
        if not resolve_content_type(part, overrides, defaults):
            problems.append(f"{part}: no content type resolves for this part")

    for part in overrides:
        if part not in names:
            problems.append(f"[Content_Types].xml: Override names missing part /{part}")

    for pattern, expected in ECMA_CONTENT_TYPES:
        for part in zf.namelist():
            if not pattern.match(part):
                continue
            actual = resolve_content_type(part, overrides, defaults)
            if actual != expected:
                problems.append(
                    f"{part}: content type is {actual or '<none>'!r}, "
                    f"ECMA-376 requires {expected!r}"
                )
    return problems


# The main part's content type is what tells a consumer which member of the
# PPTX family the package is. PowerPoint refuses a file whose extension and
# main content type disagree, reporting that the file extension has changed.
MAIN_CONTENT_TYPE_BY_EXTENSION = {
    "pptx": PML + "presentation.main+xml",
    "potx": PML + "template.main+xml",
    "ppsx": PML + "slideshow.main+xml",
    "pptm": "application/vnd.ms-powerpoint.presentation.macroEnabled.main+xml",
    "potm": "application/vnd.ms-powerpoint.template.macroEnabled.main+xml",
    "ppsm": "application/vnd.ms-powerpoint.slideshow.macroEnabled.main+xml",
}


def check_extension_matches_main_part(
    path: pathlib.Path, zf: zipfile.ZipFile
) -> list[str]:
    ext = path.suffix.lstrip(".").lower()
    expected = MAIN_CONTENT_TYPE_BY_EXTENSION.get(ext)
    if expected is None:
        if "ppt/presentation.xml" in zf.namelist():
            return [
                f"named .{ext} but the package is a PresentationML package; "
                f"PowerPoint refuses a file whose extension does not match its "
                f"contents"
            ]
        return []

    overrides, defaults = content_type_map(zf)
    actual = resolve_content_type("ppt/presentation.xml", overrides, defaults)
    if actual != expected:
        return [
            f"ppt/presentation.xml: content type is {actual or '<none>'!r}, "
            f"but a .{ext} package requires {expected!r}"
        ]
    return []


# Relationship types a part may hold at most once. Two of these on one part is
# a package the Open XML SDK rejects outright and PowerPoint refuses to open.
AT_MOST_ONE_PER_PART = ("comments", "slideLayout", "notesSlide", "notesMaster")


def check_relationship_cardinality(zf: zipfile.ZipFile) -> list[str]:
    problems = []
    for part in zf.namelist():
        if not part.endswith(".rels"):
            continue
        root = ET.fromstring(zf.read(part))
        seen: dict[str, int] = {}
        for rel in root.findall(f"{{{NS_REL_PART}}}Relationship"):
            kind = rel.get("Type", "").rpartition("/")[2]
            seen[kind] = seen.get(kind, 0) + 1
        for kind in AT_MOST_ONE_PER_PART:
            if seen.get(kind, 0) > 1:
                problems.append(
                    f"{part}: {seen[kind]} relationships of type {kind!r}; "
                    f"a part may have at most one"
                )
    return problems


def check_slide_registration(zf: zipfile.ZipFile) -> list[str]:
    """Every slide part is reachable from `p:sldIdLst`, and vice versa."""
    problems = []
    if "ppt/presentation.xml" not in zf.namelist():
        return ["ppt/presentation.xml: missing"]

    root = ET.fromstring(zf.read("ppt/presentation.xml"))
    id_list = root.find(f"{{{NS_P}}}sldIdLst")
    referenced_rids = (
        [
            e.get(f"{{{NS_REL_TYPES}}}id", "")
            for e in id_list.findall(f"{{{NS_P}}}sldId")
        ]
        if id_list is not None
        else []
    )

    rels = declared_rel_ids(zf, "ppt/_rels/presentation.xml.rels")
    registered_targets = set()
    for rid in referenced_rids:
        if rid not in rels:
            problems.append(f"ppt/presentation.xml: sldId r:id={rid!r} has no relationship")
            continue
        registered_targets.add("ppt/" + rels[rid].lstrip("/"))

    slide_parts = {
        n for n in zf.namelist() if re.match(r"^ppt/slides/slide\d+\.xml$", n)
    }
    for orphan in sorted(slide_parts - registered_targets):
        problems.append(
            f"{orphan}: a slide part that no <p:sldId> refers to; consumers do "
            f"not see it as a slide"
        )
    for missing in sorted(registered_targets - slide_parts):
        problems.append(f"{missing}: registered in sldIdLst but not in the package")
    return problems


# python-pptx opens only these two members of the PPTX family: its package
# reader maps exactly these content types to a presentation part and raises
# ValueError("is not a PowerPoint file") for the rest.  A template or a
# slideshow package is a perfectly valid file that PowerPoint opens; the
# reader's narrower range is not a finding about the package, so those are
# skipped rather than reported.
PYTHON_PPTX_READABLE_MAIN_TYPES = {
    PML + "presentation.main+xml",
    "application/vnd.ms-powerpoint.presentation.macroEnabled.main+xml",
}


def check_python_pptx(path: pathlib.Path) -> list[str]:
    try:
        from pptx import Presentation  # type: ignore[import-not-found]
    except ImportError:
        return []
    ext = path.suffix.lstrip(".").lower()
    main_type = MAIN_CONTENT_TYPE_BY_EXTENSION.get(ext)
    if main_type is not None and main_type not in PYTHON_PPTX_READABLE_MAIN_TYPES:
        return []
    try:
        deck = Presentation(str(path))
        for slide in deck.slides:
            for shape in slide.shapes:
                _ = shape.shape_type, shape.name
    except Exception as exc:  # noqa: BLE001 - any reader failure is a finding
        return [f"python-pptx refuses the package: {type(exc).__name__}: {exc}"]
    return []


def validate(path: pathlib.Path, require_reader: bool) -> list[str]:
    problems: list[str] = []
    try:
        with zipfile.ZipFile(path) as zf:
            problems += check_relationship_references(zf)
            problems += check_content_types(zf)
            problems += check_extension_matches_main_part(path, zf)
            problems += check_relationship_cardinality(zf)
            problems += check_slide_registration(zf)
    except zipfile.BadZipFile:
        return [f"not a ZIP archive ({path.stat().st_size} bytes)"]

    if require_reader:
        try:
            import pptx  # noqa: F401
        except ImportError:
            problems.append(
                "python-pptx is not installed and --require-python-pptx was given"
            )
            return problems
    problems += check_python_pptx(path)
    return problems


def collect(targets: list[str]) -> list[pathlib.Path]:
    files: list[pathlib.Path] = []
    for target in targets:
        path = pathlib.Path(target)
        if path.is_dir():
            for suffix in (
                "pptx", "potx", "ppsx", "pptm", "potm", "ppsm",
                # Formats the library is asked for and does not implement land
                # here too: a package named .pdf is exactly the finding.
                "pdf", "odp", "html", "ppt", "pps", "pot", "xps", "tiff",
                "gif", "swf", "otp", "fodp", "md", "xml",
            ):
                files += sorted(path.rglob(f"*.{suffix}"))
        else:
            files.append(path)
    return files


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("targets", nargs="+", help="files or directories to check")
    parser.add_argument(
        "--require-python-pptx",
        action="store_true",
        help="fail if python-pptx is not installed instead of skipping read-back",
    )
    parser.add_argument(
        "--min-files",
        type=int,
        default=0,
        metavar="N",
        help=(
            "fail unless at least N files were checked. Zero files already fails, "
            "but a corpus that shrank because tests stopped writing to it still "
            "reports success on the files that remain; this turns that into a failure."
        ),
    )
    args = parser.parse_args(argv)

    files = collect(args.targets)
    if not files:
        print("no presentation files found", file=sys.stderr)
        return 1

    if len(files) < args.min_files:
        print(
            f"expected at least {args.min_files} presentation file(s), found {len(files)}",
            file=sys.stderr,
        )
        return 1

    failed = 0
    for path in files:
        problems = validate(path, args.require_python_pptx)
        if problems:
            failed += 1
            print(f"FAIL {path}")
            for problem in problems:
                print(f"       {problem}")
        else:
            print(f"ok   {path}")

    print(f"\n{len(files)} file(s) checked, {failed} failed")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
