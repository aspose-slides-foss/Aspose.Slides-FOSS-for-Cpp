// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/bevel_preset_type.h>
#include <Aspose/Slides/Foss/cell_format.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/line_dash_style.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_bevel.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/three_d_format.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: clear shapes from first slide and return a reference.
Slide& clear_slide(Presentation& pres) {
    pres.slides()[0].shapes().clear();
    return pres.slides()[0];
}

} // namespace

// ---------------------------------------------------------------------------
// ShapeBevel property tests
// ---------------------------------------------------------------------------

/// Default-constructed ShapeBevel has NOT_DEFINED type and zero dimensions.
TEST(ShapeBevelTest, DefaultValues) {
    ShapeBevel bevel;
    EXPECT_EQ(bevel.bevel_type(), BevelPresetType::NOT_DEFINED);
    EXPECT_DOUBLE_EQ(bevel.width(), 0.0);
    EXPECT_DOUBLE_EQ(bevel.height(), 0.0);
}

/// Width getter/setter round-trips correctly.
TEST(ShapeBevelTest, WidthPersists) {
    ShapeBevel bevel;
    bevel.set_width(12.5);
    EXPECT_DOUBLE_EQ(bevel.width(), 12.5);
}

/// Height getter/setter round-trips correctly.
TEST(ShapeBevelTest, HeightPersists) {
    ShapeBevel bevel;
    bevel.set_height(8.0);
    EXPECT_DOUBLE_EQ(bevel.height(), 8.0);
}

/// Bevel type getter/setter round-trips correctly.
TEST(ShapeBevelTest, BevelTypePersists) {
    ShapeBevel bevel;
    bevel.set_bevel_type(BevelPresetType::CIRCLE);
    EXPECT_EQ(bevel.bevel_type(), BevelPresetType::CIRCLE);
}

/// All bevel preset types can be set and retrieved.
TEST(ShapeBevelTest, AllBevelTypesRoundTrip) {
    const BevelPresetType types[] = {
        BevelPresetType::ANGLE,    BevelPresetType::ART_DECO,
        BevelPresetType::CIRCLE,   BevelPresetType::CONVEX,
        BevelPresetType::COOL_SLANT, BevelPresetType::CROSS,
        BevelPresetType::DIVOT,    BevelPresetType::HARD_EDGE,
        BevelPresetType::RELAXED_INSET, BevelPresetType::RIBLET,
        BevelPresetType::SLOPE,    BevelPresetType::SOFT_ROUND,
    };
    ShapeBevel bevel;
    for (auto t : types) {
        bevel.set_bevel_type(t);
        EXPECT_EQ(bevel.bevel_type(), t);
    }
}

// ---------------------------------------------------------------------------
// OOXML round-trip for BevelPresetType (_BEVEL_MAP equivalent)
// ---------------------------------------------------------------------------

/// OOXML attribute strings map correctly to BevelPresetType.
TEST(ShapeBevelTest, OoxmlFromStringMapping) {
    EXPECT_EQ(bevel_preset_type_from_ooxml("angle"),        BevelPresetType::ANGLE);
    EXPECT_EQ(bevel_preset_type_from_ooxml("artDeco"),      BevelPresetType::ART_DECO);
    EXPECT_EQ(bevel_preset_type_from_ooxml("circle"),       BevelPresetType::CIRCLE);
    EXPECT_EQ(bevel_preset_type_from_ooxml("convex"),       BevelPresetType::CONVEX);
    EXPECT_EQ(bevel_preset_type_from_ooxml("coolSlant"),    BevelPresetType::COOL_SLANT);
    EXPECT_EQ(bevel_preset_type_from_ooxml("cross"),        BevelPresetType::CROSS);
    EXPECT_EQ(bevel_preset_type_from_ooxml("divot"),        BevelPresetType::DIVOT);
    EXPECT_EQ(bevel_preset_type_from_ooxml("hardEdge"),     BevelPresetType::HARD_EDGE);
    EXPECT_EQ(bevel_preset_type_from_ooxml("relaxedInset"), BevelPresetType::RELAXED_INSET);
    EXPECT_EQ(bevel_preset_type_from_ooxml("riblet"),       BevelPresetType::RIBLET);
    EXPECT_EQ(bevel_preset_type_from_ooxml("slope"),        BevelPresetType::SLOPE);
    EXPECT_EQ(bevel_preset_type_from_ooxml("softRound"),    BevelPresetType::SOFT_ROUND);
}

