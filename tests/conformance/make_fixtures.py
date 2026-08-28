#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Aspose Pty Ltd
"""Generate the committed .pptx fixtures under tests/test_data.

The fixtures are decks this library did **not** write.  They exist so that the
reader can be tested against input it did not produce itself: every other
``.pptx`` path named in the test tree points at a file the library created
seconds earlier, which cannot exercise the load path at all.

The XML below is written out by hand rather than by any presentation library,
so the fixtures carry no third-party content and their whole shape is visible
in this file.  Regenerate with::

    python tests/conformance/make_fixtures.py

and re-run ``tests/conformance/validate.py`` afterwards.  The output is
byte-deterministic (fixed timestamps, fixed member order, stored compression),
so a regeneration that changes nothing produces no diff.
"""

from __future__ import annotations

import pathlib
import zipfile

OUT_DIR = pathlib.Path(__file__).resolve().parent.parent / "test_data"

NS_P = 'xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main"'
NS_A = 'xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main"'
NS_R = 'xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"'

DECL = '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>\n'


def _theme() -> str:
    """A minimal but schema-complete a:theme part.

    CT_BaseStyles requires clrScheme, fontScheme and fmtScheme, and fmtScheme
    requires exactly three entries in each of its four style lists.
    """
    colors = [
        ("dk1", '<a:sysClr val="windowText" lastClr="000000"/>'),
        ("lt1", '<a:sysClr val="window" lastClr="FFFFFF"/>'),
        ("dk2", '<a:srgbClr val="44546A"/>'),
        ("lt2", '<a:srgbClr val="E7E6E6"/>'),
        ("accent1", '<a:srgbClr val="4472C4"/>'),
        ("accent2", '<a:srgbClr val="ED7D31"/>'),
        ("accent3", '<a:srgbClr val="A5A5A5"/>'),
        ("accent4", '<a:srgbClr val="FFC000"/>'),
        ("accent5", '<a:srgbClr val="5B9BD5"/>'),
        ("accent6", '<a:srgbClr val="70AD47"/>'),
        ("hlink", '<a:srgbClr val="0563C1"/>'),
        ("folHlink", '<a:srgbClr val="954F72"/>'),
    ]
    clr_scheme = "".join(f"<a:{n}>{v}</a:{n}>" for n, v in colors)

    def font_group(tag: str) -> str:
        return (
            f'<a:{tag}><a:latin typeface="Calibri"/><a:ea typeface=""/>'
            f'<a:cs typeface=""/></a:{tag}>'
        )

    font_scheme = (
        '<a:fontScheme name="Office">'
        + font_group("majorFont")
        + font_group("minorFont")
        + "</a:fontScheme>"
    )

    solid = '<a:solidFill><a:schemeClr val="phClr"/></a:solidFill>'
    line = (
        '<a:ln w="6350" cap="flat" cmpd="sng" algn="ctr">'
        '<a:solidFill><a:schemeClr val="phClr"/></a:solidFill>'
        '<a:prstDash val="solid"/><a:miter lim="800000"/></a:ln>'
    )
    fmt_scheme = (
        '<a:fmtScheme name="Office">'
        f"<a:fillStyleLst>{solid * 3}</a:fillStyleLst>"
        f"<a:lnStyleLst>{line * 3}</a:lnStyleLst>"
        "<a:effectStyleLst>"
        + "<a:effectStyle><a:effectLst/></a:effectStyle>" * 3
        + "</a:effectStyleLst>"
        f"<a:bgFillStyleLst>{solid * 3}</a:bgFillStyleLst>"
        "</a:fmtScheme>"
    )

    return (
        DECL
        + f'<a:theme {NS_A} name="Conformance Fixture">'
        + "<a:themeElements>"
        + f'<a:clrScheme name="Office">{clr_scheme}</a:clrScheme>'
        + font_scheme
        + fmt_scheme
        + "</a:themeElements>"
        + "</a:theme>"
    )


def _empty_style_lists() -> str:
    return (
        "<p:txStyles>"
        "<p:titleStyle/><p:bodyStyle/><p:otherStyle/>"
        "</p:txStyles>"
    )


def _clr_map() -> str:
    return (
        '<p:clrMap bg1="lt1" tx1="dk1" bg2="lt2" tx2="dk2" accent1="accent1"'
        ' accent2="accent2" accent3="accent3" accent4="accent4"'
        ' accent5="accent5" accent6="accent6" hlink="hlink"'
        ' folHlink="folHlink"/>'
    )


