// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the type of the extended bullets.
enum class BulletType {
    NOT_DEFINED,
    NONE,
    SYMBOL,
    NUMBERED,
    PICTURE,
};

/// Returns the string representation of a BulletType value.
constexpr std::string_view to_string_view(BulletType value) {
    switch (value) {
        case BulletType::NOT_DEFINED: return "NotDefined";
        case BulletType::NONE: return "None";
        case BulletType::SYMBOL: return "Symbol";
        case BulletType::NUMBERED: return "Numbered";
        case BulletType::PICTURE: return "Picture";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
