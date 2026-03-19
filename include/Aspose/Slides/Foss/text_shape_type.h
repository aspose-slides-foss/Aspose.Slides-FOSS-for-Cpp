// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents text wrapping shape.
enum class TextShapeType {
    NOT_DEFINED,
    NONE,
    PLAIN,
    STOP,
    TRIANGLE,
    TRIANGLE_INVERTED,
    CHEVRON,
    CHEVRON_INVERTED,
    RING_INSIDE,
    RING_OUTSIDE,
    ARCH_UP,
    ARCH_DOWN,
    CIRCLE,
    BUTTON,
    ARCH_UP_POUR,
    ARCH_DOWN_POUR,
    CIRCLE_POUR,
    BUTTON_POUR,
    CURVE_UP,
    CURVE_DOWN,
    CAN_UP,
    CAN_DOWN,
    WAVE1,
    WAVE2,
    DOUBLE_WAVE1,
    WAVE4,
    INFLATE,
    DEFLATE,
    INFLATE_BOTTOM,
    DEFLATE_BOTTOM,
    INFLATE_TOP,
    DEFLATE_TOP,
    DEFLATE_INFLATE,
    DEFLATE_INFLATE_DEFLATE,
    FADE_RIGHT,
    FADE_LEFT,
    FADE_UP,
    FADE_DOWN,
    SLANT_UP,
    SLANT_DOWN,
    CASCADE_UP,
    CASCADE_DOWN,
    CUSTOM,
};

/// Returns the string representation of a TextShapeType value.
constexpr std::string_view to_string_view(TextShapeType value) {
    switch (value) {
        case TextShapeType::NOT_DEFINED: return "NotDefined";
        case TextShapeType::NONE: return "None";
        case TextShapeType::PLAIN: return "Plain";
        case TextShapeType::STOP: return "Stop";
        case TextShapeType::TRIANGLE: return "Triangle";
        case TextShapeType::TRIANGLE_INVERTED: return "TriangleInverted";
        case TextShapeType::CHEVRON: return "Chevron";
        case TextShapeType::CHEVRON_INVERTED: return "ChevronInverted";
        case TextShapeType::RING_INSIDE: return "RingInside";
        case TextShapeType::RING_OUTSIDE: return "RingOutside";
        case TextShapeType::ARCH_UP: return "ArchUp";
        case TextShapeType::ARCH_DOWN: return "ArchDown";
        case TextShapeType::CIRCLE: return "Circle";
        case TextShapeType::BUTTON: return "Button";
        case TextShapeType::ARCH_UP_POUR: return "ArchUpPour";
        case TextShapeType::ARCH_DOWN_POUR: return "ArchDownPour";
        case TextShapeType::CIRCLE_POUR: return "CirclePour";
        case TextShapeType::BUTTON_POUR: return "ButtonPour";
        case TextShapeType::CURVE_UP: return "CurveUp";
        case TextShapeType::CURVE_DOWN: return "CurveDown";
        case TextShapeType::CAN_UP: return "CanUp";
        case TextShapeType::CAN_DOWN: return "CanDown";
        case TextShapeType::WAVE1: return "Wave1";
        case TextShapeType::WAVE2: return "Wave2";
        case TextShapeType::DOUBLE_WAVE1: return "DoubleWave1";
        case TextShapeType::WAVE4: return "Wave4";
        case TextShapeType::INFLATE: return "Inflate";
        case TextShapeType::DEFLATE: return "Deflate";
        case TextShapeType::INFLATE_BOTTOM: return "InflateBottom";
        case TextShapeType::DEFLATE_BOTTOM: return "DeflateBottom";
        case TextShapeType::INFLATE_TOP: return "InflateTop";
        case TextShapeType::DEFLATE_TOP: return "DeflateTop";
        case TextShapeType::DEFLATE_INFLATE: return "DeflateInflate";
        case TextShapeType::DEFLATE_INFLATE_DEFLATE: return "DeflateInflateDeflate";
        case TextShapeType::FADE_RIGHT: return "FadeRight";
        case TextShapeType::FADE_LEFT: return "FadeLeft";
        case TextShapeType::FADE_UP: return "FadeUp";
        case TextShapeType::FADE_DOWN: return "FadeDown";
        case TextShapeType::SLANT_UP: return "SlantUp";
        case TextShapeType::SLANT_DOWN: return "SlantDown";
        case TextShapeType::CASCADE_UP: return "CascadeUp";
        case TextShapeType::CASCADE_DOWN: return "CascadeDown";
        case TextShapeType::CUSTOM: return "Custom";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
