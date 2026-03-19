// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/shape_collection.h>

#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/column.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/group_shape.h>
#include <Aspose/Slides/Foss/picture_frame.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/row.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/table.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>
#include "_internal/pptx/shape_factory.h"

namespace Aspose::Slides::Foss {

namespace pptx = Internal::pptx;

// ===========================================================================
// Anonymous helpers
// ===========================================================================
namespace {

// ---------------------------------------------------------------------------
// ShapeType -> OOXML preset geometry name
// ---------------------------------------------------------------------------

const char* shape_type_to_prst(ShapeType type) {
    switch (type) {
        case ShapeType::LINE:                       return "line";
        case ShapeType::LINE_INVERSE:               return "lineInv";
        case ShapeType::TRIANGLE:                   return "triangle";
        case ShapeType::RIGHT_TRIANGLE:             return "rtTriangle";
        case ShapeType::RECTANGLE:                  return "rect";
        case ShapeType::DIAMOND:                    return "diamond";
        case ShapeType::PARALLELOGRAM:              return "parallelogram";
        case ShapeType::TRAPEZOID:                  return "trapezoid";
        case ShapeType::NON_ISOSCELES_TRAPEZOID:    return "nonIsoscelesTrapezoid";
        case ShapeType::PENTAGON:                   return "pentagon";
        case ShapeType::HEXAGON:                    return "hexagon";
        case ShapeType::HEPTAGON:                   return "heptagon";
        case ShapeType::OCTAGON:                    return "octagon";
        case ShapeType::DECAGON:                    return "decagon";
        case ShapeType::DODECAGON:                  return "dodecagon";
        case ShapeType::FOUR_POINTED_STAR:          return "star4";
        case ShapeType::FIVE_POINTED_STAR:          return "star5";
        case ShapeType::SIX_POINTED_STAR:           return "star6";
        case ShapeType::SEVEN_POINTED_STAR:         return "star7";
        case ShapeType::EIGHT_POINTED_STAR:         return "star8";
        case ShapeType::TEN_POINTED_STAR:           return "star10";
        case ShapeType::TWELVE_POINTED_STAR:        return "star12";
        case ShapeType::SIXTEEN_POINTED_STAR:       return "star16";
        case ShapeType::TWENTY_FOUR_POINTED_STAR:   return "star24";
        case ShapeType::THIRTY_TWO_POINTED_STAR:    return "star32";
        case ShapeType::ROUND_CORNER_RECTANGLE:     return "roundRect";
        case ShapeType::ONE_ROUND_CORNER_RECTANGLE: return "round1Rect";
        case ShapeType::TWO_SAMESIDE_ROUND_CORNER_RECTANGLE: return "round2SameRect";
        case ShapeType::TWO_DIAGONAL_ROUND_CORNER_RECTANGLE: return "round2DiagRect";
        case ShapeType::ONE_SNIP_ONE_ROUND_CORNER_RECTANGLE: return "snipRoundRect";
        case ShapeType::ONE_SNIP_CORNER_RECTANGLE:  return "snip1Rect";
        case ShapeType::TWO_SAMESIDE_SNIP_CORNER_RECTANGLE: return "snip2SameRect";
        case ShapeType::TWO_DIAGONAL_SNIP_CORNER_RECTANGLE: return "snip2DiagRect";
        case ShapeType::PLAQUE:                     return "plaque";
        case ShapeType::ELLIPSE:                    return "ellipse";
        case ShapeType::TEARDROP:                   return "teardrop";
        case ShapeType::HOME_PLATE:                 return "homePlate";
        case ShapeType::CHEVRON:                    return "chevron";
        case ShapeType::PIE_WEDGE:                  return "pieWedge";
        case ShapeType::PIE:                        return "pie";
        case ShapeType::BLOCK_ARC:                  return "blockArc";
        case ShapeType::DONUT:                      return "donut";
        case ShapeType::NO_SMOKING:                 return "noSmoking";
        case ShapeType::RIGHT_ARROW:                return "rightArrow";
        case ShapeType::LEFT_ARROW:                 return "leftArrow";
        case ShapeType::UP_ARROW:                   return "upArrow";
        case ShapeType::DOWN_ARROW:                 return "downArrow";
        case ShapeType::STRIPED_RIGHT_ARROW:        return "stripedRightArrow";
        case ShapeType::NOTCHED_RIGHT_ARROW:        return "notchedRightArrow";
        case ShapeType::BENT_UP_ARROW:              return "bentUpArrow";
        case ShapeType::LEFT_RIGHT_ARROW:           return "leftRightArrow";
        case ShapeType::UP_DOWN_ARROW:              return "upDownArrow";
        case ShapeType::LEFT_UP_ARROW:              return "leftUpArrow";
        case ShapeType::LEFT_RIGHT_UP_ARROW:        return "leftRightUpArrow";
        case ShapeType::QUAD_ARROW:                 return "quadArrow";
        case ShapeType::CALLOUT_LEFT_ARROW:         return "leftArrowCallout";
        case ShapeType::CALLOUT_RIGHT_ARROW:        return "rightArrowCallout";
        case ShapeType::CALLOUT_UP_ARROW:           return "upArrowCallout";
        case ShapeType::CALLOUT_DOWN_ARROW:         return "downArrowCallout";
        case ShapeType::CALLOUT_LEFT_RIGHT_ARROW:   return "leftRightArrowCallout";
        case ShapeType::CALLOUT_UP_DOWN_ARROW:      return "upDownArrowCallout";
        case ShapeType::CALLOUT_QUAD_ARROW:         return "quadArrowCallout";
        case ShapeType::BENT_ARROW:                 return "bentArrow";
        case ShapeType::U_TURN_ARROW:               return "uturnArrow";
        case ShapeType::CIRCULAR_ARROW:             return "circularArrow";
        case ShapeType::LEFT_CIRCULAR_ARROW:        return "leftCircularArrow";
        case ShapeType::LEFT_RIGHT_CIRCULAR_ARROW:  return "leftRightCircularArrow";
        case ShapeType::CURVED_RIGHT_ARROW:         return "curvedRightArrow";
        case ShapeType::CURVED_LEFT_ARROW:          return "curvedLeftArrow";
        case ShapeType::CURVED_UP_ARROW:            return "curvedUpArrow";
        case ShapeType::CURVED_DOWN_ARROW:          return "curvedDownArrow";
        case ShapeType::SWOOSH_ARROW:               return "swooshArrow";
        case ShapeType::CUBE:                       return "cube";
        case ShapeType::CAN:                        return "can";
        case ShapeType::LIGHTNING_BOLT:             return "lightningBolt";
        case ShapeType::HEART:                      return "heart";
        case ShapeType::SUN:                        return "sun";
        case ShapeType::MOON:                       return "moon";
        case ShapeType::SMILEY_FACE:                return "smileyFace";
        case ShapeType::IRREGULAR_SEAL1:            return "irregularSeal1";
        case ShapeType::IRREGULAR_SEAL2:            return "irregularSeal2";
        case ShapeType::FOLDED_CORNER:              return "foldedCorner";
        case ShapeType::BEVEL:                      return "bevel";
        case ShapeType::FRAME:                      return "frame";
        case ShapeType::HALF_FRAME:                 return "halfFrame";
        case ShapeType::CORNER:                     return "corner";
        case ShapeType::DIAGONAL_STRIPE:            return "diagStripe";
        case ShapeType::CHORD:                      return "chord";
        case ShapeType::CURVED_ARC:                 return "arc";
        case ShapeType::LEFT_BRACKET:               return "leftBracket";
        case ShapeType::RIGHT_BRACKET:              return "rightBracket";
        case ShapeType::LEFT_BRACE:                 return "leftBrace";
        case ShapeType::RIGHT_BRACE:                return "rightBrace";
        case ShapeType::BRACKET_PAIR:               return "bracketPair";
        case ShapeType::BRACE_PAIR:                 return "bracePair";
        case ShapeType::STRAIGHT_CONNECTOR1:        return "straightConnector1";
        case ShapeType::BENT_CONNECTOR2:            return "bentConnector2";
        case ShapeType::BENT_CONNECTOR3:            return "bentConnector3";
        case ShapeType::BENT_CONNECTOR4:            return "bentConnector4";
        case ShapeType::BENT_CONNECTOR5:            return "bentConnector5";
        case ShapeType::CURVED_CONNECTOR2:          return "curvedConnector2";
        case ShapeType::CURVED_CONNECTOR3:          return "curvedConnector3";
        case ShapeType::CURVED_CONNECTOR4:          return "curvedConnector4";
        case ShapeType::CURVED_CONNECTOR5:          return "curvedConnector5";
        case ShapeType::CALLOUT1:                   return "callout1";
        case ShapeType::CALLOUT2:                   return "callout2";
        case ShapeType::CALLOUT3:                   return "callout3";
        case ShapeType::CALLOUT_1_WITH_ACCENT:      return "accentCallout1";
        case ShapeType::CALLOUT_2_WITH_ACCENT:      return "accentCallout2";
        case ShapeType::CALLOUT_3_WITH_ACCENT:      return "accentCallout3";
        case ShapeType::CALLOUT_1_WITH_BORDER:      return "borderCallout1";
        case ShapeType::CALLOUT_2_WITH_BORDER:      return "borderCallout2";
        case ShapeType::CALLOUT_3_WITH_BORDER:      return "borderCallout3";
        case ShapeType::CALLOUT_1_WITH_BORDER_AND_ACCENT: return "accentBorderCallout1";
        case ShapeType::CALLOUT_2_WITH_BORDER_AND_ACCENT: return "accentBorderCallout2";
        case ShapeType::CALLOUT_3_WITH_BORDER_AND_ACCENT: return "accentBorderCallout3";
        case ShapeType::CALLOUT_WEDGE_RECTANGLE:    return "wedgeRectCallout";
        case ShapeType::CALLOUT_WEDGE_ROUND_RECTANGLE: return "wedgeRoundRectCallout";
        case ShapeType::CALLOUT_WEDGE_ELLIPSE:      return "wedgeEllipseCallout";
        case ShapeType::CALLOUT_CLOUD:              return "cloudCallout";
        case ShapeType::CLOUD:                      return "cloud";
        case ShapeType::RIBBON:                     return "ribbon";
        case ShapeType::RIBBON2:                    return "ribbon2";
        case ShapeType::ELLIPSE_RIBBON:             return "ellipseRibbon";
        case ShapeType::ELLIPSE_RIBBON2:            return "ellipseRibbon2";
        case ShapeType::LEFT_RIGHT_RIBBON:          return "leftRightRibbon";
        case ShapeType::VERTICAL_SCROLL:            return "verticalScroll";
        case ShapeType::HORIZONTAL_SCROLL:          return "horizontalScroll";
        case ShapeType::WAVE:                       return "wave";
        case ShapeType::DOUBLE_WAVE:                return "doubleWave";
        case ShapeType::PLUS:                       return "mathPlus";
        case ShapeType::PROCESS_FLOW:               return "flowChartProcess";
        case ShapeType::DECISION_FLOW:              return "flowChartDecision";
        case ShapeType::INPUT_OUTPUT_FLOW:          return "flowChartInputOutput";
        case ShapeType::PREDEFINED_PROCESS_FLOW:    return "flowChartPredefinedProcess";
        case ShapeType::INTERNAL_STORAGE_FLOW:      return "flowChartInternalStorage";
        case ShapeType::DOCUMENT_FLOW:              return "flowChartDocument";
        case ShapeType::MULTI_DOCUMENT_FLOW:        return "flowChartMultidocument";
        case ShapeType::TERMINATOR_FLOW:            return "flowChartTerminator";
        case ShapeType::PREPARATION_FLOW:           return "flowChartPreparation";
        case ShapeType::MANUAL_INPUT_FLOW:          return "flowChartManualInput";
        case ShapeType::MANUAL_OPERATION_FLOW:      return "flowChartManualOperation";
        case ShapeType::CONNECTOR_FLOW:             return "flowChartConnector";
        case ShapeType::PUNCHED_CARD_FLOW:          return "flowChartPunchedCard";
        case ShapeType::PUNCHED_TAPE_FLOW:          return "flowChartPunchedTape";
        case ShapeType::SUMMING_JUNCTION_FLOW:      return "flowChartSummingJunction";
        case ShapeType::OR_FLOW:                    return "flowChartOr";
        case ShapeType::COLLATE_FLOW:               return "flowChartCollate";
        case ShapeType::SORT_FLOW:                  return "flowChartSort";
        case ShapeType::EXTRACT_FLOW:               return "flowChartExtract";
        case ShapeType::MERGE_FLOW:                 return "flowChartMerge";
        case ShapeType::OFFLINE_STORAGE_FLOW:       return "flowChartOfflineStorage";
        case ShapeType::ONLINE_STORAGE_FLOW:        return "flowChartOnlineStorage";
        case ShapeType::MAGNETIC_TAPE_FLOW:         return "flowChartMagneticTape";
        case ShapeType::MAGNETIC_DISK_FLOW:         return "flowChartMagneticDisk";
        case ShapeType::MAGNETIC_DRUM_FLOW:         return "flowChartMagneticDrum";
        case ShapeType::DISPLAY_FLOW:               return "flowChartDisplay";
        case ShapeType::DELAY_FLOW:                 return "flowChartDelay";
        case ShapeType::ALTERNATE_PROCESS_FLOW:     return "flowChartAlternateProcess";
        case ShapeType::OFF_PAGE_CONNECTOR_FLOW:    return "flowChartOffpageConnector";
        case ShapeType::BLANK_BUTTON:               return "actionButtonBlank";
        case ShapeType::HOME_BUTTON:                return "actionButtonHome";
        case ShapeType::HELP_BUTTON:                return "actionButtonHelp";
        case ShapeType::INFORMATION_BUTTON:         return "actionButtonInformation";
        case ShapeType::FORWARD_OR_NEXT_BUTTON:     return "actionButtonForwardNext";
        case ShapeType::BACK_OR_PREVIOUS_BUTTON:    return "actionButtonBackPrevious";
        case ShapeType::END_BUTTON:                 return "actionButtonEnd";
        case ShapeType::BEGINNING_BUTTON:           return "actionButtonBeginning";
        case ShapeType::RETURN_BUTTON:              return "actionButtonReturn";
        case ShapeType::DOCUMENT_BUTTON:            return "actionButtonDocument";
        case ShapeType::SOUND_BUTTON:               return "actionButtonSound";
        case ShapeType::MOVIE_BUTTON:               return "actionButtonMovie";
        case ShapeType::GEAR6:                      return "gear6";
        case ShapeType::GEAR9:                      return "gear9";
        case ShapeType::FUNNEL:                     return "funnel";
        case ShapeType::PLUS_MATH:                  return "mathPlus";
        case ShapeType::MINUS_MATH:                 return "mathMinus";
        case ShapeType::MULTIPLY_MATH:              return "mathMultiply";
        case ShapeType::DIVIDE_MATH:                return "mathDivide";
        case ShapeType::EQUAL_MATH:                 return "mathEqual";
        case ShapeType::NOT_EQUAL_MATH:             return "mathNotEqual";
        case ShapeType::CORNER_TABS:                return "cornerTabs";
        case ShapeType::SQUARE_TABS:                return "squareTabs";
        case ShapeType::PLAQUE_TABS:                return "plaqueTabs";
        case ShapeType::CHART_X:                    return "chartX";
        case ShapeType::CHART_STAR:                 return "chartStar";
        case ShapeType::CHART_PLUS:                 return "chartPlus";
        default:                                    return nullptr;
    }
}

// ---------------------------------------------------------------------------
// OOXML preset geometry name -> ShapeType (reverse of shape_type_to_prst)
// ---------------------------------------------------------------------------

ShapeType prst_to_shape_type(std::string_view prst) {
    static const std::unordered_map<std::string_view, ShapeType> map = {
        {"line", ShapeType::LINE},
        {"lineInv", ShapeType::LINE_INVERSE},
        {"triangle", ShapeType::TRIANGLE},
        {"rtTriangle", ShapeType::RIGHT_TRIANGLE},
        {"rect", ShapeType::RECTANGLE},
        {"diamond", ShapeType::DIAMOND},
        {"parallelogram", ShapeType::PARALLELOGRAM},
        {"trapezoid", ShapeType::TRAPEZOID},
        {"nonIsoscelesTrapezoid", ShapeType::NON_ISOSCELES_TRAPEZOID},
        {"pentagon", ShapeType::PENTAGON},
        {"hexagon", ShapeType::HEXAGON},
        {"heptagon", ShapeType::HEPTAGON},
        {"octagon", ShapeType::OCTAGON},
        {"decagon", ShapeType::DECAGON},
        {"dodecagon", ShapeType::DODECAGON},
        {"star4", ShapeType::FOUR_POINTED_STAR},
        {"star5", ShapeType::FIVE_POINTED_STAR},
        {"star6", ShapeType::SIX_POINTED_STAR},
        {"star7", ShapeType::SEVEN_POINTED_STAR},
        {"star8", ShapeType::EIGHT_POINTED_STAR},
        {"star10", ShapeType::TEN_POINTED_STAR},
        {"star12", ShapeType::TWELVE_POINTED_STAR},
        {"star16", ShapeType::SIXTEEN_POINTED_STAR},
        {"star24", ShapeType::TWENTY_FOUR_POINTED_STAR},
        {"star32", ShapeType::THIRTY_TWO_POINTED_STAR},
        {"roundRect", ShapeType::ROUND_CORNER_RECTANGLE},
        {"round1Rect", ShapeType::ONE_ROUND_CORNER_RECTANGLE},
        {"round2SameRect", ShapeType::TWO_SAMESIDE_ROUND_CORNER_RECTANGLE},
        {"round2DiagRect", ShapeType::TWO_DIAGONAL_ROUND_CORNER_RECTANGLE},
        {"snipRoundRect", ShapeType::ONE_SNIP_ONE_ROUND_CORNER_RECTANGLE},
        {"snip1Rect", ShapeType::ONE_SNIP_CORNER_RECTANGLE},
        {"snip2SameRect", ShapeType::TWO_SAMESIDE_SNIP_CORNER_RECTANGLE},
        {"snip2DiagRect", ShapeType::TWO_DIAGONAL_SNIP_CORNER_RECTANGLE},
        {"plaque", ShapeType::PLAQUE},
        {"ellipse", ShapeType::ELLIPSE},
        {"teardrop", ShapeType::TEARDROP},
        {"homePlate", ShapeType::HOME_PLATE},
        {"chevron", ShapeType::CHEVRON},
        {"pieWedge", ShapeType::PIE_WEDGE},
        {"pie", ShapeType::PIE},
        {"blockArc", ShapeType::BLOCK_ARC},
        {"donut", ShapeType::DONUT},
        {"noSmoking", ShapeType::NO_SMOKING},
        {"rightArrow", ShapeType::RIGHT_ARROW},
        {"leftArrow", ShapeType::LEFT_ARROW},
        {"upArrow", ShapeType::UP_ARROW},
        {"downArrow", ShapeType::DOWN_ARROW},
        {"stripedRightArrow", ShapeType::STRIPED_RIGHT_ARROW},
        {"notchedRightArrow", ShapeType::NOTCHED_RIGHT_ARROW},
        {"bentUpArrow", ShapeType::BENT_UP_ARROW},
        {"leftRightArrow", ShapeType::LEFT_RIGHT_ARROW},
        {"upDownArrow", ShapeType::UP_DOWN_ARROW},
        {"leftUpArrow", ShapeType::LEFT_UP_ARROW},
        {"leftRightUpArrow", ShapeType::LEFT_RIGHT_UP_ARROW},
        {"quadArrow", ShapeType::QUAD_ARROW},
        {"leftArrowCallout", ShapeType::CALLOUT_LEFT_ARROW},
        {"rightArrowCallout", ShapeType::CALLOUT_RIGHT_ARROW},
        {"upArrowCallout", ShapeType::CALLOUT_UP_ARROW},
        {"downArrowCallout", ShapeType::CALLOUT_DOWN_ARROW},
        {"leftRightArrowCallout", ShapeType::CALLOUT_LEFT_RIGHT_ARROW},
        {"upDownArrowCallout", ShapeType::CALLOUT_UP_DOWN_ARROW},
        {"quadArrowCallout", ShapeType::CALLOUT_QUAD_ARROW},
        {"bentArrow", ShapeType::BENT_ARROW},
        {"uturnArrow", ShapeType::U_TURN_ARROW},
        {"circularArrow", ShapeType::CIRCULAR_ARROW},
        {"leftCircularArrow", ShapeType::LEFT_CIRCULAR_ARROW},
        {"leftRightCircularArrow", ShapeType::LEFT_RIGHT_CIRCULAR_ARROW},
        {"curvedRightArrow", ShapeType::CURVED_RIGHT_ARROW},
        {"curvedLeftArrow", ShapeType::CURVED_LEFT_ARROW},
        {"curvedUpArrow", ShapeType::CURVED_UP_ARROW},
        {"curvedDownArrow", ShapeType::CURVED_DOWN_ARROW},
        {"swooshArrow", ShapeType::SWOOSH_ARROW},
        {"cube", ShapeType::CUBE},
        {"can", ShapeType::CAN},
        {"lightningBolt", ShapeType::LIGHTNING_BOLT},
        {"heart", ShapeType::HEART},
        {"sun", ShapeType::SUN},
        {"moon", ShapeType::MOON},
        {"smileyFace", ShapeType::SMILEY_FACE},
        {"irregularSeal1", ShapeType::IRREGULAR_SEAL1},
        {"irregularSeal2", ShapeType::IRREGULAR_SEAL2},
        {"foldedCorner", ShapeType::FOLDED_CORNER},
        {"bevel", ShapeType::BEVEL},
        {"frame", ShapeType::FRAME},
        {"halfFrame", ShapeType::HALF_FRAME},
        {"corner", ShapeType::CORNER},
        {"diagStripe", ShapeType::DIAGONAL_STRIPE},
        {"chord", ShapeType::CHORD},
        {"arc", ShapeType::CURVED_ARC},
        {"leftBracket", ShapeType::LEFT_BRACKET},
        {"rightBracket", ShapeType::RIGHT_BRACKET},
        {"leftBrace", ShapeType::LEFT_BRACE},
        {"rightBrace", ShapeType::RIGHT_BRACE},
        {"bracketPair", ShapeType::BRACKET_PAIR},
        {"bracePair", ShapeType::BRACE_PAIR},
        {"straightConnector1", ShapeType::STRAIGHT_CONNECTOR1},
        {"bentConnector2", ShapeType::BENT_CONNECTOR2},
        {"bentConnector3", ShapeType::BENT_CONNECTOR3},
        {"bentConnector4", ShapeType::BENT_CONNECTOR4},
        {"bentConnector5", ShapeType::BENT_CONNECTOR5},
        {"curvedConnector2", ShapeType::CURVED_CONNECTOR2},
        {"curvedConnector3", ShapeType::CURVED_CONNECTOR3},
        {"curvedConnector4", ShapeType::CURVED_CONNECTOR4},
        {"curvedConnector5", ShapeType::CURVED_CONNECTOR5},
        {"callout1", ShapeType::CALLOUT1},
        {"callout2", ShapeType::CALLOUT2},
        {"callout3", ShapeType::CALLOUT3},
        {"accentCallout1", ShapeType::CALLOUT_1_WITH_ACCENT},
        {"accentCallout2", ShapeType::CALLOUT_2_WITH_ACCENT},
        {"accentCallout3", ShapeType::CALLOUT_3_WITH_ACCENT},
        {"borderCallout1", ShapeType::CALLOUT_1_WITH_BORDER},
        {"borderCallout2", ShapeType::CALLOUT_2_WITH_BORDER},
        {"borderCallout3", ShapeType::CALLOUT_3_WITH_BORDER},
        {"accentBorderCallout1", ShapeType::CALLOUT_1_WITH_BORDER_AND_ACCENT},
        {"accentBorderCallout2", ShapeType::CALLOUT_2_WITH_BORDER_AND_ACCENT},
        {"accentBorderCallout3", ShapeType::CALLOUT_3_WITH_BORDER_AND_ACCENT},
        {"wedgeRectCallout", ShapeType::CALLOUT_WEDGE_RECTANGLE},
        {"wedgeRoundRectCallout", ShapeType::CALLOUT_WEDGE_ROUND_RECTANGLE},
        {"wedgeEllipseCallout", ShapeType::CALLOUT_WEDGE_ELLIPSE},
        {"cloudCallout", ShapeType::CALLOUT_CLOUD},
        {"cloud", ShapeType::CLOUD},
        {"ribbon", ShapeType::RIBBON},
        {"ribbon2", ShapeType::RIBBON2},
        {"ellipseRibbon", ShapeType::ELLIPSE_RIBBON},
        {"ellipseRibbon2", ShapeType::ELLIPSE_RIBBON2},
        {"leftRightRibbon", ShapeType::LEFT_RIGHT_RIBBON},
        {"verticalScroll", ShapeType::VERTICAL_SCROLL},
        {"horizontalScroll", ShapeType::HORIZONTAL_SCROLL},
        {"wave", ShapeType::WAVE},
        {"doubleWave", ShapeType::DOUBLE_WAVE},
        {"mathPlus", ShapeType::PLUS},
        {"flowChartProcess", ShapeType::PROCESS_FLOW},
        {"flowChartDecision", ShapeType::DECISION_FLOW},
        {"flowChartInputOutput", ShapeType::INPUT_OUTPUT_FLOW},
        {"flowChartPredefinedProcess", ShapeType::PREDEFINED_PROCESS_FLOW},
        {"flowChartInternalStorage", ShapeType::INTERNAL_STORAGE_FLOW},
        {"flowChartDocument", ShapeType::DOCUMENT_FLOW},
        {"flowChartMultidocument", ShapeType::MULTI_DOCUMENT_FLOW},
        {"flowChartTerminator", ShapeType::TERMINATOR_FLOW},
        {"flowChartPreparation", ShapeType::PREPARATION_FLOW},
        {"flowChartManualInput", ShapeType::MANUAL_INPUT_FLOW},
        {"flowChartManualOperation", ShapeType::MANUAL_OPERATION_FLOW},
        {"flowChartConnector", ShapeType::CONNECTOR_FLOW},
        {"flowChartPunchedCard", ShapeType::PUNCHED_CARD_FLOW},
        {"flowChartPunchedTape", ShapeType::PUNCHED_TAPE_FLOW},
        {"flowChartSummingJunction", ShapeType::SUMMING_JUNCTION_FLOW},
        {"flowChartOr", ShapeType::OR_FLOW},
        {"flowChartCollate", ShapeType::COLLATE_FLOW},
        {"flowChartSort", ShapeType::SORT_FLOW},
        {"flowChartExtract", ShapeType::EXTRACT_FLOW},
        {"flowChartMerge", ShapeType::MERGE_FLOW},
        {"flowChartOfflineStorage", ShapeType::OFFLINE_STORAGE_FLOW},
        {"flowChartOnlineStorage", ShapeType::ONLINE_STORAGE_FLOW},
        {"flowChartMagneticTape", ShapeType::MAGNETIC_TAPE_FLOW},
        {"flowChartMagneticDisk", ShapeType::MAGNETIC_DISK_FLOW},
        {"flowChartMagneticDrum", ShapeType::MAGNETIC_DRUM_FLOW},
        {"flowChartDisplay", ShapeType::DISPLAY_FLOW},
        {"flowChartDelay", ShapeType::DELAY_FLOW},
        {"flowChartAlternateProcess", ShapeType::ALTERNATE_PROCESS_FLOW},
        {"flowChartOffpageConnector", ShapeType::OFF_PAGE_CONNECTOR_FLOW},
        {"actionButtonBlank", ShapeType::BLANK_BUTTON},
        {"actionButtonHome", ShapeType::HOME_BUTTON},
        {"actionButtonHelp", ShapeType::HELP_BUTTON},
        {"actionButtonInformation", ShapeType::INFORMATION_BUTTON},
        {"actionButtonForwardNext", ShapeType::FORWARD_OR_NEXT_BUTTON},
        {"actionButtonBackPrevious", ShapeType::BACK_OR_PREVIOUS_BUTTON},
        {"actionButtonEnd", ShapeType::END_BUTTON},
        {"actionButtonBeginning", ShapeType::BEGINNING_BUTTON},
        {"actionButtonReturn", ShapeType::RETURN_BUTTON},
        {"actionButtonDocument", ShapeType::DOCUMENT_BUTTON},
        {"actionButtonSound", ShapeType::SOUND_BUTTON},
        {"actionButtonMovie", ShapeType::MOVIE_BUTTON},
        {"gear6", ShapeType::GEAR6},
        {"gear9", ShapeType::GEAR9},
        {"funnel", ShapeType::FUNNEL},
        {"mathMinus", ShapeType::MINUS_MATH},
        {"mathMultiply", ShapeType::MULTIPLY_MATH},
        {"mathDivide", ShapeType::DIVIDE_MATH},
        {"mathEqual", ShapeType::EQUAL_MATH},
        {"mathNotEqual", ShapeType::NOT_EQUAL_MATH},
        {"cornerTabs", ShapeType::CORNER_TABS},
        {"squareTabs", ShapeType::SQUARE_TABS},
        {"plaqueTabs", ShapeType::PLAQUE_TABS},
        {"chartX", ShapeType::CHART_X},
        {"chartStar", ShapeType::CHART_STAR},
        {"chartPlus", ShapeType::CHART_PLUS},
    };
    auto it = map.find(prst);
    return it != map.end() ? it->second : ShapeType::NOT_DEFINED;
}

// ---------------------------------------------------------------------------
// Connector default adjustments
// ---------------------------------------------------------------------------

struct ConnectorAdj {
    const char* name;
    int value;
};

struct ConnectorAdjList {
    const ConnectorAdj* adjs;
    std::size_t count;
};

ConnectorAdjList get_connector_adjustments(std::string_view prst) {
    static constexpr ConnectorAdj kBent3[] = {{"adj1", 50000}};
    static constexpr ConnectorAdj kBent4[] = {{"adj1", 50000}, {"adj2", 50000}};
    static constexpr ConnectorAdj kBent5[] = {{"adj1", 50000}, {"adj2", 50000}, {"adj3", 50000}};

    if (prst == "bentConnector3" || prst == "curvedConnector3")
        return {kBent3, 1};
    if (prst == "bentConnector4" || prst == "curvedConnector4")
        return {kBent4, 2};
    if (prst == "bentConnector5" || prst == "curvedConnector5")
        return {kBent5, 3};
    return {nullptr, 0};
}

// ---------------------------------------------------------------------------
// Shape factory: create a Shape subclass from an XML element
// ---------------------------------------------------------------------------

std::unique_ptr<Shape> create_shape_from_xml(
    pugi::xml_node elem,
    Internal::pptx::SlidePart* slide_part,
    IBaseSlide* parent_slide) {

    auto tag = std::string_view(elem.name());
    std::unique_ptr<Shape> shape;

    if (tag == "p:sp") {
        // AutoShape has its own init_internal that also parses the text frame.
        // Call it directly on the derived type since it is non-virtual.
        auto auto_shape = std::make_unique<AutoShape>();
        auto_shape->init_internal(elem, slide_part, parent_slide);
        shape = std::move(auto_shape);
    } else if (tag == "p:cxnSp") {
        shape = std::make_unique<Connector>();
        shape->init_internal(elem, slide_part, parent_slide);
    } else if (tag == "p:pic") {
        shape = std::make_unique<PictureFrame>();
        shape->init_internal(elem, slide_part, parent_slide);
    } else if (tag == "p:grpSp") {
        shape = std::make_unique<GroupShape>();
        shape->init_internal(elem, slide_part, parent_slide);
    } else {
        // p:graphicFrame (tables, charts) handled separately
        return nullptr;
    }

    // Restore shape_type from the prstGeom preset attribute in the XML.
    auto sp_pr = elem.child("p:spPr");
    if (sp_pr) {
        auto prst_geom = sp_pr.child("a:prstGeom");
        if (prst_geom) {
            auto prst_attr = prst_geom.attribute("prst");
            if (prst_attr) {
                shape->set_shape_type(prst_to_shape_type(prst_attr.as_string()));
            }
        }
    }

    return shape;
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

bool is_group_property_tag(std::string_view tag) {
    return tag == "p:nvGrpSpPr" || tag == "p:grpSpPr";
}

bool is_shape_tag(std::string_view tag) {
    return tag == "p:sp" || tag == "p:pic" || tag == "p:graphicFrame" ||
           tag == "p:grpSp" || tag == "p:cxnSp";
}

std::string to_emu(double points) {
    return std::to_string(static_cast<int>(std::round(points * pptx::kEmuPerPoint)));
}

std::string format_auto_shape_name(ShapeType type, int shape_id) {
    auto sv = to_string_view(type);
    std::string name;
    for (std::size_t i = 0; i < sv.size(); ++i) {
        if (i > 0 && std::isupper(static_cast<unsigned char>(sv[i])) &&
            std::islower(static_cast<unsigned char>(sv[i > 0 ? i - 1 : 0]))) {
            name += ' ';
        }
        name += sv[i];
    }
    name += ' ';
    name += std::to_string(shape_id);
    return name;
}

// Build a table from column widths and row heights (in-memory, no XML).
std::unique_ptr<Table> build_table_simple(
    std::span<const double> column_widths,
    std::span<const double> row_heights) {

    auto table = std::make_unique<Table>();
    for (std::size_t ci = 0; ci < column_widths.size(); ++ci) {
        table->columns().add(std::make_unique<Column>(column_widths[ci]));
    }
    for (std::size_t ri = 0; ri < row_heights.size(); ++ri) {
        auto row = std::make_unique<Row>(row_heights[ri]);
        for (std::size_t ci = 0; ci < column_widths.size(); ++ci) {
            auto cell = std::make_unique<Cell>();
            cell->set_first_row_index(static_cast<int>(ri));
            cell->set_first_column_index(static_cast<int>(ci));
            cell->set_table(table.get());
            row->add(std::move(cell));
        }
        table->rows().add(std::move(row));
    }
    return table;
}

// Compute relative path from source_dir to target_path.
std::string compute_relative_path(std::string_view source_dir,
                                  std::string_view target_path) {
    // Split paths into segments
    auto split = [](std::string_view path) {
        std::vector<std::string_view> parts;
        while (!path.empty()) {
            auto pos = path.find('/');
            if (pos == std::string_view::npos) {
                parts.push_back(path);
                break;
            }
            if (pos > 0) parts.push_back(path.substr(0, pos));
            path.remove_prefix(pos + 1);
        }
        return parts;
    };

    auto source_parts = split(source_dir);
    auto target_parts = split(target_path);

    // Find common prefix length
    std::size_t common = 0;
    for (std::size_t i = 0; i < std::min(source_parts.size(), target_parts.size()); ++i) {
        if (source_parts[i] == target_parts[i])
            ++common;
        else
            break;
    }

    std::string result;
    for (std::size_t i = common; i < source_parts.size(); ++i) {
        if (!result.empty()) result += '/';
        result += "..";
    }
    for (std::size_t i = common; i < target_parts.size(); ++i) {
        if (!result.empty()) result += '/';
        result += target_parts[i];
    }
    return result;
}

} // anonymous namespace

// ===========================================================================
// Special members
// ===========================================================================

ShapeCollection::~ShapeCollection() = default;
ShapeCollection::ShapeCollection(ShapeCollection&&) noexcept = default;
ShapeCollection& ShapeCollection::operator=(ShapeCollection&&) noexcept = default;

// ===========================================================================
// init_internal
// ===========================================================================

void ShapeCollection::init_internal(Internal::pptx::SlidePart* slide_part,
                                    IBaseSlide* parent_slide) {
    slide_part_ = slide_part;
    parent_slide_ = parent_slide;
    cache_valid_ = false;
    shapes_.clear();
    tables_.clear();
}

// ===========================================================================
// XML-backed internal API
// ===========================================================================

pugi::xml_node ShapeCollection::get_sp_tree() const {
    if (!slide_part_) return {};
    auto root = slide_part_->root();
    if (!root) return {};
    auto csld = root.child("p:cSld");
    if (!csld) return {};
    return csld.child("p:spTree");
}

void ShapeCollection::load_shapes() const {
    if (cache_valid_) return;
    cache_valid_ = true;

    if (!slide_part_) return;

    auto sp_tree = get_sp_tree();
    if (!sp_tree) return;

    // Build a lookup of existing shapes by XML node for identity preservation
    std::unordered_map<void*, std::unique_ptr<Shape>> existing;
    for (auto& s : shapes_) {
        auto node = s->xml_element();
        if (node) {
            existing[node.internal_object()] = std::move(s);
        }
    }
    shapes_.clear();

    for (auto child : sp_tree.children()) {
        auto tag = std::string_view(child.name());
        if (is_group_property_tag(tag)) continue;
        if (!is_shape_tag(tag)) continue;

        // graphicFrame (tables, charts, etc.) — load into tables_
        if (tag == "p:graphicFrame") {
            auto variant = pptx::shape_factory::create_graphical_object(
                child, slide_part_, parent_slide_);
            if (auto* tbl_ptr = std::get_if<std::unique_ptr<Table>>(&variant)) {
                // Avoid duplicates: only add if not already tracked
                bool already_tracked = false;
                for (auto& existing_tbl : tables_) {
                    if (existing_tbl->xml_element().internal_object() ==
                        child.internal_object()) {
                        already_tracked = true;
                        break;
                    }
                }
                if (!already_tracked) {
                    tables_.push_back(std::move(*tbl_ptr));
                }
            }
            continue;
        }

        void* key = child.internal_object();
        auto it = existing.find(key);
        if (it != existing.end()) {
            shapes_.push_back(std::move(it->second));
            existing.erase(it);
        } else {
            auto shape = create_shape_from_xml(child, slide_part_, parent_slide_);
            if (shape) {
                shapes_.push_back(std::move(shape));
            }
        }
    }
    // Shapes remaining in 'existing' are no longer in XML — they are destroyed.

    // Build a shape-ID-to-pointer lookup for connection resolution.
    std::unordered_map<std::uint32_t, Shape*> id_to_shape;
    for (auto& s : shapes_) {
        auto c_nv_pr = s->get_c_nv_pr();
        if (c_nv_pr) {
            auto id_attr = c_nv_pr.attribute("id");
            if (id_attr) {
                id_to_shape[id_attr.as_uint()] = s.get();
            }
        }
    }

    // Restore connector connections from XML.
    for (auto& s : shapes_) {
        auto* conn = dynamic_cast<Connector*>(s.get());
        if (!conn) continue;
        auto c_nv_cxn_sp_pr = conn->get_c_nv_cxn_sp_pr();
        if (!c_nv_cxn_sp_pr) continue;

        auto st_cxn = c_nv_cxn_sp_pr.child("a:stCxn");
        if (st_cxn) {
            auto id_attr = st_cxn.attribute("id");
            auto idx_attr = st_cxn.attribute("idx");
            if (id_attr) {
                auto it = id_to_shape.find(id_attr.as_uint());
                if (it != id_to_shape.end()) {
                    conn->set_start_shape_connected_to(it->second);
                    if (idx_attr) {
                        conn->set_start_shape_connection_site_index(
                            idx_attr.as_uint());
                    }
                }
            }
        }

        auto end_cxn = c_nv_cxn_sp_pr.child("a:endCxn");
        if (end_cxn) {
            auto id_attr = end_cxn.attribute("id");
            auto idx_attr = end_cxn.attribute("idx");
            if (id_attr) {
                auto it = id_to_shape.find(id_attr.as_uint());
                if (it != id_to_shape.end()) {
                    conn->set_end_shape_connected_to(it->second);
                    if (idx_attr) {
                        conn->set_end_shape_connection_site_index(
                            idx_attr.as_uint());
                    }
                }
            }
        }
    }
}

void ShapeCollection::invalidate_cache() {
    cache_valid_ = false;
}

void ShapeCollection::save_to_part() {
    if (slide_part_) {
        slide_part_->save();
    }
}

int ShapeCollection::next_shape_id() const {
    auto sp_tree = get_sp_tree();
    if (!sp_tree) return 2;

    int max_id = 1;
    // Walk all descendants looking for 'id' attributes
    for (auto node = sp_tree; node; node = node.next_sibling()) {
        for (auto desc : sp_tree.children()) {
            // Recursive iteration via pugixml tree walker
            (void)desc;
        }
    }
    // Use pugixml's tree_walker or manual recursion
    struct IdFinder : pugi::xml_tree_walker {
        int max_id = 1;
        bool for_each(pugi::xml_node& node) override {
            auto id_attr = node.attribute("id");
            if (id_attr) {
                int val = id_attr.as_int(0);
                if (val > max_id) max_id = val;
            }
            return true;
        }
    } finder;
    sp_tree.traverse(finder);
    return finder.max_id + 1;
}

// ===========================================================================
// build_auto_shape_xml
// ===========================================================================

void ShapeCollection::build_auto_shape_xml(
    pugi::xml_node sp, int shape_id, std::string_view name,
    ShapeType type, double x, double y, double w, double h,
    bool create_from_template) {

    auto prst = shape_type_to_prst(type);
    if (!prst) prst = "rect";

    auto x_emu = to_emu(x);
    auto y_emu = to_emu(y);
    auto w_emu = to_emu(w);
    auto h_emu = to_emu(h);

    // nvSpPr
    auto nv_sp_pr = sp.append_child("p:nvSpPr");
    auto c_nv_pr = nv_sp_pr.append_child("p:cNvPr");
    c_nv_pr.append_attribute("id") = std::to_string(shape_id).c_str();
    c_nv_pr.append_attribute("name") = std::string(name).c_str();
    nv_sp_pr.append_child("p:cNvSpPr");
    nv_sp_pr.append_child("p:nvPr");

    // spPr
    auto sp_pr = sp.append_child("p:spPr");
    auto xfrm = sp_pr.append_child("a:xfrm");
    auto off = xfrm.append_child("a:off");
    off.append_attribute("x") = x_emu.c_str();
    off.append_attribute("y") = y_emu.c_str();
    auto ext = xfrm.append_child("a:ext");
    ext.append_attribute("cx") = w_emu.c_str();
    ext.append_attribute("cy") = h_emu.c_str();
    auto prst_geom = sp_pr.append_child("a:prstGeom");
    prst_geom.append_attribute("prst") = prst;
    prst_geom.append_child("a:avLst");

    if (create_from_template) {
        // p:style for theme-based appearance
        auto style = sp.append_child("p:style");

        auto ln_ref = style.append_child("a:lnRef");
        ln_ref.append_attribute("idx") = "2";
        auto ln_ref_clr = ln_ref.append_child("a:schemeClr");
        ln_ref_clr.append_attribute("val") = "accent1";
        ln_ref_clr.append_child("a:shade").append_attribute("val") = "50000";

        auto fill_ref = style.append_child("a:fillRef");
        fill_ref.append_attribute("idx") = "1";
        fill_ref.append_child("a:schemeClr").append_attribute("val") = "accent1";

        auto effect_ref = style.append_child("a:effectRef");
        effect_ref.append_attribute("idx") = "0";
        effect_ref.append_child("a:schemeClr").append_attribute("val") = "accent1";

        auto font_ref = style.append_child("a:fontRef");
        font_ref.append_attribute("idx") = "minor";
        font_ref.append_child("a:schemeClr").append_attribute("val") = "lt1";
    }

    // txBody (must come after p:style)
    auto tx_body = sp.append_child("p:txBody");
    auto body_pr = tx_body.append_child("a:bodyPr");
    body_pr.append_attribute("rtlCol") = "0";
    body_pr.append_attribute("anchor") = "ctr";
    tx_body.append_child("a:lstStyle");
    auto a_p = tx_body.append_child("a:p");
    a_p.append_child("a:endParaRPr");
}

// ===========================================================================
// build_connector_xml
// ===========================================================================

void ShapeCollection::build_connector_xml(
    pugi::xml_node cxn_sp, int shape_id, std::string_view name,
    ShapeType type, double x, double y, double w, double h,
    bool create_from_template) {

    auto prst = shape_type_to_prst(type);
    if (!prst) prst = "bentConnector3";

    auto x_emu = to_emu(x);
    auto y_emu = to_emu(y);
    auto w_emu = to_emu(w);
    auto h_emu = to_emu(h);

    // nvCxnSpPr
    auto nv_cxn_sp_pr = cxn_sp.append_child("p:nvCxnSpPr");
    auto c_nv_pr = nv_cxn_sp_pr.append_child("p:cNvPr");
    c_nv_pr.append_attribute("id") = std::to_string(shape_id).c_str();
    c_nv_pr.append_attribute("name") = std::string(name).c_str();
    nv_cxn_sp_pr.append_child("p:cNvCxnSpPr");
    nv_cxn_sp_pr.append_child("p:nvPr");

    // spPr
    auto sp_pr = cxn_sp.append_child("p:spPr");
    auto xfrm = sp_pr.append_child("a:xfrm");
    auto off = xfrm.append_child("a:off");
    off.append_attribute("x") = x_emu.c_str();
    off.append_attribute("y") = y_emu.c_str();
    auto ext = xfrm.append_child("a:ext");
    ext.append_attribute("cx") = w_emu.c_str();
    ext.append_attribute("cy") = h_emu.c_str();
    auto prst_geom = sp_pr.append_child("a:prstGeom");
    prst_geom.append_attribute("prst") = prst;
    auto av_lst = prst_geom.append_child("a:avLst");

    auto adj_list = get_connector_adjustments(prst);
    for (std::size_t i = 0; i < adj_list.count; ++i) {
        auto gd = av_lst.append_child("a:gd");
        gd.append_attribute("name") = adj_list.adjs[i].name;
        auto fmla = std::string("val ") + std::to_string(adj_list.adjs[i].value);
        gd.append_attribute("fmla") = fmla.c_str();
    }

    if (create_from_template) {
        auto style = cxn_sp.append_child("p:style");

        auto ln_ref = style.append_child("a:lnRef");
        ln_ref.append_attribute("idx") = "1";
        ln_ref.append_child("a:schemeClr").append_attribute("val") = "accent1";

        auto fill_ref = style.append_child("a:fillRef");
        fill_ref.append_attribute("idx") = "0";
        fill_ref.append_child("a:schemeClr").append_attribute("val") = "accent1";

        auto effect_ref = style.append_child("a:effectRef");
        effect_ref.append_attribute("idx") = "0";
        effect_ref.append_child("a:schemeClr").append_attribute("val") = "accent1";

        auto font_ref = style.append_child("a:fontRef");
        font_ref.append_attribute("idx") = "minor";
        font_ref.append_child("a:schemeClr").append_attribute("val") = "tx1";
    }
}

// ===========================================================================
// insert_or_append helper
// ===========================================================================

pugi::xml_node ShapeCollection::insert_or_append(
    pugi::xml_node sp_tree,
    std::optional<std::size_t> index,
    const char* element_name) {

    if (!index.has_value()) {
        return sp_tree.append_child(element_name);
    }

    std::size_t shape_count = 0;
    for (auto child : sp_tree.children()) {
        auto tag = std::string_view(child.name());
        if (is_group_property_tag(tag)) continue;
        if (shape_count == *index) {
            return sp_tree.insert_child_before(element_name, child);
        }
        ++shape_count;
    }
    return sp_tree.append_child(element_name);
}

// ===========================================================================
// add_auto_shape_impl
// ===========================================================================

AutoShape& ShapeCollection::add_auto_shape_impl(
    std::optional<std::size_t> index, ShapeType type,
    double x, double y, double w, double h,
    bool create_from_template) {

    load_shapes();

    if (slide_part_) {
        auto sp_tree = get_sp_tree();
        if (!sp_tree)
            throw std::runtime_error("Cannot add shape: slide has no shape tree");

        int shape_id = next_shape_id();
        auto name = format_auto_shape_name(type, shape_id);

        auto node = insert_or_append(sp_tree, index, "p:sp");
        build_auto_shape_xml(node, shape_id, name, type, x, y, w, h,
                             create_from_template);
        save_to_part();

        auto shape = std::make_unique<AutoShape>();
        shape->init_internal(node, slide_part_, parent_slide_);
        auto& ref = *shape;

        if (index.has_value() && *index <= shapes_.size()) {
            shapes_.insert(
                shapes_.begin() + static_cast<std::ptrdiff_t>(*index),
                std::move(shape));
        } else {
            shapes_.push_back(std::move(shape));
        }
        return ref;
    }

    // Simple (non-XML) mode
    auto shape = std::make_unique<AutoShape>(type, x, y, w, h);
    if (create_from_template) {
        shape->add_text_frame("");
    }
    auto& ref = *shape;
    if (index.has_value() && *index <= shapes_.size()) {
        shapes_.insert(
            shapes_.begin() + static_cast<std::ptrdiff_t>(*index),
            std::move(shape));
    } else {
        shapes_.push_back(std::move(shape));
    }
    return ref;
}

// ===========================================================================
// add_connector_impl
// ===========================================================================

Connector& ShapeCollection::add_connector_impl(
    std::optional<std::size_t> index, ShapeType type,
    double x, double y, double w, double h,
    bool create_from_template) {

    load_shapes();

    if (slide_part_) {
        auto sp_tree = get_sp_tree();
        if (!sp_tree)
            throw std::runtime_error("Cannot add shape: slide has no shape tree");

        int shape_id = next_shape_id();
        auto name = "Connector " + std::to_string(shape_id);

        auto node = insert_or_append(sp_tree, index, "p:cxnSp");
        build_connector_xml(node, shape_id, name, type, x, y, w, h,
                            create_from_template);
        save_to_part();

        auto shape = std::make_unique<Connector>();
        shape->init_internal(node, slide_part_, parent_slide_);
        auto& ref = *shape;

        if (index.has_value() && *index <= shapes_.size()) {
            shapes_.insert(
                shapes_.begin() + static_cast<std::ptrdiff_t>(*index),
                std::move(shape));
        } else {
            shapes_.push_back(std::move(shape));
        }
        return ref;
    }

    // Simple mode
    auto shape = std::make_unique<Connector>(type, x, y, w, h);

    // Populate default adjustments based on preset geometry.
    auto prst = shape_type_to_prst(type);
    if (prst) {
        auto adj_list = get_connector_adjustments(prst);
        for (std::size_t a = 0; a < adj_list.count; ++a) {
            shape->adjustments().add(
                AdjustValue(adj_list.adjs[a].name, adj_list.adjs[a].value));
        }
    }

    auto& ref = *shape;
    if (index.has_value() && *index <= shapes_.size()) {
        shapes_.insert(
            shapes_.begin() + static_cast<std::ptrdiff_t>(*index),
            std::move(shape));
    } else {
        shapes_.push_back(std::move(shape));
    }
    return ref;
}

// ===========================================================================
// add_picture_frame_impl
// ===========================================================================

PictureFrame& ShapeCollection::add_picture_frame_impl(
    std::optional<std::size_t> index, ShapeType type,
    double x, double y, double w, double h,
    PPImage& image) {

    load_shapes();

    if (slide_part_) {
        auto sp_tree = get_sp_tree();
        if (!sp_tree)
            throw std::runtime_error("Cannot add shape: slide has no shape tree");

        auto prst = shape_type_to_prst(type);
        if (!prst) prst = "rect";

        // Resolve image relationship
        auto& image_part_name = image.part_name();
        auto& rels_mgr = slide_part_->rels_manager();

        // Compute relative target from slide to image
        auto slide_dir = slide_part_->part_name();
        auto slash_pos = slide_dir.rfind('/');
        if (slash_pos != std::string::npos)
            slide_dir = slide_dir.substr(0, slash_pos);

        auto relative_target = compute_relative_path(slide_dir, image_part_name);

        // Check if relationship already exists
        std::string embed_id;
        auto existing_rels = rels_mgr.get_relationships_by_type(
            Internal::opc::rel_types::kImage);
        for (auto& rel : existing_rels) {
            auto resolved = slide_part_->resolve_target(rel.target);
            if (resolved == image_part_name) {
                embed_id = rel.id;
                break;
            }
        }
        if (embed_id.empty()) {
            embed_id = rels_mgr.add_relationship(
                Internal::opc::rel_types::kImage, relative_target);
            rels_mgr.save();
        }

        int shape_id = next_shape_id();
        auto name = "Picture " + std::to_string(shape_id);
        auto x_emu = to_emu(x);
        auto y_emu = to_emu(y);
        auto w_emu = to_emu(w);
        auto h_emu = to_emu(h);

        auto pic = insert_or_append(sp_tree, index, "p:pic");

        // nvPicPr
        auto nv_pic_pr = pic.append_child("p:nvPicPr");
        auto c_nv_pr = nv_pic_pr.append_child("p:cNvPr");
        c_nv_pr.append_attribute("id") = std::to_string(shape_id).c_str();
        c_nv_pr.append_attribute("name") = name.c_str();
        auto c_nv_pic_pr = nv_pic_pr.append_child("p:cNvPicPr");
        auto pic_locks = c_nv_pic_pr.append_child("a:picLocks");
        pic_locks.append_attribute("noChangeAspect") = "1";
        nv_pic_pr.append_child("p:nvPr");

        // blipFill
        auto blip_fill = pic.append_child("p:blipFill");
        auto blip = blip_fill.append_child("a:blip");
        // r:embed attribute
        auto r_embed_name = std::string("{") +
            std::string(Internal::pptx::ns_uri::kR) + "}embed";
        blip.append_attribute(r_embed_name.c_str()) = embed_id.c_str();
        auto stretch = blip_fill.append_child("a:stretch");
        stretch.append_child("a:fillRect");

        // spPr
        auto sp_pr = pic.append_child("p:spPr");
        auto xfrm = sp_pr.append_child("a:xfrm");
        auto off = xfrm.append_child("a:off");
        off.append_attribute("x") = x_emu.c_str();
        off.append_attribute("y") = y_emu.c_str();
        auto ext = xfrm.append_child("a:ext");
        ext.append_attribute("cx") = w_emu.c_str();
        ext.append_attribute("cy") = h_emu.c_str();
        auto prst_geom = sp_pr.append_child("a:prstGeom");
        prst_geom.append_attribute("prst") = prst;
        prst_geom.append_child("a:avLst");

        save_to_part();

        auto shape = std::make_unique<PictureFrame>();
        shape->init_internal(pic, slide_part_, parent_slide_);
        shape->set_pp_image(&image);
        auto& ref = *shape;

        if (index.has_value() && *index <= shapes_.size()) {
            shapes_.insert(
                shapes_.begin() + static_cast<std::ptrdiff_t>(*index),
                std::move(shape));
        } else {
            shapes_.push_back(std::move(shape));
        }
        return ref;
    }

    // Simple mode
    auto shape = std::make_unique<PictureFrame>(type, x, y, w, h, &image);
    auto& ref = *shape;
    if (index.has_value() && *index <= shapes_.size()) {
        shapes_.insert(
            shapes_.begin() + static_cast<std::ptrdiff_t>(*index),
            std::move(shape));
    } else {
        shapes_.push_back(std::move(shape));
    }
    return ref;
}

// ===========================================================================
// add_table_impl
// ===========================================================================

Table& ShapeCollection::add_table_impl(
    std::optional<std::size_t> index, double x, double y,
    std::span<const double> column_widths,
    std::span<const double> row_heights) {

    if (slide_part_) {
        auto sp_tree = get_sp_tree();
        if (!sp_tree)
            throw std::runtime_error("Cannot add shape: slide has no shape tree");

        int shape_id = next_shape_id();
        auto name = "Table " + std::to_string(shape_id);

        auto x_emu = to_emu(x);
        auto y_emu = to_emu(y);
        double total_w = 0;
        for (auto cw : column_widths) total_w += cw;
        double total_h = 0;
        for (auto rh : row_heights) total_h += rh;
        auto w_emu = to_emu(total_w);
        auto h_emu = to_emu(total_h);

        auto gf = insert_or_append(sp_tree, index, "p:graphicFrame");

        // nvGraphicFramePr
        auto nv_gf_pr = gf.append_child("p:nvGraphicFramePr");
        auto c_nv_pr = nv_gf_pr.append_child("p:cNvPr");
        c_nv_pr.append_attribute("id") = std::to_string(shape_id).c_str();
        c_nv_pr.append_attribute("name") = name.c_str();
        auto c_nv_gf_pr = nv_gf_pr.append_child("p:cNvGraphicFramePr");
        auto gf_locking = c_nv_gf_pr.append_child("a:graphicFrameLocking");
        gf_locking.append_attribute("noGrp") = "1";
        nv_gf_pr.append_child("p:nvPr");

        // p:xfrm
        auto xfrm = gf.append_child("p:xfrm");
        auto off = xfrm.append_child("a:off");
        off.append_attribute("x") = x_emu.c_str();
        off.append_attribute("y") = y_emu.c_str();
        auto ext = xfrm.append_child("a:ext");
        ext.append_attribute("cx") = w_emu.c_str();
        ext.append_attribute("cy") = h_emu.c_str();

        // a:graphic > a:graphicData > a:tbl
        auto graphic = gf.append_child("a:graphic");
        auto graphic_data = graphic.append_child("a:graphicData");
        graphic_data.append_attribute("uri") =
            std::string(pptx::Elements::kTableUri).c_str();

        auto tbl = graphic_data.append_child("a:tbl");

        // a:tblPr
        auto tbl_pr = tbl.append_child("a:tblPr");
        tbl_pr.append_attribute("firstRow") = "1";
        tbl_pr.append_attribute("bandRow") = "1";
        auto tbl_style_id = tbl_pr.append_child("a:tableStyleId");
        tbl_style_id.text().set("{5C22544A-7EE6-4342-B048-85BDC9FD1C3A}");

        // a:tblGrid
        auto tbl_grid = tbl.append_child("a:tblGrid");
        for (auto cw : column_widths) {
            auto grid_col = tbl_grid.append_child("a:gridCol");
            grid_col.append_attribute("w") = to_emu(cw).c_str();
        }

        // Rows
        auto num_cols = column_widths.size();
        for (auto rh : row_heights) {
            auto tr = tbl.append_child("a:tr");
            tr.append_attribute("h") = to_emu(rh).c_str();
            for (std::size_t c = 0; c < num_cols; ++c) {
                auto tc = tr.append_child("a:tc");
                auto txbody = tc.append_child("a:txBody");
                txbody.append_child("a:bodyPr");
                txbody.append_child("a:lstStyle");
                txbody.append_child("a:p");
                tc.append_child("a:tcPr");
            }
        }

        save_to_part();

        // Create an XML-backed table so that modifications propagate to the XML.
        auto table = std::make_unique<Table>();
        table->init_internal(gf, slide_part_, parent_slide_);
        auto& ref = *table;
        if (index.has_value() && *index <= tables_.size()) {
            tables_.insert(
                tables_.begin() + static_cast<std::ptrdiff_t>(*index),
                std::move(table));
        } else {
            tables_.push_back(std::move(table));
        }
        return ref;
    }

    // Simple mode
    auto table = build_table_simple(column_widths, row_heights);
    table->offset_x_ = x;
    table->offset_y_ = y;
    auto& ref = *table;
    if (index.has_value() && *index <= tables_.size()) {
        tables_.insert(
            tables_.begin() + static_cast<std::ptrdiff_t>(*index),
            std::move(table));
    } else {
        tables_.push_back(std::move(table));
    }
    return ref;
}

// ===========================================================================
// reorder_single
// ===========================================================================

void ShapeCollection::reorder_single(std::size_t new_index, Shape& shape) {
    load_shapes();

    if (slide_part_) {
        auto sp_tree = get_sp_tree();
        if (!sp_tree) return;

        auto shape_elem = shape.xml_element();
        if (!shape_elem) return;

        // Remove from current position in XML
        sp_tree.remove_child(shape_elem);

        // Find the new insertion point (skip nvGrpSpPr and grpSpPr)
        std::size_t current_shape_idx = 0;
        pugi::xml_node insert_before;
        for (auto child : sp_tree.children()) {
            auto tag = std::string_view(child.name());
            if (is_group_property_tag(tag)) continue;
            if (current_shape_idx >= new_index) {
                insert_before = child;
                break;
            }
            ++current_shape_idx;
        }

        if (insert_before) {
            sp_tree.insert_copy_before(shape_elem, insert_before);
        } else {
            sp_tree.append_copy(shape_elem);
        }
    }

    // Also reorder in shapes_ vector
    auto it = std::find_if(shapes_.begin(), shapes_.end(),
                           [&](const auto& p) { return p.get() == &shape; });
    if (it == shapes_.end()) return;

    auto owned = std::move(*it);
    shapes_.erase(it);

    if (new_index > shapes_.size()) {
        new_index = shapes_.size();
    }
    shapes_.insert(shapes_.begin() + static_cast<std::ptrdiff_t>(new_index),
                   std::move(owned));
}

// ===========================================================================
// IShapeCollection implementation
// ===========================================================================

IGroupShape* ShapeCollection::parent_group() const noexcept { return nullptr; }
IShapeCollection& ShapeCollection::as_i_collection() noexcept { return *this; }
IShapeCollection& ShapeCollection::as_i_enumerable() noexcept { return *this; }

std::size_t ShapeCollection::size() const noexcept {
    load_shapes();
    return shapes_.size();
}

Shape& ShapeCollection::operator[](std::size_t index) {
    load_shapes();
    return *shapes_.at(index);
}

const Shape& ShapeCollection::operator[](std::size_t index) const {
    load_shapes();
    return *shapes_.at(index);
}

std::vector<Shape*> ShapeCollection::to_array() {
    load_shapes();
    std::vector<Shape*> result;
    result.reserve(shapes_.size());
    for (auto& s : shapes_) {
        result.push_back(s.get());
    }
    return result;
}

std::vector<Shape*> ShapeCollection::to_array(std::size_t start_index,
                                              std::size_t count) {
    load_shapes();
    if (start_index > shapes_.size()) {
        throw std::out_of_range("to_array: start_index out of range");
    }
    auto actual_count = std::min(count, shapes_.size() - start_index);
    std::vector<Shape*> result;
    result.reserve(actual_count);
    for (std::size_t i = start_index; i < start_index + actual_count; ++i) {
        result.push_back(shapes_[i].get());
    }
    return result;
}

// ---------------------------------------------------------------------------
// add/insert auto shape
// ---------------------------------------------------------------------------

AutoShape& ShapeCollection::add_auto_shape(ShapeType type, double x, double y,
                                           double width, double height) {
    return add_auto_shape_impl(std::nullopt, type, x, y, width, height, true);
}

AutoShape& ShapeCollection::add_auto_shape(ShapeType type, double x, double y,
                                           double width, double height,
                                           bool create_from_template) {
    return add_auto_shape_impl(std::nullopt, type, x, y, width, height,
                               create_from_template);
}

AutoShape& ShapeCollection::insert_auto_shape(std::size_t index, ShapeType type,
                                              double x, double y,
                                              double width, double height) {
    return add_auto_shape_impl(index, type, x, y, width, height, true);
}

AutoShape& ShapeCollection::insert_auto_shape(std::size_t index, ShapeType type,
                                              double x, double y,
                                              double width, double height,
                                              bool create_from_template) {
    return add_auto_shape_impl(index, type, x, y, width, height,
                               create_from_template);
}

// ---------------------------------------------------------------------------
// add/insert connector
// ---------------------------------------------------------------------------

Connector& ShapeCollection::add_connector(ShapeType type, double x, double y,
                                          double width, double height) {
    return add_connector_impl(std::nullopt, type, x, y, width, height, true);
}

Connector& ShapeCollection::add_connector(ShapeType type, double x, double y,
                                          double width, double height,
                                          bool create_from_template) {
    return add_connector_impl(std::nullopt, type, x, y, width, height,
                              create_from_template);
}

Connector& ShapeCollection::insert_connector(std::size_t index, ShapeType type,
                                             double x, double y,
                                             double width, double height) {
    return add_connector_impl(index, type, x, y, width, height, true);
}

Connector& ShapeCollection::insert_connector(std::size_t index, ShapeType type,
                                             double x, double y,
                                             double width, double height,
                                             bool create_from_template) {
    return add_connector_impl(index, type, x, y, width, height,
                              create_from_template);
}

// ---------------------------------------------------------------------------
// index_of
// ---------------------------------------------------------------------------

std::ptrdiff_t ShapeCollection::index_of(const Shape& shape) const {
    load_shapes();
    for (std::size_t i = 0; i < shapes_.size(); ++i) {
        if (shapes_[i].get() == &shape) {
            return static_cast<std::ptrdiff_t>(i);
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// add/insert picture frame
// ---------------------------------------------------------------------------

PictureFrame& ShapeCollection::add_picture_frame(ShapeType type, double x,
                                                  double y, double width,
                                                  double height,
                                                  PPImage& image) {
    return add_picture_frame_impl(std::nullopt, type, x, y, width, height, image);
}

PictureFrame& ShapeCollection::insert_picture_frame(std::size_t index,
                                                     ShapeType type, double x,
                                                     double y, double width,
                                                     double height,
                                                     PPImage& image) {
    return add_picture_frame_impl(index, type, x, y, width, height, image);
}

// ---------------------------------------------------------------------------
// add/insert table
// ---------------------------------------------------------------------------

Table& ShapeCollection::add_table(double x, double y,
                                  std::span<const double> column_widths,
                                  std::span<const double> row_heights) {
    return add_table_impl(std::nullopt, x, y, column_widths, row_heights);
}

Table& ShapeCollection::insert_table(std::size_t index, double x, double y,
                                     std::span<const double> column_widths,
                                     std::span<const double> row_heights) {
    return add_table_impl(index, x, y, column_widths, row_heights);
}

// ---------------------------------------------------------------------------
// remove / clear
// ---------------------------------------------------------------------------

void ShapeCollection::remove(const Shape& shape) {
    load_shapes();

    if (slide_part_) {
        auto elem = shape.xml_element();
        if (elem) {
            auto sp_tree = get_sp_tree();
            if (sp_tree) {
                sp_tree.remove_child(elem);
            }
            save_to_part();
        }
    }

    auto it = std::find_if(shapes_.begin(), shapes_.end(),
                           [&](const auto& p) { return p.get() == &shape; });
    if (it != shapes_.end()) {
        shapes_.erase(it);
    }
}

void ShapeCollection::remove_at(std::size_t index) {
    load_shapes();
    if (index >= shapes_.size()) {
        throw std::out_of_range("remove_at: index out of range");
    }

    if (slide_part_) {
        auto elem = shapes_[index]->xml_element();
        if (elem) {
            auto sp_tree = get_sp_tree();
            if (sp_tree) {
                sp_tree.remove_child(elem);
            }
            save_to_part();
        }
    }

    shapes_.erase(shapes_.begin() + static_cast<std::ptrdiff_t>(index));
}

void ShapeCollection::clear() noexcept {
    if (slide_part_) {
        auto sp_tree = get_sp_tree();
        if (sp_tree) {
            // Remove all shape elements but keep group properties
            auto child = sp_tree.first_child();
            while (child) {
                auto next = child.next_sibling();
                auto tag = std::string_view(child.name());
                if (!is_group_property_tag(tag)) {
                    sp_tree.remove_child(child);
                }
                child = next;
            }
            save_to_part();
        }
    }
    shapes_.clear();
    tables_.clear();
    cache_valid_ = true;
}

// ---------------------------------------------------------------------------
// reorder
// ---------------------------------------------------------------------------

void ShapeCollection::reorder(std::size_t new_index, Shape& shape) {
    reorder_single(new_index, shape);
}

void ShapeCollection::reorder(std::size_t index, std::span<Shape*> shapes) {
    for (auto* shape : shapes) {
        reorder_single(index, *shape);
        ++index;
    }
}

// ---------------------------------------------------------------------------
// Iterators
// ---------------------------------------------------------------------------

ShapeCollection::iterator ShapeCollection::begin() noexcept {
    load_shapes();
    return shapes_.begin();
}
ShapeCollection::iterator ShapeCollection::end() noexcept {
    load_shapes();
    return shapes_.end();
}
ShapeCollection::const_iterator ShapeCollection::begin() const noexcept {
    load_shapes();
    return shapes_.begin();
}
ShapeCollection::const_iterator ShapeCollection::end() const noexcept {
    load_shapes();
    return shapes_.end();
}

} // namespace Aspose::Slides::Foss
