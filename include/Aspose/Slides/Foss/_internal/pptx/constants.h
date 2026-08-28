// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file constants.h
/// @brief PPTX XML namespace constants, qualified element names, and attribute helpers.

#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

namespace Aspose::Slides::Foss::Internal::pptx {

// ---------------------------------------------------------------------------
// Raw namespace URIs
// ---------------------------------------------------------------------------

/// XML namespace URIs used in PPTX documents.
namespace ns_uri {

inline constexpr std::string_view kP =
    "http://schemas.openxmlformats.org/presentationml/2006/main";
inline constexpr std::string_view kA =
    "http://schemas.openxmlformats.org/drawingml/2006/main";
inline constexpr std::string_view kR =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships";
inline constexpr std::string_view kPR =
    "http://schemas.openxmlformats.org/package/2006/relationships";
inline constexpr std::string_view kCT =
    "http://schemas.openxmlformats.org/package/2006/content-types";
inline constexpr std::string_view kCP =
    "http://schemas.openxmlformats.org/package/2006/metadata/core-properties";
inline constexpr std::string_view kDC =
    "http://purl.org/dc/elements/1.1/";
inline constexpr std::string_view kDCTerms =
    "http://purl.org/dc/terms/";
inline constexpr std::string_view kEP =
    "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties";
inline constexpr std::string_view kV =
    "urn:schemas-microsoft-com:vml";
inline constexpr std::string_view kO =
    "urn:schemas-microsoft-com:office:office";
inline constexpr std::string_view kC =
    "http://schemas.openxmlformats.org/drawingml/2006/chart";
inline constexpr std::string_view kDGM =
    "http://schemas.openxmlformats.org/drawingml/2006/diagram";
inline constexpr std::string_view kPIC =
    "http://schemas.openxmlformats.org/drawingml/2006/picture";
inline constexpr std::string_view kM =
    "http://schemas.openxmlformats.org/officeDocument/2006/math";
inline constexpr std::string_view kP14 =
    "http://schemas.microsoft.com/office/powerpoint/2010/main";
inline constexpr std::string_view kP15 =
    "http://schemas.microsoft.com/office/powerpoint/2012/main";
inline constexpr std::string_view kA14 =
    "http://schemas.microsoft.com/office/drawing/2010/main";
inline constexpr std::string_view kMC =
    "http://schemas.openxmlformats.org/markup-compatibility/2006";

} // namespace ns_uri

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

inline const std::unordered_map<std::string, std::string>& namespaces_map() {
    static const std::unordered_map<std::string, std::string> m = {
        {"p",       std::string(ns_uri::kP)},
        {"a",       std::string(ns_uri::kA)},
        {"r",       std::string(ns_uri::kR)},
        {"pr",      std::string(ns_uri::kPR)},
        {"ct",      std::string(ns_uri::kCT)},
        {"cp",      std::string(ns_uri::kCP)},
        {"dc",      std::string(ns_uri::kDC)},
        {"dcterms", std::string(ns_uri::kDCTerms)},
        {"ep",      std::string(ns_uri::kEP)},
        {"v",       std::string(ns_uri::kV)},
        {"o",       std::string(ns_uri::kO)},
        {"c",       std::string(ns_uri::kC)},
        {"dgm",     std::string(ns_uri::kDGM)},
        {"pic",     std::string(ns_uri::kPIC)},
        {"m",       std::string(ns_uri::kM)},
        {"p14",     std::string(ns_uri::kP14)},
        {"p15",     std::string(ns_uri::kP15)},
        {"a14",     std::string(ns_uri::kA14)},
        {"mc",      std::string(ns_uri::kMC)},
    };
    return m;
}

// ---------------------------------------------------------------------------
// Ns – formatted namespace strings  "{uri}"
// ---------------------------------------------------------------------------

namespace detail {

/// Build a Clark-notation namespace prefix: "{uri}".
inline std::string make_ns(std::string_view uri) {
    std::string s;
    s.reserve(uri.size() + 2);
    s += '{';
    s += uri;
    s += '}';
    return s;
}

} // namespace detail

/// Namespace helper providing Clark-notation formatted strings ("{uri}").
struct Ns {
    static inline const std::string kP   = detail::make_ns(ns_uri::kP);
    static inline const std::string kA   = detail::make_ns(ns_uri::kA);
    static inline const std::string kR   = detail::make_ns(ns_uri::kR);
    static inline const std::string kPR  = detail::make_ns(ns_uri::kPR);
    static inline const std::string kCT  = detail::make_ns(ns_uri::kCT);
    static inline const std::string kC   = detail::make_ns(ns_uri::kC);
    static inline const std::string kPIC = detail::make_ns(ns_uri::kPIC);

