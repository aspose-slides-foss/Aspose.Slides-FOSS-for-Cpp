// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include "shape_type_mapping.h"

#include <array>
#include <algorithm>
#include <string_view>
#include <unordered_map>

namespace Aspose::Slides::Foss::Internal::pptx::shape_type_mapping {

namespace {

/// A single entry in the OOXML prst ↔ ShapeType name mapping.
struct MappingEntry {
    std::string_view prst;
    std::string_view shape_type_name;
};

/// Complete mapping table between OOXML ST_ShapeType prst values and
/// ShapeType enum member names.
constexpr std::array kMappingTable = {
    MappingEntry{"line", "LINE"},
    MappingEntry{"lineInv", "LINE_INVERSE"},
    MappingEntry{"triangle", "TRIANGLE"},
    MappingEntry{"rtTriangle", "RIGHT_TRIANGLE"},
    MappingEntry{"rect", "RECTANGLE"},
    MappingEntry{"diamond", "DIAMOND"},
    MappingEntry{"parallelogram", "PARALLELOGRAM"},
    MappingEntry{"trapezoid", "TRAPEZOID"},
    MappingEntry{"nonIsoscelesTrapezoid", "NON_ISOSCELES_TRAPEZOID"},
    MappingEntry{"pentagon", "PENTAGON"},
    MappingEntry{"hexagon", "HEXAGON"},
    MappingEntry{"heptagon", "HEPTAGON"},
    MappingEntry{"octagon", "OCTAGON"},
    MappingEntry{"decagon", "DECAGON"},
    MappingEntry{"dodecagon", "DODECAGON"},
    MappingEntry{"star4", "FOUR_POINTED_STAR"},
    MappingEntry{"star5", "FIVE_POINTED_STAR"},
    MappingEntry{"star6", "SIX_POINTED_STAR"},
    MappingEntry{"star7", "SEVEN_POINTED_STAR"},
    MappingEntry{"star8", "EIGHT_POINTED_STAR"},
    MappingEntry{"star10", "TEN_POINTED_STAR"},
    MappingEntry{"star12", "TWELVE_POINTED_STAR"},
    MappingEntry{"star16", "SIXTEEN_POINTED_STAR"},
    MappingEntry{"star24", "TWENTY_FOUR_POINTED_STAR"},
    MappingEntry{"star32", "THIRTY_TWO_POINTED_STAR"},
    MappingEntry{"roundRect", "ROUND_CORNER_RECTANGLE"},
    MappingEntry{"round1Rect", "ONE_ROUND_CORNER_RECTANGLE"},
    MappingEntry{"round2SameRect", "TWO_SAMESIDE_ROUND_CORNER_RECTANGLE"},
    MappingEntry{"round2DiagRect", "TWO_DIAGONAL_ROUND_CORNER_RECTANGLE"},
    MappingEntry{"snipRoundRect", "ONE_SNIP_ONE_ROUND_CORNER_RECTANGLE"},
    MappingEntry{"snip1Rect", "ONE_SNIP_CORNER_RECTANGLE"},
    MappingEntry{"snip2SameRect", "TWO_SAMESIDE_SNIP_CORNER_RECTANGLE"},
    MappingEntry{"snip2DiagRect", "TWO_DIAGONAL_SNIP_CORNER_RECTANGLE"},
    MappingEntry{"plaque", "PLAQUE"},
    MappingEntry{"ellipse", "ELLIPSE"},
    MappingEntry{"teardrop", "TEARDROP"},
    MappingEntry{"homePlate", "HOME_PLATE"},
    MappingEntry{"chevron", "CHEVRON"},
    MappingEntry{"pieWedge", "PIE_WEDGE"},
    MappingEntry{"pie", "PIE"},
    MappingEntry{"blockArc", "BLOCK_ARC"},
    MappingEntry{"donut", "DONUT"},
    MappingEntry{"noSmoking", "NO_SMOKING"},
    MappingEntry{"rightArrow", "RIGHT_ARROW"},
    MappingEntry{"leftArrow", "LEFT_ARROW"},
    MappingEntry{"upArrow", "UP_ARROW"},
    MappingEntry{"downArrow", "DOWN_ARROW"},
    MappingEntry{"stripedRightArrow", "STRIPED_RIGHT_ARROW"},
    MappingEntry{"notchedRightArrow", "NOTCHED_RIGHT_ARROW"},
    MappingEntry{"bentUpArrow", "BENT_UP_ARROW"},
    MappingEntry{"leftRightArrow", "LEFT_RIGHT_ARROW"},
    MappingEntry{"upDownArrow", "UP_DOWN_ARROW"},
    MappingEntry{"leftUpArrow", "LEFT_UP_ARROW"},
    MappingEntry{"leftRightUpArrow", "LEFT_RIGHT_UP_ARROW"},
    MappingEntry{"quadArrow", "QUAD_ARROW"},
    MappingEntry{"leftArrowCallout", "CALLOUT_LEFT_ARROW"},
    MappingEntry{"rightArrowCallout", "CALLOUT_RIGHT_ARROW"},
    MappingEntry{"upArrowCallout", "CALLOUT_UP_ARROW"},
    MappingEntry{"downArrowCallout", "CALLOUT_DOWN_ARROW"},
    MappingEntry{"leftRightArrowCallout", "CALLOUT_LEFT_RIGHT_ARROW"},
    MappingEntry{"upDownArrowCallout", "CALLOUT_UP_DOWN_ARROW"},
    MappingEntry{"quadArrowCallout", "CALLOUT_QUAD_ARROW"},
    MappingEntry{"bentArrow", "BENT_ARROW"},
    MappingEntry{"uturnArrow", "U_TURN_ARROW"},
    MappingEntry{"circularArrow", "CIRCULAR_ARROW"},
    MappingEntry{"leftCircularArrow", "LEFT_CIRCULAR_ARROW"},
    MappingEntry{"leftRightCircularArrow", "LEFT_RIGHT_CIRCULAR_ARROW"},
    MappingEntry{"curvedRightArrow", "CURVED_RIGHT_ARROW"},
    MappingEntry{"curvedLeftArrow", "CURVED_LEFT_ARROW"},
    MappingEntry{"curvedUpArrow", "CURVED_UP_ARROW"},
    MappingEntry{"curvedDownArrow", "CURVED_DOWN_ARROW"},
    MappingEntry{"swooshArrow", "SWOOSH_ARROW"},
    MappingEntry{"cube", "CUBE"},
    MappingEntry{"can", "CAN"},
    MappingEntry{"lightningBolt", "LIGHTNING_BOLT"},
    MappingEntry{"heart", "HEART"},
    MappingEntry{"sun", "SUN"},
    MappingEntry{"moon", "MOON"},
    MappingEntry{"smileyFace", "SMILEY_FACE"},
    MappingEntry{"irregularSeal1", "IRREGULAR_SEAL1"},
    MappingEntry{"irregularSeal2", "IRREGULAR_SEAL2"},
    MappingEntry{"foldedCorner", "FOLDED_CORNER"},
    MappingEntry{"bevel", "BEVEL"},
    MappingEntry{"frame", "FRAME"},
    MappingEntry{"halfFrame", "HALF_FRAME"},
    MappingEntry{"corner", "CORNER"},
    MappingEntry{"diagStripe", "DIAGONAL_STRIPE"},
    MappingEntry{"chord", "CHORD"},
    MappingEntry{"arc", "CURVED_ARC"},
    MappingEntry{"leftBracket", "LEFT_BRACKET"},
    MappingEntry{"rightBracket", "RIGHT_BRACKET"},
    MappingEntry{"leftBrace", "LEFT_BRACE"},
    MappingEntry{"rightBrace", "RIGHT_BRACE"},
    MappingEntry{"bracketPair", "BRACKET_PAIR"},
    MappingEntry{"bracePair", "BRACE_PAIR"},
    MappingEntry{"straightConnector1", "STRAIGHT_CONNECTOR1"},
    MappingEntry{"bentConnector2", "BENT_CONNECTOR2"},
    MappingEntry{"bentConnector3", "BENT_CONNECTOR3"},
    MappingEntry{"bentConnector4", "BENT_CONNECTOR4"},
    MappingEntry{"bentConnector5", "BENT_CONNECTOR5"},
    MappingEntry{"curvedConnector2", "CURVED_CONNECTOR2"},
    MappingEntry{"curvedConnector3", "CURVED_CONNECTOR3"},
    MappingEntry{"curvedConnector4", "CURVED_CONNECTOR4"},
    MappingEntry{"curvedConnector5", "CURVED_CONNECTOR5"},
    MappingEntry{"callout1", "CALLOUT1"},
    MappingEntry{"callout2", "CALLOUT2"},
    MappingEntry{"callout3", "CALLOUT3"},
    MappingEntry{"accentCallout1", "CALLOUT_1_WITH_ACCENT"},
    MappingEntry{"accentCallout2", "CALLOUT_2_WITH_ACCENT"},
    MappingEntry{"accentCallout3", "CALLOUT_3_WITH_ACCENT"},
    MappingEntry{"borderCallout1", "CALLOUT_1_WITH_BORDER"},
    MappingEntry{"borderCallout2", "CALLOUT_2_WITH_BORDER"},
    MappingEntry{"borderCallout3", "CALLOUT_3_WITH_BORDER"},
    MappingEntry{"accentBorderCallout1", "CALLOUT_1_WITH_BORDER_AND_ACCENT"},
    MappingEntry{"accentBorderCallout2", "CALLOUT_2_WITH_BORDER_AND_ACCENT"},
    MappingEntry{"accentBorderCallout3", "CALLOUT_3_WITH_BORDER_AND_ACCENT"},
    MappingEntry{"wedgeRectCallout", "CALLOUT_WEDGE_RECTANGLE"},
    MappingEntry{"wedgeRoundRectCallout", "CALLOUT_WEDGE_ROUND_RECTANGLE"},
    MappingEntry{"wedgeEllipseCallout", "CALLOUT_WEDGE_ELLIPSE"},
    MappingEntry{"cloudCallout", "CALLOUT_CLOUD"},
    MappingEntry{"cloud", "CLOUD"},
    MappingEntry{"ribbon", "RIBBON"},
    MappingEntry{"ribbon2", "RIBBON2"},
    MappingEntry{"ellipseRibbon", "ELLIPSE_RIBBON"},
    MappingEntry{"ellipseRibbon2", "ELLIPSE_RIBBON2"},
    MappingEntry{"leftRightRibbon", "LEFT_RIGHT_RIBBON"},
    MappingEntry{"verticalScroll", "VERTICAL_SCROLL"},
    MappingEntry{"horizontalScroll", "HORIZONTAL_SCROLL"},
    MappingEntry{"wave", "WAVE"},
    MappingEntry{"doubleWave", "DOUBLE_WAVE"},
    MappingEntry{"plus", "PLUS"},
    MappingEntry{"flowChartProcess", "PROCESS_FLOW"},
    MappingEntry{"flowChartDecision", "DECISION_FLOW"},
    MappingEntry{"flowChartInputOutput", "INPUT_OUTPUT_FLOW"},
    MappingEntry{"flowChartPredefinedProcess", "PREDEFINED_PROCESS_FLOW"},
    MappingEntry{"flowChartInternalStorage", "INTERNAL_STORAGE_FLOW"},
    MappingEntry{"flowChartDocument", "DOCUMENT_FLOW"},
    MappingEntry{"flowChartMultidocument", "MULTI_DOCUMENT_FLOW"},
    MappingEntry{"flowChartTerminator", "TERMINATOR_FLOW"},
    MappingEntry{"flowChartPreparation", "PREPARATION_FLOW"},
    MappingEntry{"flowChartManualInput", "MANUAL_INPUT_FLOW"},
    MappingEntry{"flowChartManualOperation", "MANUAL_OPERATION_FLOW"},
    MappingEntry{"flowChartConnector", "CONNECTOR_FLOW"},
    MappingEntry{"flowChartPunchedCard", "PUNCHED_CARD_FLOW"},
    MappingEntry{"flowChartPunchedTape", "PUNCHED_TAPE_FLOW"},
    MappingEntry{"flowChartSummingJunction", "SUMMING_JUNCTION_FLOW"},
    MappingEntry{"flowChartOr", "OR_FLOW"},
    MappingEntry{"flowChartCollate", "COLLATE_FLOW"},
    MappingEntry{"flowChartSort", "SORT_FLOW"},
    MappingEntry{"flowChartExtract", "EXTRACT_FLOW"},
    MappingEntry{"flowChartMerge", "MERGE_FLOW"},
    MappingEntry{"flowChartOfflineStorage", "OFFLINE_STORAGE_FLOW"},
    MappingEntry{"flowChartOnlineStorage", "ONLINE_STORAGE_FLOW"},
    MappingEntry{"flowChartMagneticTape", "MAGNETIC_TAPE_FLOW"},
    MappingEntry{"flowChartMagneticDisk", "MAGNETIC_DISK_FLOW"},
    MappingEntry{"flowChartMagneticDrum", "MAGNETIC_DRUM_FLOW"},
    MappingEntry{"flowChartDisplay", "DISPLAY_FLOW"},
    MappingEntry{"flowChartDelay", "DELAY_FLOW"},
    MappingEntry{"flowChartAlternateProcess", "ALTERNATE_PROCESS_FLOW"},
    MappingEntry{"flowChartOffpageConnector", "OFF_PAGE_CONNECTOR_FLOW"},
    MappingEntry{"actionButtonBlank", "BLANK_BUTTON"},
    MappingEntry{"actionButtonHome", "HOME_BUTTON"},
    MappingEntry{"actionButtonHelp", "HELP_BUTTON"},
    MappingEntry{"actionButtonInformation", "INFORMATION_BUTTON"},
    MappingEntry{"actionButtonForwardNext", "FORWARD_OR_NEXT_BUTTON"},
    MappingEntry{"actionButtonBackPrevious", "BACK_OR_PREVIOUS_BUTTON"},
    MappingEntry{"actionButtonEnd", "END_BUTTON"},
    MappingEntry{"actionButtonBeginning", "BEGINNING_BUTTON"},
    MappingEntry{"actionButtonReturn", "RETURN_BUTTON"},
    MappingEntry{"actionButtonDocument", "DOCUMENT_BUTTON"},
    MappingEntry{"actionButtonSound", "SOUND_BUTTON"},
    MappingEntry{"actionButtonMovie", "MOVIE_BUTTON"},
    MappingEntry{"gear6", "GEAR6"},
    MappingEntry{"gear9", "GEAR9"},
    MappingEntry{"funnel", "FUNNEL"},
    MappingEntry{"mathPlus", "PLUS_MATH"},
    MappingEntry{"mathMinus", "MINUS_MATH"},
    MappingEntry{"mathMultiply", "MULTIPLY_MATH"},
    MappingEntry{"mathDivide", "DIVIDE_MATH"},
    MappingEntry{"mathEqual", "EQUAL_MATH"},
    MappingEntry{"mathNotEqual", "NOT_EQUAL_MATH"},
    MappingEntry{"cornerTabs", "CORNER_TABS"},
    MappingEntry{"squareTabs", "SQUARE_TABS"},
    MappingEntry{"plaqueTabs", "PLAQUE_TABS"},
    MappingEntry{"chartX", "CHART_X"},
    MappingEntry{"chartStar", "CHART_STAR"},
    MappingEntry{"chartPlus", "CHART_PLUS"},
};

/// Helper to create a string-keyed hash map. Uses std::string keys so that
/// std::string_view lookups work via transparent hashing.
struct StringHash {
    using is_transparent = void;
    std::size_t operator()(std::string_view sv) const noexcept {
        return std::hash<std::string_view>{}(sv);
    }
};

struct StringEqual {
    using is_transparent = void;
    bool operator()(std::string_view a, std::string_view b) const noexcept {
        return a == b;
    }
};

using LookupMap = std::unordered_map<std::string, std::string_view, StringHash, StringEqual>;

const LookupMap& prst_to_name_map() {
    static const auto* map = [] {
        auto* m = new LookupMap{};
        m->reserve(kMappingTable.size());
        for (const auto& entry : kMappingTable) {
            m->emplace(std::string(entry.prst), entry.shape_type_name);
        }
        return m;
    }();
    return *map;
}

const LookupMap& name_to_prst_map() {
    static const auto* map = [] {
        auto* m = new LookupMap{};
        m->reserve(kMappingTable.size());
        for (const auto& entry : kMappingTable) {
            m->emplace(std::string(entry.shape_type_name), entry.prst);
        }
        return m;
    }();
    return *map;
}

} // anonymous namespace

std::optional<std::string_view> ooxml_prst_to_shape_type_name(std::string_view prst) {
    const auto& map = prst_to_name_map();
    if (auto it = map.find(prst); it != map.end()) {
        return it->second;
    }
    return std::nullopt;
}

std::optional<std::string_view> shape_type_name_to_ooxml_prst(std::string_view name) {
    const auto& map = name_to_prst_map();
    if (auto it = map.find(name); it != map.end()) {
        return it->second;
    }
    return std::nullopt;
}

} // namespace Aspose::Slides::Foss::Internal::pptx::shape_type_mapping