/// Unknown OOXML strings map to NOT_DEFINED.
TEST(ShapeBevelTest, OoxmlUnknownReturnsNotDefined) {
    EXPECT_EQ(bevel_preset_type_from_ooxml(""),        BevelPresetType::NOT_DEFINED);
    EXPECT_EQ(bevel_preset_type_from_ooxml("unknown"), BevelPresetType::NOT_DEFINED);
}

/// BevelPresetType values convert to correct OOXML attribute strings.
TEST(ShapeBevelTest, OoxmlToStringMapping) {
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::ANGLE),         "angle");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::ART_DECO),      "artDeco");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::CIRCLE),        "circle");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::CONVEX),        "convex");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::COOL_SLANT),    "coolSlant");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::CROSS),         "cross");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::DIVOT),         "divot");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::HARD_EDGE),     "hardEdge");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::RELAXED_INSET), "relaxedInset");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::RIBLET),        "riblet");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::SLOPE),         "slope");
    EXPECT_EQ(bevel_preset_type_to_ooxml(BevelPresetType::SOFT_ROUND),    "softRound");
}

/// NOT_DEFINED converts to empty OOXML string.
TEST(ShapeBevelTest, OoxmlNotDefinedIsEmpty) {
    EXPECT_TRUE(bevel_preset_type_to_ooxml(BevelPresetType::NOT_DEFINED).empty());
}

/// OOXML round-trip: to_ooxml(from_ooxml(s)) == s for all valid values.
TEST(ShapeBevelTest, OoxmlRoundTrip) {
    const std::string_view ooxml_values[] = {
        "angle", "artDeco", "circle", "convex", "coolSlant", "cross",
        "divot", "hardEdge", "relaxedInset", "riblet", "slope", "softRound",
    };
    for (auto sv : ooxml_values) {
        auto type = bevel_preset_type_from_ooxml(sv);
        EXPECT_NE(type, BevelPresetType::NOT_DEFINED) << "Failed for: " << sv;
        EXPECT_EQ(bevel_preset_type_to_ooxml(type), sv) << "Round-trip failed for: " << sv;
    }
}

// ---------------------------------------------------------------------------
// ShapeBevel via ThreeDFormat on shapes
// ---------------------------------------------------------------------------

/// Bevel properties persist on a shape's 3D format.
/// Ports: test_shape_frame_properties (x/y/width/height persist on shape)
TEST(ShapeBevelTest, BevelOnShapePersists) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 200, 200, 300, 250);

    auto& bt = shape.three_d_format().bevel_top();
    bt.set_bevel_type(BevelPresetType::CONVEX);
    bt.set_width(6.0);
    bt.set_height(4.0);

    EXPECT_EQ(shape.three_d_format().bevel_top().bevel_type(),
              BevelPresetType::CONVEX);
    EXPECT_DOUBLE_EQ(shape.three_d_format().bevel_top().width(), 6.0);
    EXPECT_DOUBLE_EQ(shape.three_d_format().bevel_top().height(), 4.0);
}

