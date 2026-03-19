// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/base_portion_format.h>
#include <Aspose/Slides/Foss/i_portion_format.h>

#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents text portion formatting properties with write access.
/// When XML-backed (after init_from_rpr), property changes are persisted
/// to the <a:rPr> element automatically.
class PortionFormat final : public BasePortionFormat, public IPortionFormat {
public:
    PortionFormat() = default;
    ~PortionFormat() override = default;

    /// Initialize from an existing <a:rPr> XML node (or null node).
    /// @param r_element The parent <a:r> element.
    /// @param save_callback Called after XML changes to persist the slide part.
    void init_from_rpr(pugi::xml_node r_element,
                       std::function<void()> save_callback);

protected:
    void on_property_changed() override;

private:
    /// Ensure <a:rPr> child exists under r_element_ and return it.
    pugi::xml_node ensure_rpr();

    /// Write all current format properties to the rPr XML node.
    void flush_to_xml();

    /// Read all format properties from the rPr XML node.
    void read_from_xml();

    pugi::xml_node r_element_;
    std::function<void()> save_callback_;
    bool suppress_change_ = false;
};

} // namespace Aspose::Slides::Foss