def _placeholder_sp(
    shape_id: int,
    name: str,
    ph_attrs: str,
    xfrm: str,
    text: str,
) -> str:
    """A p:sp carrying a placeholder.

    ``xfrm`` is the literal ``<a:xfrm>`` element or the empty string.  A
    placeholder with no xfrm of its own inherits its geometry from the layout,
    which is the case the reader has to resolve.
    """
    body = (
        "<p:txBody><a:bodyPr/><a:lstStyle/>"
        f"<a:p><a:r><a:rPr lang=\"en-US\" dirty=\"0\"/><a:t>{text}</a:t></a:r></a:p>"
        "</p:txBody>"
    )
    return (
        "<p:sp>"
        "<p:nvSpPr>"
        f'<p:cNvPr id="{shape_id}" name="{name}"/>'
        "<p:cNvSpPr><a:spLocks noGrp=\"1\"/></p:cNvSpPr>"
        f"<p:nvPr><p:ph {ph_attrs}/></p:nvPr>"
        "</p:nvSpPr>"
        f"<p:spPr>{xfrm}</p:spPr>"
        + body
        + "</p:sp>"
    )


def _sp_tree(shapes: str) -> str:
    return (
        "<p:spTree>"
        '<p:nvGrpSpPr><p:cNvPr id="1" name=""/><p:cNvGrpSpPr/><p:nvPr/></p:nvGrpSpPr>'
        "<p:grpSpPr><a:xfrm>"
        '<a:off x="0" y="0"/><a:ext cx="0" cy="0"/>'
        '<a:chOff x="0" y="0"/><a:chExt cx="0" cy="0"/>'
        "</a:xfrm></p:grpSpPr>"
        + shapes
        + "</p:spTree>"
    )


def _slide_master() -> str:
    shapes = _placeholder_sp(
        2,
        "Title Placeholder 1",
        'type="title"',
        '<a:xfrm><a:off x="838200" y="365125"/><a:ext cx="7772400" cy="1325563"/></a:xfrm>',
        "",
    ) + _placeholder_sp(
        3,
        "Text Placeholder 2",
        'type="body" idx="1"',
        '<a:xfrm><a:off x="838200" y="1825625"/><a:ext cx="7772400" cy="4351338"/></a:xfrm>',
        "",
    )
    return (
        DECL
        + f"<p:sldMaster {NS_P} {NS_A} {NS_R}>"
        + "<p:cSld>"
        + '<p:bg><p:bgPr><a:solidFill><a:schemeClr val="bg1"/></a:solidFill>'
          "<a:effectLst/></p:bgPr></p:bg>"
        + _sp_tree(shapes)
        + "</p:cSld>"
        + _clr_map()
        + '<p:sldLayoutIdLst><p:sldLayoutId id="2147483649" r:id="rId1"/></p:sldLayoutIdLst>'
        + _empty_style_lists()
        + "</p:sldMaster>"
    )


def _slide_layout() -> str:
    shapes = _placeholder_sp(
        2,
        "Title 1",
        'type="title"',
        '<a:xfrm><a:off x="838200" y="365125"/><a:ext cx="7772400" cy="1325563"/></a:xfrm>',
        "",
    ) + _placeholder_sp(
        3,
        "Content Placeholder 2",
        'idx="1"',
        '<a:xfrm><a:off x="838200" y="1825625"/><a:ext cx="7772400" cy="4351338"/></a:xfrm>',
        "",
    )
    return (
        DECL
        + f'<p:sldLayout {NS_P} {NS_A} {NS_R} type="obj" preserve="1">'
        + f"<p:cSld name=\"Title and Content\">{_sp_tree(shapes)}</p:cSld>"
        + "<p:clrMapOvr><a:masterClrMapping/></p:clrMapOvr>"
        + "</p:sldLayout>"
    )


def _slide() -> str:
    """The slide under test.

    Both placeholders carry a bare ``<p:spPr/>``: no ``a:xfrm`` of their own,
    so their position and size resolve through the layout.  That is exactly
    the input the shape reader has to survive.
    """
    shapes = _placeholder_sp(
        2, "Title 1", 'type="title"', "", "Fixture Title"
    ) + _placeholder_sp(
        3, "Content Placeholder 2", 'idx="1"', "", "Fixture body text"
    )
    return (
        DECL
        + f"<p:sld {NS_P} {NS_A} {NS_R}>"
        + f"<p:cSld>{_sp_tree(shapes)}</p:cSld>"
        + "<p:clrMapOvr><a:masterClrMapping/></p:clrMapOvr>"
        + "</p:sld>"
    )


def _presentation() -> str:
    return (
        DECL
        + f'<p:presentation {NS_P} {NS_A} {NS_R} saveSubsetFonts="1">'
        + '<p:sldMasterIdLst><p:sldMasterId id="2147483648" r:id="rId1"/></p:sldMasterIdLst>'
        + '<p:sldIdLst><p:sldId id="256" r:id="rId2"/></p:sldIdLst>'
        + '<p:sldSz cx="9144000" cy="6858000" type="screen4x3"/>'
        + '<p:notesSz cx="6858000" cy="9144000"/>'
        + "</p:presentation>"
    )


# The relationship *type* vocabulary and the namespace of the .rels part
# itself are two different URIs; mixing them up produces a package that some
# readers accept and others reject at load.
REL = "http://schemas.openxmlformats.org/officeDocument/2006/relationships"
REL_NS = 'xmlns="http://schemas.openxmlformats.org/package/2006/relationships"'


