// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cmath>
#include <string>

#include <pugixml.hpp>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

/// Represents a geometry shape's adjustment value.
/// These values affect the shape's form.
class AdjustValue final {
public:
    AdjustValue() = default;
    AdjustValue(std::string name, int raw_value)
        : name_(std::move(name)), raw_value_(raw_value) {}

    /// Initialize this adjustment value from an XML `<a:gd>` element.
    /// @param gd_element The XML node representing the guide definition.
    /// @param slide_part The SlidePart that owns the XML. May be nullptr.
    void init_internal(pugi::xml_node gd_element,
                       Internal::pptx::SlidePart* slide_part);

    /// Returns the name of this adjustment value. Read-only.
    [[nodiscard]] const std::string& name() const noexcept { return name_; }

    /// Returns the raw adjustment value.
    [[nodiscard]] int raw_value() const noexcept { return raw_value_; }

    /// Sets the raw adjustment value.
    void set_raw_value(int value) noexcept;

    /// Returns the value interpreted as an angle in degrees.
    [[nodiscard]] double angle_value() const noexcept {
        return raw_value_ / 60000.0;
    }

    /// Sets the value interpreted as an angle in degrees.
    void set_angle_value(double value) noexcept {
        set_raw_value(static_cast<int>(std::round(value * 60000.0)));
    }

    /// Returns the backing XML element, if any.
    [[nodiscard]] pugi::xml_node gd_element() const { return gd_element_; }

private:
    std::string name_;
    int raw_value_ = 0;
    pugi::xml_node gd_element_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
};

} // namespace Aspose::Slides::Foss
