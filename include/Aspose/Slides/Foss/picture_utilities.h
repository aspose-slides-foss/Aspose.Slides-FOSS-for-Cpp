// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>
#include <string_view>

#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

class PPImage;
class Slide;

namespace Internal::pptx { class SlidePart; }

namespace picture {

/// Resolves pending image references on picture frame shapes within a slide.
///
/// Iterates through all shapes on the given slide, finds PictureFrame shapes
/// that have a pending part name, and resolves each one by searching the
/// presentation's image collection for a PPImage with a matching part name.
/// Once resolved, the PictureFrame's image pointer is set and the pending
/// part name is cleared.
void flush_pending_blip_images(Slide& slide);

/// Computes a relative path from a directory to a target path.
/// @param from_dir The source directory (e.g., "ppt/slides").
/// @param to_path The target file path (e.g., "ppt/media/image1.png").
/// @return The relative path (e.g., "../media/image1.png").
[[nodiscard]] std::string compute_relative_path(std::string_view from_dir,
                                                std::string_view to_path);

/// Sets an image relationship on a blip XML element.
///
/// Finds or creates an OPC relationship for the given image in the slide part,
/// then sets the r:embed attribute on the blip element to reference it.
/// @param blip The a:blip XML element to update.
/// @param slide_part The slide part owning the relationships.
/// @param pp_image The image whose part name is the relationship target.
void set_blip_image(pugi::xml_node blip,
                    Internal::pptx::SlidePart& slide_part,
                    const PPImage& pp_image);

} // namespace picture

} // namespace Aspose::Slides::Foss
