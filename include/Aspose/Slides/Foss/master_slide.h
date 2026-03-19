// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>
#include <vector>

#include <Aspose/Slides/Foss/base_slide.h>
#include <Aspose/Slides/Foss/i_master_slide.h>
#include <Aspose/Slides/Foss/master_layout_slide_collection.h>
#include <Aspose/Slides/Foss/shape_collection.h>

namespace Aspose::Slides::Foss::Internal::opc { class OpcPackage; }
namespace Aspose::Slides::Foss::Internal::pptx { class MasterSlidePart; }

namespace Aspose::Slides::Foss {

class Presentation;
class ILayoutSlide;

/// Represents a master slide in a presentation.
class MasterSlide final : public BaseSlide, public IMasterSlide {
public:
    MasterSlide() = default;

    /// Internal initialization from OPC package data.
    ///
    /// Links the master slide to its OPC part so that property accessors
    /// can delegate to the underlying XML data.
    ///
    /// @param presentation  The parent Presentation object.
    /// @param package       The OPC package containing the presentation.
    /// @param part_name     The part name of this master slide.
    /// @param master_part   The parsed MasterSlidePart.
    /// @param layout_slides Non-owning pointers to layout slides belonging to this master.
    void init_internal(Presentation* presentation,
                       Internal::opc::OpcPackage& package,
                       std::string part_name,
                       Internal::pptx::MasterSlidePart& master_part,
                       std::vector<ILayoutSlide*> layout_slides = {});

    /// Returns the collection of shapes on this master slide.
    [[nodiscard]] ShapeCollection& shapes() override { return shapes_; }
    [[nodiscard]] const ShapeCollection& shapes() const override { return shapes_; }

    /// Returns the collection of child layout slides for this master slide. Read-only.
    [[nodiscard]] MasterLayoutSlideCollection& layout_slides() override { return layout_slides_; }
    [[nodiscard]] const MasterLayoutSlideCollection& layout_slides() const override { return layout_slides_; }

protected:
    /// Returns the master slide part for this slide.
    [[nodiscard]] SlidePartVariant get_slide_part() override;

private:
    ShapeCollection shapes_;
    MasterLayoutSlideCollection layout_slides_;

    // Internal OPC state (set by init_internal)
    Internal::opc::OpcPackage* package_ = nullptr;
    std::string part_name_;
    Internal::pptx::MasterSlidePart* master_part_ = nullptr;
};

} // namespace Aspose::Slides::Foss
