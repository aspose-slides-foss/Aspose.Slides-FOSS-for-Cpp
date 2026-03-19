// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents preset geometry of shapes.
enum class ShapeType {
    NOT_DEFINED,
    CUSTOM,
    LINE,
    LINE_INVERSE,
    TRIANGLE,
    RIGHT_TRIANGLE,
    RECTANGLE,
    DIAMOND,
    PARALLELOGRAM,
    TRAPEZOID,
    NON_ISOSCELES_TRAPEZOID,
    PENTAGON,
    HEXAGON,
    HEPTAGON,
    OCTAGON,
    DECAGON,
    DODECAGON,
    FOUR_POINTED_STAR,
    FIVE_POINTED_STAR,
    SIX_POINTED_STAR,
    SEVEN_POINTED_STAR,
    EIGHT_POINTED_STAR,
    TEN_POINTED_STAR,
    TWELVE_POINTED_STAR,
    SIXTEEN_POINTED_STAR,
    TWENTY_FOUR_POINTED_STAR,
    THIRTY_TWO_POINTED_STAR,
    ROUND_CORNER_RECTANGLE,
    ONE_ROUND_CORNER_RECTANGLE,
    TWO_SAMESIDE_ROUND_CORNER_RECTANGLE,
    TWO_DIAGONAL_ROUND_CORNER_RECTANGLE,
    ONE_SNIP_ONE_ROUND_CORNER_RECTANGLE,
    ONE_SNIP_CORNER_RECTANGLE,
    TWO_SAMESIDE_SNIP_CORNER_RECTANGLE,
    TWO_DIAGONAL_SNIP_CORNER_RECTANGLE,
    PLAQUE,
    ELLIPSE,
    TEARDROP,
    HOME_PLATE,
    CHEVRON,
    PIE_WEDGE,
    PIE,
    BLOCK_ARC,
    DONUT,
    NO_SMOKING,
    RIGHT_ARROW,
    LEFT_ARROW,
    UP_ARROW,
    DOWN_ARROW,
    STRIPED_RIGHT_ARROW,
    NOTCHED_RIGHT_ARROW,
    BENT_UP_ARROW,
    LEFT_RIGHT_ARROW,
    UP_DOWN_ARROW,
    LEFT_UP_ARROW,
    LEFT_RIGHT_UP_ARROW,
    QUAD_ARROW,
    CALLOUT_LEFT_ARROW,
    CALLOUT_RIGHT_ARROW,
    CALLOUT_UP_ARROW,
    CALLOUT_DOWN_ARROW,
    CALLOUT_LEFT_RIGHT_ARROW,
    CALLOUT_UP_DOWN_ARROW,
    CALLOUT_QUAD_ARROW,
    BENT_ARROW,
    U_TURN_ARROW,
    CIRCULAR_ARROW,
    LEFT_CIRCULAR_ARROW,
    LEFT_RIGHT_CIRCULAR_ARROW,
    CURVED_RIGHT_ARROW,
    CURVED_LEFT_ARROW,
    CURVED_UP_ARROW,
    CURVED_DOWN_ARROW,
    SWOOSH_ARROW,
    CUBE,
    CAN,
    LIGHTNING_BOLT,
    HEART,
    SUN,
    MOON,
    SMILEY_FACE,
    IRREGULAR_SEAL1,
    IRREGULAR_SEAL2,
    FOLDED_CORNER,
    BEVEL,
    FRAME,
    HALF_FRAME,
    CORNER,
    DIAGONAL_STRIPE,
    CHORD,
    CURVED_ARC,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_BRACE,
    RIGHT_BRACE,
    BRACKET_PAIR,
    BRACE_PAIR,
    STRAIGHT_CONNECTOR1,
    BENT_CONNECTOR2,
    BENT_CONNECTOR3,
    BENT_CONNECTOR4,
    BENT_CONNECTOR5,
    CURVED_CONNECTOR2,
    CURVED_CONNECTOR3,
    CURVED_CONNECTOR4,
    CURVED_CONNECTOR5,
    CALLOUT1,
    CALLOUT2,
    CALLOUT3,
    CALLOUT_1_WITH_ACCENT,
    CALLOUT_2_WITH_ACCENT,
    CALLOUT_3_WITH_ACCENT,
    CALLOUT_1_WITH_BORDER,
    CALLOUT_2_WITH_BORDER,
    CALLOUT_3_WITH_BORDER,
    CALLOUT_1_WITH_BORDER_AND_ACCENT,
    CALLOUT_2_WITH_BORDER_AND_ACCENT,
    CALLOUT_3_WITH_BORDER_AND_ACCENT,
    CALLOUT_WEDGE_RECTANGLE,
    CALLOUT_WEDGE_ROUND_RECTANGLE,
    CALLOUT_WEDGE_ELLIPSE,
    CALLOUT_CLOUD,
    CLOUD,
    RIBBON,
    RIBBON2,
    ELLIPSE_RIBBON,
    ELLIPSE_RIBBON2,
    LEFT_RIGHT_RIBBON,
    VERTICAL_SCROLL,
    HORIZONTAL_SCROLL,
    WAVE,
    DOUBLE_WAVE,
    PLUS,
    PROCESS_FLOW,
    DECISION_FLOW,
    INPUT_OUTPUT_FLOW,
    PREDEFINED_PROCESS_FLOW,
    INTERNAL_STORAGE_FLOW,
    DOCUMENT_FLOW,
    MULTI_DOCUMENT_FLOW,
    TERMINATOR_FLOW,
    PREPARATION_FLOW,
    MANUAL_INPUT_FLOW,
    MANUAL_OPERATION_FLOW,
    CONNECTOR_FLOW,
    PUNCHED_CARD_FLOW,
    PUNCHED_TAPE_FLOW,
    SUMMING_JUNCTION_FLOW,
    OR_FLOW,
    COLLATE_FLOW,
    SORT_FLOW,
    EXTRACT_FLOW,
    MERGE_FLOW,
    OFFLINE_STORAGE_FLOW,
    ONLINE_STORAGE_FLOW,
    MAGNETIC_TAPE_FLOW,
    MAGNETIC_DISK_FLOW,
    MAGNETIC_DRUM_FLOW,
    DISPLAY_FLOW,
    DELAY_FLOW,
    ALTERNATE_PROCESS_FLOW,
    OFF_PAGE_CONNECTOR_FLOW,
    BLANK_BUTTON,
    HOME_BUTTON,
    HELP_BUTTON,
    INFORMATION_BUTTON,
    FORWARD_OR_NEXT_BUTTON,
    BACK_OR_PREVIOUS_BUTTON,
    END_BUTTON,
    BEGINNING_BUTTON,
    RETURN_BUTTON,
    DOCUMENT_BUTTON,
    SOUND_BUTTON,
    MOVIE_BUTTON,
    GEAR6,
    GEAR9,
    FUNNEL,
    PLUS_MATH,
    MINUS_MATH,
    MULTIPLY_MATH,
    DIVIDE_MATH,
    EQUAL_MATH,
    NOT_EQUAL_MATH,
    CORNER_TABS,
    SQUARE_TABS,
    PLAQUE_TABS,
    CHART_X,
    CHART_STAR,
    CHART_PLUS,
};

