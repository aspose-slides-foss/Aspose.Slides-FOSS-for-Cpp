// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the slide layout type.
enum class SlideLayoutType {
    CUSTOM,
    TITLE,
    TEXT,
    TWO_COLUMN_TEXT,
    TABLE,
    TEXT_AND_CHART,
    CHART_AND_TEXT,
    DIAGRAM,
    CHART,
    TEXT_AND_CLIP_ART,
    CLIP_ART_AND_TEXT,
    TITLE_ONLY,
    BLANK,
    TEXT_AND_OBJECT,
    OBJECT_AND_TEXT,
    OBJECT,
    TITLE_AND_OBJECT,
    TEXT_AND_MEDIA,
    MEDIA_AND_TEXT,
    OBJECT_OVER_TEXT,
    TEXT_OVER_OBJECT,
    TEXT_AND_TWO_OBJECTS,
    TWO_OBJECTS_AND_TEXT,
    TWO_OBJECTS_OVER_TEXT,
    FOUR_OBJECTS,
    VERTICAL_TEXT,
    CLIP_ART_AND_VERTICAL_TEXT,
    VERTICAL_TITLE_AND_TEXT,
    VERTICAL_TITLE_AND_TEXT_OVER_CHART,
    TWO_OBJECTS,
    OBJECT_AND_TWO_OBJECT,
    TWO_OBJECTS_AND_OBJECT,
    SECTION_HEADER,
    TWO_TEXT_AND_TWO_OBJECTS,
    TITLE_OBJECT_AND_CAPTION,
    PICTURE_AND_CAPTION,
};

/// Returns the string representation of a SlideLayoutType value.
constexpr std::string_view to_string_view(SlideLayoutType value) {
    switch (value) {
        case SlideLayoutType::CUSTOM: return "Custom";
        case SlideLayoutType::TITLE: return "Title";
        case SlideLayoutType::TEXT: return "Text";
        case SlideLayoutType::TWO_COLUMN_TEXT: return "TwoColumnText";
        case SlideLayoutType::TABLE: return "Table";
        case SlideLayoutType::TEXT_AND_CHART: return "TextAndChart";
        case SlideLayoutType::CHART_AND_TEXT: return "ChartAndText";
        case SlideLayoutType::DIAGRAM: return "Diagram";
        case SlideLayoutType::CHART: return "Chart";
        case SlideLayoutType::TEXT_AND_CLIP_ART: return "TextAndClipArt";
        case SlideLayoutType::CLIP_ART_AND_TEXT: return "ClipArtAndText";
        case SlideLayoutType::TITLE_ONLY: return "TitleOnly";
        case SlideLayoutType::BLANK: return "Blank";
        case SlideLayoutType::TEXT_AND_OBJECT: return "TextAndObject";
        case SlideLayoutType::OBJECT_AND_TEXT: return "ObjectAndText";
        case SlideLayoutType::OBJECT: return "Object";
        case SlideLayoutType::TITLE_AND_OBJECT: return "TitleAndObject";
        case SlideLayoutType::TEXT_AND_MEDIA: return "TextAndMedia";
        case SlideLayoutType::MEDIA_AND_TEXT: return "MediaAndText";
        case SlideLayoutType::OBJECT_OVER_TEXT: return "ObjectOverText";
        case SlideLayoutType::TEXT_OVER_OBJECT: return "TextOverObject";
        case SlideLayoutType::TEXT_AND_TWO_OBJECTS: return "TextAndTwoObjects";
        case SlideLayoutType::TWO_OBJECTS_AND_TEXT: return "TwoObjectsAndText";
        case SlideLayoutType::TWO_OBJECTS_OVER_TEXT: return "TwoObjectsOverText";
        case SlideLayoutType::FOUR_OBJECTS: return "FourObjects";
        case SlideLayoutType::VERTICAL_TEXT: return "VerticalText";
        case SlideLayoutType::CLIP_ART_AND_VERTICAL_TEXT: return "ClipArtAndVerticalText";
        case SlideLayoutType::VERTICAL_TITLE_AND_TEXT: return "VerticalTitleAndText";
        case SlideLayoutType::VERTICAL_TITLE_AND_TEXT_OVER_CHART: return "VerticalTitleAndTextOverChart";
        case SlideLayoutType::TWO_OBJECTS: return "TwoObjects";
        case SlideLayoutType::OBJECT_AND_TWO_OBJECT: return "ObjectAndTwoObject";
        case SlideLayoutType::TWO_OBJECTS_AND_OBJECT: return "TwoObjectsAndObject";
        case SlideLayoutType::SECTION_HEADER: return "SectionHeader";
        case SlideLayoutType::TWO_TEXT_AND_TWO_OBJECTS: return "TwoTextAndTwoObjects";
        case SlideLayoutType::TITLE_OBJECT_AND_CAPTION: return "TitleObjectAndCaption";
        case SlideLayoutType::PICTURE_AND_CAPTION: return "PictureAndCaption";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
