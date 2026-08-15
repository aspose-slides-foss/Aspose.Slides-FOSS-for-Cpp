// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <pugixml.hpp>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Set an attribute on @p node, adding it when the element does not carry it.
///
/// `pugi::xml_node::attribute()` returns a null attribute for a name the
/// element does not have, and `xml_attribute::set_value()` on a null attribute
/// is a silent no-op. Writing `node.attribute("x").set_value(v)` therefore
/// persists nothing whenever the element was freshly created without `x`,
/// which is exactly the state a newly enabled effect or newly created element
/// is in. Always go through this helper instead.
template <typename T>
void set_attribute(pugi::xml_node node, const char* name, T value) {
    if (auto attr = node.attribute(name)) {
        attr.set_value(value);
    } else {
        node.append_attribute(name).set_value(value);
    }
}

} // namespace Aspose::Slides::Foss::Internal::pptx