/// Returns the string representation of a ShapeType value.
constexpr std::string_view to_string_view(ShapeType value) {
    switch (value) {
        case ShapeType::NOT_DEFINED: return "NotDefined";
        case ShapeType::CUSTOM: return "Custom";
        case ShapeType::LINE: return "Line";
        case ShapeType::LINE_INVERSE: return "LineInverse";
        case ShapeType::TRIANGLE: return "Triangle";
        case ShapeType::RIGHT_TRIANGLE: return "RightTriangle";
        case ShapeType::RECTANGLE: return "Rectangle";
        case ShapeType::DIAMOND: return "Diamond";
        case ShapeType::PARALLELOGRAM: return "Parallelogram";
        case ShapeType::TRAPEZOID: return "Trapezoid";
        case ShapeType::NON_ISOSCELES_TRAPEZOID: return "NonIsoscelesTrapezoid";
        case ShapeType::PENTAGON: return "Pentagon";
        case ShapeType::HEXAGON: return "Hexagon";
        case ShapeType::HEPTAGON: return "Heptagon";
        case ShapeType::OCTAGON: return "Octagon";
        case ShapeType::DECAGON: return "Decagon";
        case ShapeType::DODECAGON: return "Dodecagon";
        case ShapeType::FOUR_POINTED_STAR: return "FourPointedStar";
        case ShapeType::FIVE_POINTED_STAR: return "FivePointedStar";
        case ShapeType::SIX_POINTED_STAR: return "SixPointedStar";
        case ShapeType::SEVEN_POINTED_STAR: return "SevenPointedStar";
        case ShapeType::EIGHT_POINTED_STAR: return "EightPointedStar";
        case ShapeType::TEN_POINTED_STAR: return "TenPointedStar";
        case ShapeType::TWELVE_POINTED_STAR: return "TwelvePointedStar";
        case ShapeType::SIXTEEN_POINTED_STAR: return "SixteenPointedStar";
        case ShapeType::TWENTY_FOUR_POINTED_STAR: return "TwentyFourPointedStar";
        case ShapeType::THIRTY_TWO_POINTED_STAR: return "ThirtyTwoPointedStar";
        case ShapeType::ROUND_CORNER_RECTANGLE: return "RoundCornerRectangle";
        case ShapeType::ONE_ROUND_CORNER_RECTANGLE: return "OneRoundCornerRectangle";
        case ShapeType::TWO_SAMESIDE_ROUND_CORNER_RECTANGLE: return "TwoSamesideRoundCornerRectangle";
        case ShapeType::TWO_DIAGONAL_ROUND_CORNER_RECTANGLE: return "TwoDiagonalRoundCornerRectangle";
        case ShapeType::ONE_SNIP_ONE_ROUND_CORNER_RECTANGLE: return "OneSnipOneRoundCornerRectangle";
        case ShapeType::ONE_SNIP_CORNER_RECTANGLE: return "OneSnipCornerRectangle";
        case ShapeType::TWO_SAMESIDE_SNIP_CORNER_RECTANGLE: return "TwoSamesideSnipCornerRectangle";
        case ShapeType::TWO_DIAGONAL_SNIP_CORNER_RECTANGLE: return "TwoDiagonalSnipCornerRectangle";
        case ShapeType::PLAQUE: return "Plaque";
        case ShapeType::ELLIPSE: return "Ellipse";
        case ShapeType::TEARDROP: return "Teardrop";
        case ShapeType::HOME_PLATE: return "HomePlate";
        case ShapeType::CHEVRON: return "Chevron";
        case ShapeType::PIE_WEDGE: return "PieWedge";
        case ShapeType::PIE: return "Pie";
        case ShapeType::BLOCK_ARC: return "BlockArc";
        case ShapeType::DONUT: return "Donut";
        case ShapeType::NO_SMOKING: return "NoSmoking";
        case ShapeType::RIGHT_ARROW: return "RightArrow";
        case ShapeType::LEFT_ARROW: return "LeftArrow";
        case ShapeType::UP_ARROW: return "UpArrow";
        case ShapeType::DOWN_ARROW: return "DownArrow";
        case ShapeType::STRIPED_RIGHT_ARROW: return "StripedRightArrow";
        case ShapeType::NOTCHED_RIGHT_ARROW: return "NotchedRightArrow";
        case ShapeType::BENT_UP_ARROW: return "BentUpArrow";
        case ShapeType::LEFT_RIGHT_ARROW: return "LeftRightArrow";
        case ShapeType::UP_DOWN_ARROW: return "UpDownArrow";
        case ShapeType::LEFT_UP_ARROW: return "LeftUpArrow";
        case ShapeType::LEFT_RIGHT_UP_ARROW: return "LeftRightUpArrow";
        case ShapeType::QUAD_ARROW: return "QuadArrow";
        case ShapeType::CALLOUT_LEFT_ARROW: return "CalloutLeftArrow";
        case ShapeType::CALLOUT_RIGHT_ARROW: return "CalloutRightArrow";
        case ShapeType::CALLOUT_UP_ARROW: return "CalloutUpArrow";
        case ShapeType::CALLOUT_DOWN_ARROW: return "CalloutDownArrow";
        case ShapeType::CALLOUT_LEFT_RIGHT_ARROW: return "CalloutLeftRightArrow";
        case ShapeType::CALLOUT_UP_DOWN_ARROW: return "CalloutUpDownArrow";
        case ShapeType::CALLOUT_QUAD_ARROW: return "CalloutQuadArrow";
        case ShapeType::BENT_ARROW: return "BentArrow";
        case ShapeType::U_TURN_ARROW: return "UTurnArrow";
        case ShapeType::CIRCULAR_ARROW: return "CircularArrow";
        case ShapeType::LEFT_CIRCULAR_ARROW: return "LeftCircularArrow";
        case ShapeType::LEFT_RIGHT_CIRCULAR_ARROW: return "LeftRightCircularArrow";
        case ShapeType::CURVED_RIGHT_ARROW: return "CurvedRightArrow";
        case ShapeType::CURVED_LEFT_ARROW: return "CurvedLeftArrow";
        case ShapeType::CURVED_UP_ARROW: return "CurvedUpArrow";
        case ShapeType::CURVED_DOWN_ARROW: return "CurvedDownArrow";
        case ShapeType::SWOOSH_ARROW: return "SwooshArrow";
        case ShapeType::CUBE: return "Cube";
        case ShapeType::CAN: return "Can";
        case ShapeType::LIGHTNING_BOLT: return "LightningBolt";
        case ShapeType::HEART: return "Heart";
        case ShapeType::SUN: return "Sun";
        case ShapeType::MOON: return "Moon";
        case ShapeType::SMILEY_FACE: return "SmileyFace";
        case ShapeType::IRREGULAR_SEAL1: return "IrregularSeal1";
        case ShapeType::IRREGULAR_SEAL2: return "IrregularSeal2";
        case ShapeType::FOLDED_CORNER: return "FoldedCorner";
        case ShapeType::BEVEL: return "Bevel";
        case ShapeType::FRAME: return "Frame";
        case ShapeType::HALF_FRAME: return "HalfFrame";
        case ShapeType::CORNER: return "Corner";
        case ShapeType::DIAGONAL_STRIPE: return "DiagonalStripe";
        case ShapeType::CHORD: return "Chord";
        case ShapeType::CURVED_ARC: return "CurvedArc";
        case ShapeType::LEFT_BRACKET: return "LeftBracket";
        case ShapeType::RIGHT_BRACKET: return "RightBracket";
        case ShapeType::LEFT_BRACE: return "LeftBrace";
        case ShapeType::RIGHT_BRACE: return "RightBrace";
        case ShapeType::BRACKET_PAIR: return "BracketPair";
        case ShapeType::BRACE_PAIR: return "BracePair";
        case ShapeType::STRAIGHT_CONNECTOR1: return "StraightConnector1";
        case ShapeType::BENT_CONNECTOR2: return "BentConnector2";
        case ShapeType::BENT_CONNECTOR3: return "BentConnector3";
        case ShapeType::BENT_CONNECTOR4: return "BentConnector4";
        case ShapeType::BENT_CONNECTOR5: return "BentConnector5";
        case ShapeType::CURVED_CONNECTOR2: return "CurvedConnector2";
        case ShapeType::CURVED_CONNECTOR3: return "CurvedConnector3";
        case ShapeType::CURVED_CONNECTOR4: return "CurvedConnector4";
        case ShapeType::CURVED_CONNECTOR5: return "CurvedConnector5";
        case ShapeType::CALLOUT1: return "Callout1";
        case ShapeType::CALLOUT2: return "Callout2";
        case ShapeType::CALLOUT3: return "Callout3";
        case ShapeType::CALLOUT_1_WITH_ACCENT: return "Callout1WithAccent";
        case ShapeType::CALLOUT_2_WITH_ACCENT: return "Callout2WithAccent";
        case ShapeType::CALLOUT_3_WITH_ACCENT: return "Callout3WithAccent";
        case ShapeType::CALLOUT_1_WITH_BORDER: return "Callout1WithBorder";
        case ShapeType::CALLOUT_2_WITH_BORDER: return "Callout2WithBorder";
        case ShapeType::CALLOUT_3_WITH_BORDER: return "Callout3WithBorder";
        case ShapeType::CALLOUT_1_WITH_BORDER_AND_ACCENT: return "Callout1WithBorderAndAccent";
        case ShapeType::CALLOUT_2_WITH_BORDER_AND_ACCENT: return "Callout2WithBorderAndAccent";
        case ShapeType::CALLOUT_3_WITH_BORDER_AND_ACCENT: return "Callout3WithBorderAndAccent";
        case ShapeType::CALLOUT_WEDGE_RECTANGLE: return "CalloutWedgeRectangle";
        case ShapeType::CALLOUT_WEDGE_ROUND_RECTANGLE: return "CalloutWedgeRoundRectangle";
        case ShapeType::CALLOUT_WEDGE_ELLIPSE: return "CalloutWedgeEllipse";
        case ShapeType::CALLOUT_CLOUD: return "CalloutCloud";
        case ShapeType::CLOUD: return "Cloud";
        case ShapeType::RIBBON: return "Ribbon";
        case ShapeType::RIBBON2: return "Ribbon2";
        case ShapeType::ELLIPSE_RIBBON: return "EllipseRibbon";
        case ShapeType::ELLIPSE_RIBBON2: return "EllipseRibbon2";
        case ShapeType::LEFT_RIGHT_RIBBON: return "LeftRightRibbon";
        case ShapeType::VERTICAL_SCROLL: return "VerticalScroll";
        case ShapeType::HORIZONTAL_SCROLL: return "HorizontalScroll";
        case ShapeType::WAVE: return "Wave";
        case ShapeType::DOUBLE_WAVE: return "DoubleWave";
        case ShapeType::PLUS: return "Plus";
        case ShapeType::PROCESS_FLOW: return "ProcessFlow";
        case ShapeType::DECISION_FLOW: return "DecisionFlow";
        case ShapeType::INPUT_OUTPUT_FLOW: return "InputOutputFlow";
        case ShapeType::PREDEFINED_PROCESS_FLOW: return "PredefinedProcessFlow";
        case ShapeType::INTERNAL_STORAGE_FLOW: return "InternalStorageFlow";
        case ShapeType::DOCUMENT_FLOW: return "DocumentFlow";
        case ShapeType::MULTI_DOCUMENT_FLOW: return "MultiDocumentFlow";
        case ShapeType::TERMINATOR_FLOW: return "TerminatorFlow";
        case ShapeType::PREPARATION_FLOW: return "PreparationFlow";
        case ShapeType::MANUAL_INPUT_FLOW: return "ManualInputFlow";
        case ShapeType::MANUAL_OPERATION_FLOW: return "ManualOperationFlow";
        case ShapeType::CONNECTOR_FLOW: return "ConnectorFlow";
        case ShapeType::PUNCHED_CARD_FLOW: return "PunchedCardFlow";
        case ShapeType::PUNCHED_TAPE_FLOW: return "PunchedTapeFlow";
        case ShapeType::SUMMING_JUNCTION_FLOW: return "SummingJunctionFlow";
        case ShapeType::OR_FLOW: return "OrFlow";
        case ShapeType::COLLATE_FLOW: return "CollateFlow";
        case ShapeType::SORT_FLOW: return "SortFlow";
        case ShapeType::EXTRACT_FLOW: return "ExtractFlow";
        case ShapeType::MERGE_FLOW: return "MergeFlow";
        case ShapeType::OFFLINE_STORAGE_FLOW: return "OfflineStorageFlow";
        case ShapeType::ONLINE_STORAGE_FLOW: return "OnlineStorageFlow";
        case ShapeType::MAGNETIC_TAPE_FLOW: return "MagneticTapeFlow";
        case ShapeType::MAGNETIC_DISK_FLOW: return "MagneticDiskFlow";
        case ShapeType::MAGNETIC_DRUM_FLOW: return "MagneticDrumFlow";
        case ShapeType::DISPLAY_FLOW: return "DisplayFlow";
        case ShapeType::DELAY_FLOW: return "DelayFlow";
        case ShapeType::ALTERNATE_PROCESS_FLOW: return "AlternateProcessFlow";
        case ShapeType::OFF_PAGE_CONNECTOR_FLOW: return "OffPageConnectorFlow";
        case ShapeType::BLANK_BUTTON: return "BlankButton";
        case ShapeType::HOME_BUTTON: return "HomeButton";
        case ShapeType::HELP_BUTTON: return "HelpButton";
        case ShapeType::INFORMATION_BUTTON: return "InformationButton";
        case ShapeType::FORWARD_OR_NEXT_BUTTON: return "ForwardOrNextButton";
        case ShapeType::BACK_OR_PREVIOUS_BUTTON: return "BackOrPreviousButton";
        case ShapeType::END_BUTTON: return "EndButton";
        case ShapeType::BEGINNING_BUTTON: return "BeginningButton";
        case ShapeType::RETURN_BUTTON: return "ReturnButton";
        case ShapeType::DOCUMENT_BUTTON: return "DocumentButton";
        case ShapeType::SOUND_BUTTON: return "SoundButton";
        case ShapeType::MOVIE_BUTTON: return "MovieButton";
        case ShapeType::GEAR6: return "Gear6";
        case ShapeType::GEAR9: return "Gear9";
        case ShapeType::FUNNEL: return "Funnel";
        case ShapeType::PLUS_MATH: return "PlusMath";
        case ShapeType::MINUS_MATH: return "MinusMath";
        case ShapeType::MULTIPLY_MATH: return "MultiplyMath";
        case ShapeType::DIVIDE_MATH: return "DivideMath";
        case ShapeType::EQUAL_MATH: return "EqualMath";
        case ShapeType::NOT_EQUAL_MATH: return "NotEqualMath";
        case ShapeType::CORNER_TABS: return "CornerTabs";
        case ShapeType::SQUARE_TABS: return "SquareTabs";
        case ShapeType::PLAQUE_TABS: return "PlaqueTabs";
        case ShapeType::CHART_X: return "ChartX";
        case ShapeType::CHART_STAR: return "ChartStar";
        case ShapeType::CHART_PLUS: return "ChartPlus";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