    /// Get formatted namespace string by prefix.
    /// @param prefix Namespace prefix (e.g., "p", "a", "r").
    /// @return Clark-notation string like "{http://...}".
    /// @throws std::out_of_range if prefix not found.
    static std::string get(std::string_view prefix) {
        const auto& m = namespaces_map();
        auto it = m.find(std::string(prefix));
        if (it == m.end()) {
            throw std::out_of_range(
                std::string("Unknown namespace prefix: ") + std::string(prefix));
        }
        return detail::make_ns(it->second);
    }
};

// ---------------------------------------------------------------------------
// Elements – fully-qualified element names
// ---------------------------------------------------------------------------

/// Common PPTX element names with full namespace qualification.
struct Elements {
    // -- Presentation elements --
    static inline const std::string kPresentation         = Ns::kP + "presentation";
    static inline const std::string kSldIdLst             = Ns::kP + "sldIdLst";
    static inline const std::string kSldId                = Ns::kP + "sldId";
    static inline const std::string kSldMasterIdLst       = Ns::kP + "sldMasterIdLst";
    static inline const std::string kSldMasterId          = Ns::kP + "sldMasterId";
    static inline const std::string kSldSz                = Ns::kP + "sldSz";
    static inline const std::string kNotesSz              = Ns::kP + "notesSz";

    // -- Slide elements --
    static inline const std::string kSld                  = Ns::kP + "sld";
    static inline const std::string kCSld                 = Ns::kP + "cSld";
    static inline const std::string kSpTree               = Ns::kP + "spTree";

    // -- Shape elements --
    static inline const std::string kSp                   = Ns::kP + "sp";
    static inline const std::string kNvSpPr               = Ns::kP + "nvSpPr";
    static inline const std::string kCNvPr                = Ns::kP + "cNvPr";
    static inline const std::string kSpPr                 = Ns::kP + "spPr";
    static inline const std::string kTxBody               = Ns::kP + "txBody";

    // -- DrawingML elements --
    static inline const std::string kAP                   = Ns::kA + "p";
    static inline const std::string kAR                   = Ns::kA + "r";
    static inline const std::string kAT                   = Ns::kA + "t";
    static inline const std::string kAXfrm                = Ns::kA + "xfrm";
    static inline const std::string kAOff                 = Ns::kA + "off";
    static inline const std::string kAExt                 = Ns::kA + "ext";

    // -- Fill elements --
    static inline const std::string kANoFill              = Ns::kA + "noFill";
    static inline const std::string kASolidFill           = Ns::kA + "solidFill";
    static inline const std::string kAGradFill            = Ns::kA + "gradFill";
    static inline const std::string kAPattFill            = Ns::kA + "pattFill";
    static inline const std::string kABlipFill            = Ns::kA + "blipFill";
    static inline const std::string kAGrpFill             = Ns::kA + "grpFill";

    // -- Color elements --
    static inline const std::string kASrgbClr             = Ns::kA + "srgbClr";
    static inline const std::string kASchemeClr           = Ns::kA + "schemeClr";
    static inline const std::string kAPrstClr             = Ns::kA + "prstClr";
    static inline const std::string kASysClr              = Ns::kA + "sysClr";
    static inline const std::string kAHlsClr              = Ns::kA + "hlsClr";
    static inline const std::string kAScrgbClr            = Ns::kA + "scrgbClr";

    // -- Gradient elements --
    static inline const std::string kAGsLst               = Ns::kA + "gsLst";
    static inline const std::string kAGs                  = Ns::kA + "gs";
    static inline const std::string kALin                 = Ns::kA + "lin";
    static inline const std::string kAPath                = Ns::kA + "path";
    static inline const std::string kATileRect            = Ns::kA + "tileRect";

