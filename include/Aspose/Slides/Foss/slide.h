// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <Aspose/Slides/Foss/base_slide.h>
#include <Aspose/Slides/Foss/i_slide.h>
#include <Aspose/Slides/Foss/i_slide_component.h>
#include <Aspose/Slides/Foss/notes_slide_manager.h>
#include <Aspose/Slides/Foss/shape_collection.h>

namespace Aspose::Slides::Foss::Internal::opc { class OpcPackage; }
namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class Comment;
class CommentAuthor;
class ILayoutSlide;
class LayoutSlide;
class Presentation;
struct SlideReference;

/// Represents a slide in a presentation.
class Slide final : public BaseSlide, public ISlide, public ISlideComponent {
public:
    /// Constructs a slide belonging to the given presentation.
    explicit Slide(Presentation* presentation) noexcept;

    // -- IPresentationComponent --

    /// Returns the parent presentation.
    [[nodiscard]] IPresentation* presentation() override;
    [[nodiscard]] const IPresentation* presentation() const override;

    // -- ISlideComponent --

    /// Returns this slide as the base slide.
    [[nodiscard]] IBaseSlide* slide() override;
    [[nodiscard]] const IBaseSlide* slide() const override;

    /// Allows to get base IPresentationComponent interface.
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override;
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override;

    // -- ISlide --

    /// Returns the collection of shapes on this slide.
    [[nodiscard]] ShapeCollection& shapes() noexcept override { return shapes_; }
    [[nodiscard]] const ShapeCollection& shapes() const noexcept override { return shapes_; }

    /// Returns the number of the slide. Read/write.
    [[nodiscard]] int slide_number() const noexcept override { return slide_number_; }
    /// Sets the number of the slide.
    void set_slide_number(int value) noexcept override { slide_number_ = value; }

    /// Determines whether the specified slide is hidden during a slide show. Read/write.
    [[nodiscard]] bool hidden() const noexcept override { return hidden_; }
    /// Sets whether the slide is hidden.
    void set_hidden(bool value) noexcept override { hidden_ = value; }

    /// Returns the layout slide for the current slide. Read/write.
    [[nodiscard]] ILayoutSlide* layout_slide() const noexcept override { return layout_slide_; }
    /// Sets the layout slide for the current slide.
    void set_layout_slide(ILayoutSlide* value) noexcept override { layout_slide_ = value; }

    /// Returns the notes slide manager. Read-only.
    [[nodiscard]] INotesSlideManager& notes_slide_manager() override {
        return notes_slide_manager_;
    }
    [[nodiscard]] const INotesSlideManager& notes_slide_manager() const override {
        return notes_slide_manager_;
    }

    /// Returns comments on this slide, optionally filtered by author.
    /// If author is nullptr, returns all comments on this slide.
    [[nodiscard]] std::vector<Comment*> get_slide_comments(
        CommentAuthor* author) const override;

    /// Removes this slide from the presentation.
    void remove() override;

    /// Returns a reference to this as ISlideComponent.
    [[nodiscard]] ISlideComponent& as_i_slide_component();
    [[nodiscard]] const ISlideComponent& as_i_slide_component() const;

    // -- Internal OPC-level initialization --

    /// Layout resolver callback: maps a layout part name to a LayoutSlide pointer.
    using LayoutResolver = std::function<LayoutSlide*(std::string_view)>;

    /// Internal initialization from OPC package data.
    /// @param presentation The parent Presentation object.
    /// @param package The OPC package (must outlive this slide).
    /// @param part_name The part name of this slide (e.g., "ppt/slides/slide1.xml").
    /// @param slide_ref The SlideReference from presentation.xml.
    /// @param slide_part The parsed SlidePart (must outlive this slide).
    /// @param layout_resolver Optional callable mapping layout part name to LayoutSlide*.
    void init_internal(Presentation* presentation,
                       Internal::opc::OpcPackage* package,
                       std::string_view part_name,
                       const SlideReference& slide_ref,
                       Internal::pptx::SlidePart* slide_part,
                       LayoutResolver layout_resolver = nullptr);

    /// Returns the OPC part name for this slide, or empty if not OPC-loaded.
    [[nodiscard]] const std::string& part_name() const noexcept { return part_name_; }

    /// Returns the OPC package, or nullptr if not OPC-loaded.
    [[nodiscard]] Internal::opc::OpcPackage* opc_package() const noexcept { return package_; }

    /// Returns the SlidePart, or nullptr if not OPC-loaded.
    [[nodiscard]] Internal::pptx::SlidePart* slide_part() const noexcept { return slide_part_; }

protected:
    /// Returns the OPC slide part for this slide.
    [[nodiscard]] SlidePartVariant get_slide_part() override;

private:
    Presentation* presentation_;
    ShapeCollection shapes_;
    NotesSlideManager notes_slide_manager_;
    ILayoutSlide* layout_slide_ = nullptr;
    int slide_number_ = 1;
    bool hidden_ = false;

    // OPC-level state (set by init_internal)
    Internal::opc::OpcPackage* package_ = nullptr;
    std::string part_name_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    LayoutResolver layout_resolver_;
};

} // namespace Aspose::Slides::Foss
