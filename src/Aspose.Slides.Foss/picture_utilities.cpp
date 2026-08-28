// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/picture_utilities.h>

#include <algorithm>
#include <vector>

#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>
#include <Aspose/Slides/Foss/i_presentation.h>
#include <Aspose/Slides/Foss/image_collection.h>
#include <Aspose/Slides/Foss/picture_frame.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/slide.h>

namespace Aspose::Slides::Foss::picture {

void flush_pending_blip_images(Slide& slide) {
    auto* presentation = slide.presentation();
    if (!presentation) {
        return;
    }

    auto& images = presentation->images();
    auto& shapes = slide.shapes();

    for (std::size_t i = 0; i < shapes.size(); ++i) {
        auto* pf = dynamic_cast<PictureFrame*>(&shapes[i]);
        if (!pf) {
            continue;
        }

        const auto pending = pf->pending_part_name();
        if (pending.empty()) {
            continue;
        }

        pf->clear_pending_part_name();

        for (auto& img_ptr : images) {
            if (img_ptr->part_name() == pending) {
                pf->set_pp_image(img_ptr.get());
                break;
            }
        }
    }
}

namespace {

/// Split a path string by '/' into components.
std::vector<std::string_view> split_path(std::string_view path) {
    std::vector<std::string_view> parts;
    std::size_t start = 0;
    while (start < path.size()) {
        auto pos = path.find('/', start);
        if (pos == std::string_view::npos) {
            parts.push_back(path.substr(start));
            break;
        }
        if (pos > start) {
            parts.push_back(path.substr(start, pos - start));
        }
        start = pos + 1;
    }
    return parts;
}

} // anonymous namespace

std::string compute_relative_path(std::string_view from_dir,
                                  std::string_view to_path) {
    auto from_parts = split_path(from_dir);
    auto to_parts = split_path(to_path);

    // Find common prefix length.
    std::size_t common = 0;
    for (std::size_t i = 0; i < std::min(from_parts.size(), to_parts.size()); ++i) {
        if (from_parts[i] == to_parts[i]) {
            ++common;
        } else {
            break;
        }
    }

    // Build relative path: go up from from_dir, then descend to to_path.
    std::string result;
    std::size_t up = from_parts.size() - common;
    for (std::size_t i = 0; i < up; ++i) {
        if (!result.empty()) result += '/';
        result += "..";
    }
    for (std::size_t i = common; i < to_parts.size(); ++i) {
        if (!result.empty()) result += '/';
        result += to_parts[i];
    }
    return result;
}

void set_blip_image(pugi::xml_node blip,
                    Internal::pptx::SlidePart& slide_part,
                    const PPImage& pp_image) {
    // Compute the directory of the slide part.
    const auto& part_name = slide_part.part_name();
    auto slash_pos = part_name.rfind('/');
    std::string slide_dir = (slash_pos != std::string::npos)
        ? part_name.substr(0, slash_pos)
        : "";

    const auto& image_path = pp_image.part_name();
    auto relative_target = compute_relative_path(slide_dir, image_path);

    // Check if a relationship to this image already exists.
    auto existing_rels = slide_part.rels_manager().get_relationships_by_type(
        Internal::opc::rel_types::kImage);

    std::string embed_id;
    for (const auto& rel : existing_rels) {
        if (slide_part.resolve_target(rel.target) == image_path) {
            embed_id = rel.id;
            break;
        }
    }

    // Create relationship if none found.
    if (embed_id.empty()) {
        embed_id = slide_part.rels_manager().add_relationship(
            Internal::opc::rel_types::kImage, relative_target);
        slide_part.rels_manager().save();
    }

    // Set the r:embed attribute on the blip element.
    //
    // Read under either spelling, but always write the literal prefixed name:
    // pugixml stores names verbatim, so appending the Clark-notation constant
    // would put "{uri}embed" in the file and the part would stop being XML.
    auto attr = blip.attribute("r:embed");
    if (!attr) attr = blip.attribute(Internal::pptx::Attributes::kREmbed.c_str());
    if (!attr) attr = blip.append_attribute("r:embed");
    attr.set_value(embed_id.c_str());

    slide_part.save();
}

} // namespace Aspose::Slides::Foss::picture
