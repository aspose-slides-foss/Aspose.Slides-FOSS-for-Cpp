// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/shape_type.h>

using namespace Aspose::Slides::Foss;

// --- Values used by connector tests (test_connector.py) ---

TEST(ShapeTypeTest, StraightConnector1Value) {
    ShapeType st = ShapeType::STRAIGHT_CONNECTOR1;
    EXPECT_EQ(st, ShapeType::STRAIGHT_CONNECTOR1);
    EXPECT_EQ(to_string_view(st), "StraightConnector1");
}

TEST(ShapeTypeTest, BentConnector3Value) {
    EXPECT_EQ(to_string_view(ShapeType::BENT_CONNECTOR3), "BentConnector3");
}

TEST(ShapeTypeTest, RectangleValue) {
    EXPECT_EQ(to_string_view(ShapeType::RECTANGLE), "Rectangle");
}

TEST(ShapeTypeTest, EllipseValue) {
    EXPECT_EQ(to_string_view(ShapeType::ELLIPSE), "Ellipse");
}

// --- Core enum identity tests ---

TEST(ShapeTypeTest, NotDefinedIsDefault) {
    ShapeType st{};
    EXPECT_EQ(st, ShapeType::NOT_DEFINED);
    EXPECT_EQ(to_string_view(st), "NotDefined");
}

TEST(ShapeTypeTest, CustomValue) {
    EXPECT_EQ(to_string_view(ShapeType::CUSTOM), "Custom");
}

TEST(ShapeTypeTest, AllValuesDistinct) {
    EXPECT_NE(ShapeType::NOT_DEFINED, ShapeType::CUSTOM);
    EXPECT_NE(ShapeType::LINE, ShapeType::LINE_INVERSE);
    EXPECT_NE(ShapeType::TRIANGLE, ShapeType::RIGHT_TRIANGLE);
    EXPECT_NE(ShapeType::RECTANGLE, ShapeType::DIAMOND);
    EXPECT_NE(ShapeType::STRAIGHT_CONNECTOR1, ShapeType::BENT_CONNECTOR3);
}

// --- Sampling across shape categories ---

TEST(ShapeTypeTest, BasicShapes) {
    EXPECT_EQ(to_string_view(ShapeType::LINE), "Line");
    EXPECT_EQ(to_string_view(ShapeType::TRIANGLE), "Triangle");
    EXPECT_EQ(to_string_view(ShapeType::DIAMOND), "Diamond");
    EXPECT_EQ(to_string_view(ShapeType::PENTAGON), "Pentagon");
    EXPECT_EQ(to_string_view(ShapeType::HEXAGON), "Hexagon");
    EXPECT_EQ(to_string_view(ShapeType::OCTAGON), "Octagon");
}

TEST(ShapeTypeTest, Stars) {
    EXPECT_EQ(to_string_view(ShapeType::FOUR_POINTED_STAR), "FourPointedStar");
    EXPECT_EQ(to_string_view(ShapeType::FIVE_POINTED_STAR), "FivePointedStar");
    EXPECT_EQ(to_string_view(ShapeType::TWELVE_POINTED_STAR), "TwelvePointedStar");
    EXPECT_EQ(to_string_view(ShapeType::THIRTY_TWO_POINTED_STAR), "ThirtyTwoPointedStar");
}

TEST(ShapeTypeTest, Arrows) {
    EXPECT_EQ(to_string_view(ShapeType::RIGHT_ARROW), "RightArrow");
    EXPECT_EQ(to_string_view(ShapeType::LEFT_ARROW), "LeftArrow");
    EXPECT_EQ(to_string_view(ShapeType::UP_ARROW), "UpArrow");
    EXPECT_EQ(to_string_view(ShapeType::DOWN_ARROW), "DownArrow");
    EXPECT_EQ(to_string_view(ShapeType::QUAD_ARROW), "QuadArrow");
    EXPECT_EQ(to_string_view(ShapeType::U_TURN_ARROW), "UTurnArrow");
}

TEST(ShapeTypeTest, Connectors) {
    EXPECT_EQ(to_string_view(ShapeType::BENT_CONNECTOR2), "BentConnector2");
    EXPECT_EQ(to_string_view(ShapeType::BENT_CONNECTOR4), "BentConnector4");
    EXPECT_EQ(to_string_view(ShapeType::BENT_CONNECTOR5), "BentConnector5");
    EXPECT_EQ(to_string_view(ShapeType::CURVED_CONNECTOR2), "CurvedConnector2");
    EXPECT_EQ(to_string_view(ShapeType::CURVED_CONNECTOR5), "CurvedConnector5");
}