    // -- Pattern elements --
    static inline const std::string kAFgClr               = Ns::kA + "fgClr";
    static inline const std::string kABgClr               = Ns::kA + "bgClr";

    // -- Text elements --
    static inline const std::string kABodyPr              = Ns::kA + "bodyPr";
    static inline const std::string kALstStyle            = Ns::kA + "lstStyle";
    static inline const std::string kARPr                 = Ns::kA + "rPr";
    static inline const std::string kAPPr                 = Ns::kA + "pPr";
    static inline const std::string kAEndParaRPr          = Ns::kA + "endParaRPr";
    static inline const std::string kAHighlight           = Ns::kA + "highlight";
    static inline const std::string kAULnTx               = Ns::kA + "uLnTx";
    static inline const std::string kAULn                 = Ns::kA + "uLn";
    static inline const std::string kAUFillTx             = Ns::kA + "uFillTx";
    static inline const std::string kAUFill               = Ns::kA + "uFill";
    static inline const std::string kADefRPr              = Ns::kA + "defRPr";
    static inline const std::string kATabLst              = Ns::kA + "tabLst";
    static inline const std::string kALnSpc               = Ns::kA + "lnSpc";
    static inline const std::string kASpcBef              = Ns::kA + "spcBef";
    static inline const std::string kASpcAft              = Ns::kA + "spcAft";
    static inline const std::string kASpcPct              = Ns::kA + "spcPct";
    static inline const std::string kASpcPts              = Ns::kA + "spcPts";
    static inline const std::string kABuNone              = Ns::kA + "buNone";
    static inline const std::string kABuChar              = Ns::kA + "buChar";
    static inline const std::string kABuAutoNum           = Ns::kA + "buAutoNum";
    static inline const std::string kABuFont              = Ns::kA + "buFont";
    static inline const std::string kABuSzPct             = Ns::kA + "buSzPct";
    static inline const std::string kABuSzPts             = Ns::kA + "buSzPts";
    static inline const std::string kABuClr               = Ns::kA + "buClr";
    static inline const std::string kABuClrTx             = Ns::kA + "buClrTx";
    static inline const std::string kABuFontTx            = Ns::kA + "buFontTx";
    static inline const std::string kABuSzTx              = Ns::kA + "buSzTx";
    static inline const std::string kABuBlip              = Ns::kA + "buBlip";
    static inline const std::string kALatin               = Ns::kA + "latin";
    static inline const std::string kAEa                  = Ns::kA + "ea";
    static inline const std::string kACs                  = Ns::kA + "cs";
    static inline const std::string kASym                 = Ns::kA + "sym";

    // -- Autofit elements --
    static inline const std::string kANoAutofit           = Ns::kA + "noAutofit";
    static inline const std::string kASpAutoFit           = Ns::kA + "spAutoFit";
    static inline const std::string kANormAutofit         = Ns::kA + "normAutofit";

    // -- Text warp --
    static inline const std::string kAPrstTxWarp          = Ns::kA + "prstTxWarp";

    // -- Line elements --
    static inline const std::string kALn                  = Ns::kA + "ln";
    static inline const std::string kAPrstDash            = Ns::kA + "prstDash";
    static inline const std::string kACustDash            = Ns::kA + "custDash";
    static inline const std::string kARound               = Ns::kA + "round";
    static inline const std::string kABevel               = Ns::kA + "bevel";
    static inline const std::string kAMiter               = Ns::kA + "miter";
    static inline const std::string kAHeadEnd             = Ns::kA + "headEnd";
    static inline const std::string kATailEnd             = Ns::kA + "tailEnd";

    // -- 3D elements --
    static inline const std::string kAScene3d             = Ns::kA + "scene3d";
    static inline const std::string kASp3d                = Ns::kA + "sp3d";
    static inline const std::string kACamera              = Ns::kA + "camera";
    static inline const std::string kALightRig            = Ns::kA + "lightRig";
    static inline const std::string kABevelT              = Ns::kA + "bevelT";
    static inline const std::string kABevelB              = Ns::kA + "bevelB";
    static inline const std::string kAContourClr          = Ns::kA + "contourClr";
    static inline const std::string kAExtrusionClr        = Ns::kA + "extrusionClr";
    static inline const std::string kARot                 = Ns::kA + "rot";
    static inline const std::string kAEffectLst           = Ns::kA + "effectLst";
    static inline const std::string kAEffectDag           = Ns::kA + "effectDag";
    static inline const std::string kAExtLst              = Ns::kA + "extLst";

