// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <Aspose/Slides/Foss/i_master_slide_collection.h>

namespace Aspose::Slides::Foss {

namespace Internal::opc { class OpcPackage; }

class GlobalLayoutSlideCollection;
class MasterSlide;
class Presentation;

/// Represents a master reference entry from presentation.xml (sldMasterIdLst).
struct MasterReference {
    int64_t master_id = 0;   ///< The master slide ID value.
    std::string r_id;         ///< The relationship ID (e.g., "rId2").
};

/// Manages the collection of master slides in a presentation.
class MasterSlideCollection final : public IMasterSlideCollection {
public:
    /// Constructs the collection with a back-reference to the owning presentation.
    explicit MasterSlideCollection(Presentation* presentation = nullptr);
    MasterSlideCollection(const MasterSlideCollection&) = delete;
    MasterSlideCollection& operator=(const MasterSlideCollection&) = delete;
    ~MasterSlideCollection() override;
    MasterSlideCollection(MasterSlideCollection&&) noexcept;
    MasterSlideCollection& operator=(MasterSlideCollection&&) noexcept;

    // -- IMasterSlideCollection --

    /// Returns this collection as a generic collection interface.
    [[nodiscard]] IMasterSlideCollection& as_i_collection() override;

    /// Returns this collection as a generic enumerable interface.
    [[nodiscard]] IMasterSlideCollection& as_i_enumerable() override;

    /// Returns the number of master slides.
    [[nodiscard]] std::size_t size() const noexcept override;

    /// Returns the master slide at the given index.
    [[nodiscard]] MasterSlide& operator[](std::size_t index) override;
    [[nodiscard]] const MasterSlide& operator[](std::size_t index) const override;

    /// Adds a clone of the given source master slide to the collection.
    /// Clones shapes and layout slides from the source.
    MasterSlide& add_clone(const IMasterSlide& source_master) override;

    // Range-based for loop support.
    using iterator = std::vector<std::unique_ptr<MasterSlide>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<MasterSlide>>::const_iterator;
    [[nodiscard]] iterator begin() noexcept { return masters_.begin(); }
    [[nodiscard]] iterator end() noexcept { return masters_.end(); }
    [[nodiscard]] const_iterator begin() const noexcept { return masters_.begin(); }
    [[nodiscard]] const_iterator end() const noexcept { return masters_.end(); }

    // -- Internal OPC-level methods --

    /// Internal initialization for OPC-based loading.
    /// @param presentation The parent Presentation object.
    /// @param package The OPC package (must outlive this collection).
    /// @param presentation_part_name The part name of presentation.xml.
    /// @param master_references Master ID references from presentation.xml.
    /// @param master_slides Pre-loaded master slide objects.
    void init_internal(Presentation* presentation,
                       Internal::opc::OpcPackage* package,
                       std::string_view presentation_part_name,
                       std::vector<MasterReference> master_references = {},
                       std::vector<std::unique_ptr<MasterSlide>> master_slides = {});

    /// Find the next available master slide file number in the package.
    [[nodiscard]] int get_next_master_file_number() const;

    /// Find the next available layout slide file number in the package.
    [[nodiscard]] int get_next_layout_file_number() const;

    /// Clone a master slide part and its related resources (except layouts).
    /// @return Mapping of old relationship IDs to new ones (non-layout rels only).
    [[nodiscard]] std::unordered_map<std::string, std::string> clone_master_part(
        Internal::opc::OpcPackage& source_package,
        std::string_view source_part_name,
        Internal::opc::OpcPackage& dest_package,
        std::string_view dest_part_name);

    /// Clone a layout slide part and point it to the specified master.
    void clone_layout_part(Internal::opc::OpcPackage& source_package,
                           std::string_view source_part_name,
                           Internal::opc::OpcPackage& dest_package,
                           std::string_view dest_part_name,
                           std::string_view dest_master_part_name);

    /// Find the maximum ID across all master slide IDs and layout IDs.
    /// In PPTX, sldMasterIdLst and sldLayoutIdLst share the same ID space.
    /// @return The maximum ID found, or 2147483647 if none exist.
    [[nodiscard]] int64_t get_max_master_layout_id_in_presentation() const;

    /// Update master's relationships and XML to point to cloned layouts.
    void update_master_layout_relationships(
        Internal::opc::OpcPackage& source_package,
        std::string_view source_master_part_name,
        std::string_view dest_master_part_name,
        const std::unordered_map<std::string, std::string>& layout_mapping,
        const std::unordered_map<std::string, std::string>& source_layout_rids);

private:
    Presentation* presentation_ = nullptr;
    Internal::opc::OpcPackage* package_ = nullptr;
    std::string presentation_part_name_;
    std::vector<MasterReference> master_references_;
    std::vector<std::unique_ptr<MasterSlide>> masters_;
};

} // namespace Aspose::Slides::Foss
