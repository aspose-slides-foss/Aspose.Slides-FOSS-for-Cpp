// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>
#include <string>

#include <Aspose/Slides/Foss/base_slide.h>
#include <Aspose/Slides/Foss/i_layout_slide.h>
#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/slide_layout_type.h>

namespace Aspose::Slides::Foss::Internal::opc { class OpcPackage; }
namespace Aspose::Slides::Foss::Internal::pptx { class LayoutSlidePart; }

namespace Aspose::Slides::Foss {

class Presentation;

/// Callable that resolves a master part name to a MasterSlide pointer.
using MasterResolver = std::function<IMasterSlide*(const std::string&)>;

/// Represents a layout slide.
class LayoutSlide final : public BaseSlide, public ILayoutSlide {
public:
    LayoutSlide() = default;

    /// Constructs a layout slide belonging to the given presentation.
    explicit LayoutSlide(Presentation* presentation) noexcept;

    /// Internal initialization from OPC package data.
    ///
    /// Links the layout slide to its OPC part and master resolver so that
    /// property accessors can delegate to the underlying XML data.
    ///
    /// @param presentation   The parent Presentation object.
    /// @param package        The OPC package containing the presentation.
    /// @param part_name      The part name of this layout slide.
    /// @param layout_part    The parsed LayoutSlidePart.
    /// @param master_resolver Callable that resolves a master part name to a MasterSlide.
    void init_internal(Presentation* presentation,
                       Internal::opc::OpcPackage& package,
                       std::string part_name,
                       Internal::pptx::LayoutSlidePart& layout_part,
                       MasterResolver master_resolver = nullptr);

    /// Returns the layout type. Read-only.
    [[nodiscard]] SlideLayoutType layout_type() const noexcept override { return layout_type_; }

    /// Sets the layout type.
    void set_layout_type(SlideLayoutType value) noexcept { layout_type_ = value; }

    /// Returns the parent master slide. Read/write.
    [[nodiscard]] IMasterSlide* master_slide() const noexcept override { return master_slide_; }

    /// Sets the parent master slide.
    void set_master_slide(IMasterSlide* value) noexcept override { master_slide_ = value; }

    /// Returns the collection of shapes.
    [[nodiscard]] ShapeCollection& shapes() override { return shapes_; }
    [[nodiscard]] const ShapeCollection& shapes() const override { return shapes_; }

private:
    SlideLayoutType layout_type_ = SlideLayoutType::CUSTOM;
    IMasterSlide* master_slide_ = nullptr;
    ShapeCollection shapes_;

    // Internal OPC state (set by init_internal)
    Internal::opc::OpcPackage* package_ = nullptr;
    std::string part_name_;
    Internal::pptx::LayoutSlidePart* layout_part_ = nullptr;
    MasterResolver master_resolver_;
};

} // namespace Aspose::Slides::Foss
