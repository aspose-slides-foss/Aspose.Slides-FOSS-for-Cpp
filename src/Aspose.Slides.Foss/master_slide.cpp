// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/master_slide.h>

#include <Aspose/Slides/Foss/presentation.h>

namespace Aspose::Slides::Foss {

void MasterSlide::init_internal(Presentation* presentation,
                                Internal::opc::OpcPackage& package,
                                std::string part_name,
                                Internal::pptx::MasterSlidePart& master_part,
                                std::vector<ILayoutSlide*> layout_slides) {
    set_presentation(presentation);
    package_ = &package;
    part_name_ = std::move(part_name);
    master_part_ = &master_part;
    layout_slides_.init_internal(std::move(layout_slides));
}

SlidePartVariant MasterSlide::get_slide_part() {
    return master_part_;
}

} // namespace Aspose::Slides::Foss
