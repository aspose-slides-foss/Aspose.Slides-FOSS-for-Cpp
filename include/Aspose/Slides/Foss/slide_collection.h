// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <Aspose/Slides/Foss/i_slide_collection.h>

namespace Aspose::Slides::Foss {

namespace Internal::opc { class OpcPackage; }
namespace Internal::pptx { class SlidePart; }

class ILayoutSlide;
class IMasterSlide;
class LayoutSlide;
class Presentation;
class Slide;

/// Represents a slide reference entry from presentation.xml (sldIdLst).
struct SlideReference {
    int64_t slide_id = 0;  ///< The slide ID value.
    std::string r_id;       ///< The relationship ID (e.g., "rId2").
};

/// Manages the collection of slides in a presentation.
class SlideCollection final : public ISlideCollection {
public:
    /// Constructs a slide collection for the given presentation.
    explicit SlideCollection(Presentation* presentation);
    SlideCollection(const SlideCollection&) = delete;
    SlideCollection& operator=(const SlideCollection&) = delete;
    ~SlideCollection() override;
    SlideCollection(SlideCollection&&) noexcept;
    SlideCollection& operator=(SlideCollection&&) noexcept;

    // -- ISlideCollection --

    /// Returns this collection as a generic collection interface.
    [[nodiscard]] ISlideCollection& as_i_collection() override;

    /// Returns this collection as a generic enumerable interface.
    [[nodiscard]] ISlideCollection& as_i_enumerable() override;

    /// Returns the number of slides.
    [[nodiscard]] std::size_t size() const noexcept override;

    /// Returns the slide at the given index.
    [[nodiscard]] Slide& operator[](std::size_t index) override;
    [[nodiscard]] const Slide& operator[](std::size_t index) const override;

    /// Adds a clone of the given slide to the end of the collection.
    Slide& add_clone(const Slide& source_slide) override;

    /// Adds a clone of the given slide to the specified layout.
    Slide& add_clone(const Slide& source_slide, ILayoutSlide* dest_layout) override;

    /// Adds a clone of the given slide to the specified master slide.
    Slide& add_clone(const Slide& source_slide, IMasterSlide* dest_master,
                     bool allow_clone_missing_layout) override;

    /// Inserts a clone of the given slide at the specified index.
    Slide& insert_clone(std::size_t index, const Slide& source_slide) override;

    /// Inserts a clone at the specified index with the given layout.
    Slide& insert_clone(std::size_t index, const Slide& source_slide,
                        ILayoutSlide* dest_layout) override;

    /// Inserts a clone at the specified index with the given master slide.
    Slide& insert_clone(std::size_t index, const Slide& source_slide,
                        IMasterSlide* dest_master,
                        bool allow_clone_missing_layout) override;

    /// Returns all slides as a vector of non-owning pointers.
    [[nodiscard]] std::vector<Slide*> to_array() override;

    /// Returns slides in the specified range as non-owning pointers.
    [[nodiscard]] std::vector<Slide*> to_array(std::size_t start_index,
                                               std::size_t count) override;

    /// Adds an empty slide with the given layout to the end.
    Slide& add_empty_slide(ILayoutSlide* layout) override;

    /// Inserts an empty slide with the given layout at the specified index.
    Slide& insert_empty_slide(std::size_t index, ILayoutSlide* layout) override;

    /// Removes the given slide from the collection.
    void remove(const Slide& slide) override;

    /// Removes the slide at the given index.
    void remove_at(std::size_t index) override;

    /// Returns the zero-based index of a slide, or -1 if not found.
    [[nodiscard]] std::ptrdiff_t index_of(const Slide& slide) const override;

    // Iterator support for range-based for loops.
    using iterator = std::vector<std::unique_ptr<Slide>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Slide>>::const_iterator;
    iterator begin() noexcept { return slides_.begin(); }
    iterator end() noexcept { return slides_.end(); }
    const_iterator begin() const noexcept { return slides_.begin(); }
    const_iterator end() const noexcept { return slides_.end(); }

