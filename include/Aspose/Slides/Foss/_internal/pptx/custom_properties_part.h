// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file custom_properties_part.h
/// @brief Parse and serialize docProps/custom.xml (Office custom properties).
///
/// Each custom property is stored as:
/// @code
/// <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="N" name="...">
///     <vt:type>value</vt:type>
/// </property>
/// @endcode
///
/// Type mapping: string -> lpwstr, int -> i4, double -> r8, bool -> bool,
/// TimePoint -> filetime. PIDs start at 2. The file is created on demand
/// only when custom properties are added.

#include <chrono>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Part name inside the OPC package.
inline constexpr std::string_view kCustomPropertiesPartName =
    "docProps/custom.xml";

/// A point in time (UTC) used for filetime property values.
using CustomTimePoint = std::chrono::system_clock::time_point;

/// Variant type for custom property values.
using CustomPropertyValue = std::variant<
    std::string,
    int32_t,
    double,
    bool,
    CustomTimePoint
>;

/// Parse and serialize docProps/custom.xml.
///
/// Manages a dictionary of named custom properties, each with a typed value
/// (string, int, double, bool, or datetime). Properties are lazily created:
/// the XML part is only written when save() is called and the part is dirty.
class CustomPropertiesPart final {
public:
    /// Construct from an OPC package, parsing docProps/custom.xml if present.
    /// @param package The OPC package to read from and write to.
    explicit CustomPropertiesPart(opc::OpcPackage& package);

    /// @return Number of custom properties.
    [[nodiscard]] int32_t count() const;

    /// Check if a property with the given name exists.
    /// @param name Property name.
    /// @return true if the property exists.
    [[nodiscard]] bool contains(std::string_view name) const;

    /// Get the name of a property by index.
    /// @param index Zero-based index.
    /// @return Property name.
    /// @throws std::out_of_range if index is out of bounds.
    [[nodiscard]] std::string get_name(int32_t index) const;

    /// Get the value of a property by name.
    /// @param name Property name.
    /// @return Property value, or nullopt if not found.
    [[nodiscard]] std::optional<CustomPropertyValue> get_value(
        std::string_view name) const;

    /// Set a property value. Creates the property if it does not exist.
    /// @param name Property name.
    /// @param value Typed property value.
    void set_value(std::string_view name, CustomPropertyValue value);

    /// Remove a property by name.
    /// @param name Property name.
    /// @return true if the property existed and was removed.
    bool remove(std::string_view name);

    /// Remove all custom properties and mark dirty.
    void clear();

    /// Serialize properties back to the package.
    /// Only writes if the part is dirty. Removes the part if no properties
    /// remain. Ensures the content type and root relationship are registered.
    void save();

private:
    void parse();
    [[nodiscard]] std::optional<CustomPropertyValue> read_value(
        const pugi::xml_node& prop_el) const;
    void write_value(pugi::xml_node prop_el,
                     const CustomPropertyValue& value) const;
    [[nodiscard]] static std::optional<CustomTimePoint> parse_filetime(
        std::string_view text);
    void ensure_content_type();
    void ensure_relationship();

    opc::OpcPackage& package_;

    /// Ordered storage: vector of (name, value) pairs preserves insertion order.
    std::vector<std::pair<std::string, CustomPropertyValue>> properties_;
    bool dirty_ = false;
};

} // namespace Aspose::Slides::Foss::Internal::pptx
