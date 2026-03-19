// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file opc_package.h
/// @brief OPC (Open Packaging Conventions) package with ZIP I/O support.

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace Aspose::Slides::Foss::Internal::opc {

/// Abstract interface for an OPC package that stores named parts as byte arrays.
///
/// Concrete implementations may back this with a ZIP file, in-memory map, etc.
class OpcPackage {
public:
    virtual ~OpcPackage() = default;

    /// Retrieve a part's content by name. Returns nullopt if the part does not exist.
    [[nodiscard]] virtual std::optional<std::vector<uint8_t>> get_part(
        std::string_view part_name) const = 0;

    /// Store (or overwrite) a part with the given content.
    virtual void set_part(std::string_view part_name,
                          std::vector<uint8_t> content) = 0;

    /// Check whether a part exists in the package.
    [[nodiscard]] virtual bool has_part(std::string_view part_name) const = 0;

    /// Delete a part from the package.
    /// @return true if the part existed and was deleted, false otherwise.
    virtual bool delete_part(std::string_view part_name) = 0;
};

/// In-memory OPC package with ZIP file I/O support.
///
/// Manages an Open Packaging Conventions package as an in-memory map of
/// part names to byte arrays. Supports loading from and saving to ZIP archives
/// (file paths or streams), preserving unknown parts for round-trip fidelity.
class InMemoryOpcPackage final : public OpcPackage {
public:
    InMemoryOpcPackage() = default;

    /// Open an OPC package from a file path.
    /// @param path Path to a ZIP archive.
    /// @return Loaded package.
    /// @throws std::runtime_error if the file does not exist or is not a valid ZIP.
    [[nodiscard]] static InMemoryOpcPackage open(const std::filesystem::path& path);

    /// Open an OPC package from a binary input stream.
    /// @param stream Input stream positioned at the start of a ZIP archive.
    /// @return Loaded package.
    /// @throws std::runtime_error if the stream does not contain a valid ZIP.
    [[nodiscard]] static InMemoryOpcPackage open(std::istream& stream);

    /// Create a new empty OPC package.
    [[nodiscard]] static InMemoryOpcPackage create_new();

    /// Save the package to a file path as a ZIP archive.
    void save(const std::filesystem::path& path) const;

    /// Save the package to a binary output stream as a ZIP archive.
    void save(std::ostream& stream) const;

    [[nodiscard]] std::optional<std::vector<uint8_t>> get_part(
        std::string_view part_name) const override {
        auto it = parts_.find(std::string(part_name));
        if (it != parts_.end()) return it->second;
        return std::nullopt;
    }

    void set_part(std::string_view part_name,
                  std::vector<uint8_t> content) override {
        parts_[std::string(part_name)] = std::move(content);
    }

    /// Set or update a part with string content (encoded as UTF-8).
    void set_part(std::string_view part_name, std::string_view content);

    [[nodiscard]] bool has_part(std::string_view part_name) const override {
        return parts_.contains(std::string(part_name));
    }

    bool delete_part(std::string_view part_name) override {
        return parts_.erase(std::string(part_name)) > 0;
    }

    /// Get a list of all part names in the package.
    [[nodiscard]] std::vector<std::string> get_part_names() const;

    /// Get the original file path if the package was loaded from a file.
    /// @return File path, or nullopt if loaded from stream or created new.
    [[nodiscard]] std::optional<std::string> source_path() const;

    /// Close the package and release resources.
    /// Clears all in-memory part data. The package should not be used after closing.
    void close();

private:
    std::unordered_map<std::string, std::vector<uint8_t>> parts_;
    std::optional<std::string> source_path_;
};

} // namespace Aspose::Slides::Foss::Internal::opc