TEST(ShapeTypeTest, Callouts) {
    EXPECT_EQ(to_string_view(ShapeType::CALLOUT1), "Callout1");
    EXPECT_EQ(to_string_view(ShapeType::CALLOUT_1_WITH_ACCENT), "Callout1WithAccent");
    EXPECT_EQ(to_string_view(ShapeType::CALLOUT_1_WITH_BORDER), "Callout1WithBorder");
    EXPECT_EQ(to_string_view(ShapeType::CALLOUT_1_WITH_BORDER_AND_ACCENT), "Callout1WithBorderAndAccent");
    EXPECT_EQ(to_string_view(ShapeType::CALLOUT_WEDGE_RECTANGLE), "CalloutWedgeRectangle");
    EXPECT_EQ(to_string_view(ShapeType::CALLOUT_WEDGE_ELLIPSE), "CalloutWedgeEllipse");
    EXPECT_EQ(to_string_view(ShapeType::CALLOUT_CLOUD), "CalloutCloud");
}

TEST(ShapeTypeTest, FlowchartShapes) {
    EXPECT_EQ(to_string_view(ShapeType::PROCESS_FLOW), "ProcessFlow");
    EXPECT_EQ(to_string_view(ShapeType::DECISION_FLOW), "DecisionFlow");
    EXPECT_EQ(to_string_view(ShapeType::TERMINATOR_FLOW), "TerminatorFlow");
    EXPECT_EQ(to_string_view(ShapeType::DOCUMENT_FLOW), "DocumentFlow");
}

TEST(ShapeTypeTest, MathSymbols) {
    EXPECT_EQ(to_string_view(ShapeType::PLUS_MATH), "PlusMath");
    EXPECT_EQ(to_string_view(ShapeType::MINUS_MATH), "MinusMath");
    EXPECT_EQ(to_string_view(ShapeType::MULTIPLY_MATH), "MultiplyMath");
    EXPECT_EQ(to_string_view(ShapeType::DIVIDE_MATH), "DivideMath");
    EXPECT_EQ(to_string_view(ShapeType::EQUAL_MATH), "EqualMath");
    EXPECT_EQ(to_string_view(ShapeType::NOT_EQUAL_MATH), "NotEqualMath");
}

TEST(ShapeTypeTest, RoundCornerRectangles) {
    EXPECT_EQ(to_string_view(ShapeType::ROUND_CORNER_RECTANGLE), "RoundCornerRectangle");
    EXPECT_EQ(to_string_view(ShapeType::ONE_ROUND_CORNER_RECTANGLE), "OneRoundCornerRectangle");
    EXPECT_EQ(to_string_view(ShapeType::TWO_SAMESIDE_ROUND_CORNER_RECTANGLE), "TwoSamesideRoundCornerRectangle");
    EXPECT_EQ(to_string_view(ShapeType::TWO_DIAGONAL_ROUND_CORNER_RECTANGLE), "TwoDiagonalRoundCornerRectangle");
}

TEST(ShapeTypeTest, SnipCornerRectangles) {
    EXPECT_EQ(to_string_view(ShapeType::ONE_SNIP_CORNER_RECTANGLE), "OneSnipCornerRectangle");
    EXPECT_EQ(to_string_view(ShapeType::TWO_SAMESIDE_SNIP_CORNER_RECTANGLE), "TwoSamesideSnipCornerRectangle");
    EXPECT_EQ(to_string_view(ShapeType::TWO_DIAGONAL_SNIP_CORNER_RECTANGLE), "TwoDiagonalSnipCornerRectangle");
    EXPECT_EQ(to_string_view(ShapeType::ONE_SNIP_ONE_ROUND_CORNER_RECTANGLE), "OneSnipOneRoundCornerRectangle");
}

TEST(ShapeTypeTest, MiscShapes) {
    EXPECT_EQ(to_string_view(ShapeType::HEART), "Heart");
    EXPECT_EQ(to_string_view(ShapeType::LIGHTNING_BOLT), "LightningBolt");
    EXPECT_EQ(to_string_view(ShapeType::SUN), "Sun");
    EXPECT_EQ(to_string_view(ShapeType::CLOUD), "Cloud");
    EXPECT_EQ(to_string_view(ShapeType::GEAR6), "Gear6");
    EXPECT_EQ(to_string_view(ShapeType::FUNNEL), "Funnel");
    EXPECT_EQ(to_string_view(ShapeType::CHART_PLUS), "ChartPlus");
}

TEST(ShapeTypeTest, Buttons) {
    EXPECT_EQ(to_string_view(ShapeType::BLANK_BUTTON), "BlankButton");
    EXPECT_EQ(to_string_view(ShapeType::HOME_BUTTON), "HomeButton");
    EXPECT_EQ(to_string_view(ShapeType::MOVIE_BUTTON), "MovieButton");
}