def _rels(entries: list[tuple[str, str, str]]) -> str:
    body = "".join(
        f'<Relationship Id="{rid}" Type="{REL}/{typ}" Target="{target}"/>'
        for rid, typ, target in entries
    )
    return DECL + f"<Relationships {REL_NS}>{body}</Relationships>"


def _content_types() -> str:
    ct = "http://schemas.openxmlformats.org/package/2006/content-types"
    pml = "application/vnd.openxmlformats-officedocument.presentationml"
    dml = "application/vnd.openxmlformats-officedocument"
    overrides = [
        ("/ppt/presentation.xml", f"{pml}.presentation.main+xml"),
        ("/ppt/slideMasters/slideMaster1.xml", f"{pml}.slideMaster+xml"),
        ("/ppt/slideLayouts/slideLayout1.xml", f"{pml}.slideLayout+xml"),
        ("/ppt/slides/slide1.xml", f"{pml}.slide+xml"),
        ("/ppt/theme/theme1.xml", f"{dml}.theme+xml"),
        ("/docProps/core.xml", "application/vnd.openxmlformats-package.core-properties+xml"),
        ("/docProps/app.xml", f"{dml}.extended-properties+xml"),
    ]
    body = (
        '<Default Extension="rels"'
        ' ContentType="application/vnd.openxmlformats-package.relationships+xml"/>'
        '<Default Extension="xml" ContentType="application/xml"/>'
    ) + "".join(
        f'<Override PartName="{p}" ContentType="{c}"/>' for p, c in overrides
    )
    return DECL + f'<Types xmlns="{ct}">{body}</Types>'


def _core_props() -> str:
    cp = "http://schemas.openxmlformats.org/package/2006/metadata/core-properties"
    return (
        DECL
        + f'<cp:coreProperties xmlns:cp="{cp}"'
        ' xmlns:dc="http://purl.org/dc/elements/1.1/"'
        ' xmlns:dcterms="http://purl.org/dc/terms/"'
        ' xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">'
        "<dc:title>Conformance fixture</dc:title>"
        '<dcterms:created xsi:type="dcterms:W3CDTF">2026-01-01T00:00:00Z</dcterms:created>'
        '<dcterms:modified xsi:type="dcterms:W3CDTF">2026-01-01T00:00:00Z</dcterms:modified>'
        "</cp:coreProperties>"
    )


def _app_props() -> str:
    ep = "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties"
    return (
        DECL
        + f'<Properties xmlns="{ep}">'
        "<Slides>1</Slides><Paragraphs>2</Paragraphs>"
        "</Properties>"
    )


def title_and_content_deck() -> dict[str, str]:
    """The parts of ``powerpoint_title_and_content.pptx``, in write order."""
    return {
        "[Content_Types].xml": _content_types(),
        "_rels/.rels": _rels(
            [
                ("rId1", "officeDocument", "ppt/presentation.xml"),
                ("rId2", "metadata/core-properties", "docProps/core.xml"),
                ("rId3", "extended-properties", "docProps/app.xml"),
            ]
        ),
        "docProps/app.xml": _app_props(),
        "docProps/core.xml": _core_props(),
        "ppt/presentation.xml": _presentation(),
        "ppt/_rels/presentation.xml.rels": _rels(
            [
                ("rId1", "slideMaster", "slideMasters/slideMaster1.xml"),
                ("rId2", "slide", "slides/slide1.xml"),
                ("rId3", "theme", "theme/theme1.xml"),
            ]
        ),
        "ppt/slideMasters/slideMaster1.xml": _slide_master(),
        "ppt/slideMasters/_rels/slideMaster1.xml.rels": _rels(
            [
                ("rId1", "slideLayout", "../slideLayouts/slideLayout1.xml"),
                ("rId2", "theme", "../theme/theme1.xml"),
            ]
        ),
        "ppt/slideLayouts/slideLayout1.xml": _slide_layout(),
        "ppt/slideLayouts/_rels/slideLayout1.xml.rels": _rels(
            [("rId1", "slideMaster", "../slideMasters/slideMaster1.xml")]
        ),
        "ppt/slides/slide1.xml": _slide(),
        "ppt/slides/_rels/slide1.xml.rels": _rels(
            [("rId1", "slideLayout", "../slideLayouts/slideLayout1.xml")]
        ),
        "ppt/theme/theme1.xml": _theme(),
    }


def write_deck(path: pathlib.Path, parts: dict[str, str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(path, "w", zipfile.ZIP_DEFLATED) as zf:
        for name, text in parts.items():
            info = zipfile.ZipInfo(name, date_time=(2026, 1, 1, 0, 0, 0))
            info.compress_type = zipfile.ZIP_DEFLATED
            info.external_attr = 0o600 << 16
            zf.writestr(info, text.encode("utf-8"))


def main() -> None:
    target = OUT_DIR / "powerpoint_title_and_content.pptx"
    write_deck(target, title_and_content_deck())
    print(f"wrote {target} ({target.stat().st_size} bytes)")


if __name__ == "__main__":
    main()
