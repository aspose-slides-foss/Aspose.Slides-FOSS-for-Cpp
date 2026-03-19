// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/layout_slide.h>

#include <Aspose/Slides/Foss/presentation.h>

namespace Aspose::Slides::Foss {

LayoutSlide::LayoutSlide(Presentation* presentation) noexcept
    : BaseSlide(presentation) {}

void LayoutSlide::init_internal(Presentation* presentation,
                                Internal::opc::OpcPackage& package,
                                std::string part_name,
                                Internal::pptx::LayoutSlidePart& layout_part,
                                MasterResolver master_resolver) {
    set_presentation(presentation);
    package_ = &package;
    part_name_ = std::move(part_name);
    layout_part_ = &layout_part;
    master_resolver_ = std::move(master_resolver);
    master_slide_ = nullptr;
}

} // namespace Aspose::Slides::Foss