    // -- Internal OPC-level methods --

    /// Layout resolver callback: maps a layout part name to a LayoutSlide pointer.
    using LayoutResolver = std::function<LayoutSlide*(std::string_view)>;

    /// Internal initialization for OPC-based loading.
    /// Replaces the default slide list with slides resolved from the package.
    /// @param presentation The parent Presentation object.
    /// @param package The OPC package (must outlive this collection).
    /// @param presentation_part_name The part name of presentation.xml.
    /// @param slide_references Slide ID references from presentation.xml.
    /// @param layout_resolver Callable mapping layout part name to LayoutSlide*.
    void init_internal(Presentation* presentation,
                       Internal::opc::OpcPackage* package,
                       std::string_view presentation_part_name,
                       std::vector<SlideReference> slide_references = {},
                       LayoutResolver layout_resolver = nullptr);

    /// Internal implementation for adding/inserting an empty slide at OPC level.
    /// @param layout The layout slide to use for the new slide.
    /// @param index Position to insert at. -1 means append at end.
    /// @return Reference to the newly created slide.
    Slide& add_empty_slide_internal(ILayoutSlide* layout, std::ptrdiff_t index = -1);

    /// Internal implementation for cloning a slide at OPC level.
    /// @param source_slide The slide to clone.
    /// @param index Position to insert at. -1 means append at end.
    /// @param dest_layout Optional destination layout slide.
    /// @param dest_master Optional destination master slide.
    /// @param allow_clone_missing_layout If true and layout not found, use first available.
    /// @return Reference to the cloned slide.
    Slide& clone_slide_internal(const Slide& source_slide,
                                std::ptrdiff_t index = -1,
                                ILayoutSlide* dest_layout = nullptr,
                                IMasterSlide* dest_master = nullptr,
                                bool allow_clone_missing_layout = false);

    /// Find the next available slide file number in the package.
    [[nodiscard]] int get_next_slide_file_number() const;

    /// Find a matching layout in the destination master for the source slide.
    [[nodiscard]] std::optional<std::string> find_matching_layout(
        const Slide& source_slide, IMasterSlide* dest_master, bool allow_clone) const;

    /// Find a layout in the destination presentation matching the source layout type.
    [[nodiscard]] std::optional<std::string> find_layout_by_type(
        ILayoutSlide* source_layout) const;

    /// Find matching layout by name using layout_slides.
    [[nodiscard]] std::optional<std::string> find_layout_from_layout_slides(
        ILayoutSlide* source_layout) const;

    /// Get the first available layout part name in the destination presentation.
    [[nodiscard]] std::optional<std::string> get_first_layout_part_name() const;

    /// Clone the master slide chain for a slide being cloned from another presentation.
    [[nodiscard]] std::optional<std::string> clone_master_chain_for_slide(
        const Slide& source_slide, ILayoutSlide* source_layout);

private:
    Slide& clone_slide_into(const Slide& source, std::size_t position,
                            ILayoutSlide* layout);

    /// Add a slide reference (<p:sldId>) to presentation.xml.
    SlideReference add_slide_reference_to_presentation(
        std::string_view rel_id, std::ptrdiff_t index = -1);

    Presentation* presentation_;
    std::vector<std::unique_ptr<Slide>> slides_;

    // OPC-level state
    Internal::opc::OpcPackage* package_ = nullptr;
    std::string presentation_part_name_;
    std::vector<SlideReference> slide_references_;
    LayoutResolver layout_resolver_;

    // Mapping from slide pointer to its OPC part name.
    std::unordered_map<const Slide*, std::string> slide_part_names_;

    // Owned SlidePart objects for slides loaded from OPC packages.
    std::vector<std::unique_ptr<Internal::pptx::SlidePart>> owned_slide_parts_;
};

} // namespace Aspose::Slides::Foss