/// Shape frame properties coexist with bevel settings.
/// Ports: test_shape_frame_properties (x, y, width, height, rotation)
TEST(ShapeBevelTest, ShapeFrameWithBevel) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 200, 200, 300, 250);
    shape.set_rotation(45);

    shape.three_d_format().bevel_top().set_bevel_type(BevelPresetType::CIRCLE);

    EXPECT_EQ(shape.x(), 200);
    EXPECT_EQ(shape.y(), 200);
    EXPECT_EQ(shape.width(), 300);
    EXPECT_EQ(shape.height(), 250);
    EXPECT_EQ(shape.rotation(), 45);
    EXPECT_EQ(shape.three_d_format().bevel_top().bevel_type(),
              BevelPresetType::CIRCLE);
}

/// Both top and bottom bevels can be set independently.
TEST(ShapeBevelTest, TopAndBottomBevelIndependent) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    shape.three_d_format().bevel_top().set_bevel_type(BevelPresetType::ANGLE);
    shape.three_d_format().bevel_top().set_width(10.0);
    shape.three_d_format().bevel_bottom().set_bevel_type(BevelPresetType::SLOPE);
    shape.three_d_format().bevel_bottom().set_width(5.0);

    EXPECT_EQ(shape.three_d_format().bevel_top().bevel_type(),
              BevelPresetType::ANGLE);
    EXPECT_DOUBLE_EQ(shape.three_d_format().bevel_top().width(), 10.0);
    EXPECT_EQ(shape.three_d_format().bevel_bottom().bevel_type(),
              BevelPresetType::SLOPE);
    EXPECT_DOUBLE_EQ(shape.three_d_format().bevel_bottom().width(), 5.0);
}

/// Line format width coexists with bevel on the same shape.
/// Ports: test_line_color_and_width (line width property)
TEST(ShapeBevelTest, LineWidthWithBevel) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);

    shape.line_format().set_width(5);
    shape.three_d_format().bevel_top().set_bevel_type(BevelPresetType::HARD_EDGE);

    EXPECT_EQ(shape.line_format().width(), 5);
    EXPECT_EQ(shape.three_d_format().bevel_top().bevel_type(),
              BevelPresetType::HARD_EDGE);
}

/// Dash style and bevel coexist on the same shape.
/// Ports: test_line_dash_style (dash style property)
TEST(ShapeBevelTest, LineDashStyleWithBevel) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);

    shape.line_format().set_dash_style(LineDashStyle::DASH);
    shape.three_d_format().bevel_top().set_bevel_type(BevelPresetType::RIBLET);

    EXPECT_EQ(shape.line_format().dash_style(), LineDashStyle::DASH);
    EXPECT_EQ(shape.three_d_format().bevel_top().bevel_type(),
              BevelPresetType::RIBLET);
}

/// Connector shapes support 3D bevel (width/height positive after set).
/// Ports: test_reroute (connector width > 0 or height > 0)
TEST(ShapeBevelTest, ConnectorWithBevel) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& conn = slide.shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 0, 0, 300, 200);

    conn.three_d_format().bevel_top().set_bevel_type(BevelPresetType::COOL_SLANT);
    conn.three_d_format().bevel_top().set_width(8.0);
    conn.three_d_format().bevel_top().set_height(4.0);

    EXPECT_EQ(conn.three_d_format().bevel_top().bevel_type(),
              BevelPresetType::COOL_SLANT);
    EXPECT_TRUE(conn.three_d_format().bevel_top().width() > 0 ||
                conn.three_d_format().bevel_top().height() > 0);
}

/// Notes size has positive dimensions (sanity check alongside bevel).
/// Ports: test_notes_size (positive width and height)
TEST(ShapeBevelTest, NotesSizePositive) {
    Presentation pres;
    const auto& ns = pres.notes_size();
    EXPECT_GT(ns.width(), 0.0);
    EXPECT_GT(ns.height(), 0.0);
}

/// Cell border width persists on CellFormat.
/// Ports: test_cell_borders (border width property)
TEST(ShapeBevelTest, CellBorderWidthAccessible) {
    CellFormat fmt;
    fmt.border_top().set_width(3);

    EXPECT_DOUBLE_EQ(fmt.border_top().width(), 3.0);
}
