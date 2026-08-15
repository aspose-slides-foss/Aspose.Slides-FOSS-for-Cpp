// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file effect_color.h
/// @brief The colour child a shadow or glow element is required to carry.
///
/// `CT_OuterShadowEffect`, `CT_InnerShadowEffect`, `CT_PresetShadowEffect` and
/// `CT_GlowEffect` each declare exactly one `EG_ColorChoice` child, and it is
/// not optional. An effect element written without one is refused by
/// PowerPoint outright, so a newly created element has to be given a colour
/// before it is left in the tree.

#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Read the colour child of @p element into @p format.
/// @return true when @p element carried one.
bool read_effect_color(pugi::xml_node element, SimpleColorFormat& format);

/// Replace the colour child of @p element with @p format's colour.
///
/// Written as `<a:srgbClr val="RRGGBB"/>`, with an `<a:alpha>` child when the
/// colour is not fully opaque.
void write_effect_color(pugi::xml_node element,
                        const SimpleColorFormat& format);

} // namespace Aspose::Slides::Foss::Internal::pptx
