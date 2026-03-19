// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include "shape_factory.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/group_shape.h>
#include <Aspose/Slides/Foss/picture_frame.h>
#include <Aspose/Slides/Foss/table.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

namespace Aspose::Slides::Foss::Internal::pptx::shape_factory {

namespace {

/// Case-insensitive substring search.
bool contains_ci(std::string_view haystack, std::string_view needle) {
    if (needle.size() > haystack.size()) return false;
    return std::search(
        haystack.begin(), haystack.end(),
        needle.begin(), needle.end(),
        [](char a, char b) {
            return std::tolower(static_cast<unsigned char>(a)) ==
                   std::tolower(static_cast<unsigned char>(b));
        }) != haystack.end();
}

} // namespace

ShapeVariant create_shape(pugi::xml_node xml_element,
                          SlidePart* slide_part,
                          IBaseSlide* parent_slide) {
    auto tag = std::string_view(xml_element.name());

    if (tag == "p:sp") {
        auto shape = std::make_unique<AutoShape>();
        shape->init_internal(xml_element, slide_part, parent_slide);
        return shape;
    }

    if (tag == "p:pic") {
        auto shape = std::make_unique<PictureFrame>();
        shape->init_internal(xml_element, slide_part, parent_slide);
        return shape;
    }

    if (tag == "p:grpSp") {
        auto shape = std::make_unique<GroupShape>();
        shape->init_internal(xml_element, slide_part, parent_slide);
        return shape;
    }

    if (tag == "p:cxnSp") {
        auto shape = std::make_unique<Connector>();
        shape->init_internal(xml_element, slide_part, parent_slide);
        return shape;
    }

    if (tag == "p:graphicFrame") {
        return create_graphical_object(xml_element, slide_part, parent_slide);
    }

    return std::monostate{};
}

ShapeVariant create_graphical_object(pugi::xml_node xml_element,
                                     SlidePart* slide_part,
                                     IBaseSlide* parent_slide) {
    // Navigate: p:graphicFrame > a:graphic > a:graphicData
    auto graphic = xml_element.child("a:graphic");
    if (!graphic) return std::monostate{};

    auto graphic_data = graphic.child("a:graphicData");
    if (!graphic_data) return std::monostate{};

    auto uri = std::string_view(graphic_data.attribute("uri").as_string());

    if (contains_ci(uri, "table")) {
        auto table = std::make_unique<Table>();
        table->init_internal(xml_element, slide_part, parent_slide);
        return table;
    }

    // Chart and SmartArt/Diagram are not yet implemented.
    // When available, add:
    //   if (contains_ci(uri, "chart")) { ... }
    //   if (contains_ci(uri, "smartart") || contains_ci(uri, "diagram")) { ... }

    return std::monostate{};
}

} // namespace Aspose::Slides::Foss::Internal::pptx::shape_factory
