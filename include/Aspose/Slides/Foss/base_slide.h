// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include <Aspose/Slides/Foss/i_base_slide.h>

namespace Aspose::Slides::Foss::Internal::pptx {
class SlidePart;
class LayoutSlidePart;
class MasterSlidePart;
class NotesSlidePart;
} // namespace Aspose::Slides::Foss::Internal::pptx

namespace Aspose::Slides::Foss {

class ShapeCollection;

/// Variant representing the different slide part types, or std::monostate for none.
using SlidePartVariant = std::variant<
    std::monostate,
    Internal::pptx::SlidePart*,
    Internal::pptx::LayoutSlidePart*,
    Internal::pptx::MasterSlidePart*,
    Internal::pptx::NotesSlidePart*
>;

/// Base class for all slide types (Slide, LayoutSlide, MasterSlide).
/// Implements IBaseSlide, providing common data for all slide types.
class BaseSlide : public virtual IBaseSlide {
public:
    ~BaseSlide() override = default;

    /// Returns the collection of shapes on the slide.
    [[nodiscard]] ShapeCollection& shapes() override = 0;
    [[nodiscard]] const ShapeCollection& shapes() const override = 0;

    /// Returns the name of the slide. Read/write.
    [[nodiscard]] const std::string& name() const noexcept override { return name_; }
    void set_name(std::string value) override { name_ = std::move(value); }

    /// Returns the unique slide ID within the presentation. Read-only.
    [[nodiscard]] uint32_t slide_id() const noexcept override { return slide_id_; }

    /// Returns the parent presentation. Read-only.
    [[nodiscard]] IPresentation* presentation() override { return presentation_; }
    [[nodiscard]] const IPresentation* presentation() const override { return presentation_; }

protected:
    BaseSlide() = default;

    /// Constructs a BaseSlide with a parent presentation.
    explicit BaseSlide(IPresentation* presentation) noexcept
        : presentation_(presentation) {}

    /// Get the slide part object for this slide.
    ///
    /// Returns the OPC part associated with this slide (SlidePart,
    /// LayoutSlidePart, MasterSlidePart, or NotesSlidePart).
    /// Subclasses override this to return the appropriate part.
    /// The default implementation returns std::monostate (no part).
    [[nodiscard]] virtual SlidePartVariant get_slide_part() { return std::monostate{}; }

    void set_slide_id(uint32_t id) noexcept { slide_id_ = id; }
    void set_presentation(IPresentation* presentation) noexcept { presentation_ = presentation; }

private:
    std::string name_;
    uint32_t slide_id_ = 0;
    IPresentation* presentation_ = nullptr;
};

} // namespace Aspose::Slides::Foss