    // -- Effect elements --
    static inline const std::string kABlur                = Ns::kA + "blur";
    static inline const std::string kAFillOverlay         = Ns::kA + "fillOverlay";
    static inline const std::string kAGlow                = Ns::kA + "glow";
    static inline const std::string kAInnerShdw           = Ns::kA + "innerShdw";
    static inline const std::string kAOuterShdw           = Ns::kA + "outerShdw";
    static inline const std::string kAPrstShdw            = Ns::kA + "prstShdw";
    static inline const std::string kAReflection          = Ns::kA + "reflection";
    static inline const std::string kASoftEdge            = Ns::kA + "softEdge";

    // -- Table elements --
    static inline const std::string kAGraphic             = Ns::kA + "graphic";
    static inline const std::string kAGraphicData         = Ns::kA + "graphicData";
    static inline const std::string kATbl                 = Ns::kA + "tbl";
    static inline const std::string kATblPr               = Ns::kA + "tblPr";
    static inline const std::string kATblGrid             = Ns::kA + "tblGrid";
    static inline const std::string kAGridCol             = Ns::kA + "gridCol";
    static inline const std::string kATr                  = Ns::kA + "tr";
    static inline const std::string kATc                  = Ns::kA + "tc";
    static inline const std::string kATcPr                = Ns::kA + "tcPr";
    static inline const std::string kATblStyle            = Ns::kA + "tblStyle";
    static inline const std::string kATableStyleId        = Ns::kA + "tableStyleId";

    // -- Table border elements --
    static inline const std::string kALnL                 = Ns::kA + "lnL";
    static inline const std::string kALnR                 = Ns::kA + "lnR";
    static inline const std::string kALnT                 = Ns::kA + "lnT";
    static inline const std::string kALnB                 = Ns::kA + "lnB";
    static inline const std::string kALnTlToBr            = Ns::kA + "lnTlToBr";
    static inline const std::string kALnBlToTr            = Ns::kA + "lnBlToTr";

    // -- GraphicFrame elements --
    static inline const std::string kPGraphicFrame        = Ns::kP + "graphicFrame";
    static inline const std::string kPNvGraphicFramePr    = Ns::kP + "nvGraphicFramePr";
    static inline const std::string kPCNvGraphicFramePr   = Ns::kP + "cNvGraphicFramePr";
    // CT_NonVisualGraphicFrameProperties allows exactly one child, and its
    // name is graphicFrameLocks. The *type* is CT_GraphicalObjectFrameLocking,
    // which is where the older spelling came from.
    static inline const std::string kAGraphicFrameLocks   = Ns::kA + "graphicFrameLocks";
    static inline const std::string kPNvPr                = Ns::kP + "nvPr";
    static inline const std::string kPXfrm                = Ns::kP + "xfrm";

    // -- Table URI --
    static constexpr std::string_view kTableUri =
        "http://schemas.openxmlformats.org/drawingml/2006/table";

    // -- DrawingML txBody (for table cells) --
    static inline const std::string kATxBody              = Ns::kA + "txBody";
};

// ---------------------------------------------------------------------------
// Unit conversion constants
// ---------------------------------------------------------------------------

/// 1 point = 12700 EMUs (914400 EMU/inch / 72 points/inch).
inline constexpr int kEmuPerPoint = 12700;

/// OOXML stores rotation in 60000ths of a degree.
inline constexpr int kRotationUnit = 60000;

// ---------------------------------------------------------------------------
// Attributes – common PPTX attribute names
// ---------------------------------------------------------------------------

/// Common PPTX attribute names.
struct Attributes {
    // With namespace
    static inline const std::string kRId    = Ns::kR + "id";
    static inline const std::string kREmbed = Ns::kR + "embed";

    // Without namespace
    static constexpr std::string_view kId   = "id";
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kCx   = "cx";
    static constexpr std::string_view kCy   = "cy";
    static constexpr std::string_view kX    = "x";
    static constexpr std::string_view kY    = "y";
};

} // namespace Aspose::Slides::Foss::Internal::pptx
