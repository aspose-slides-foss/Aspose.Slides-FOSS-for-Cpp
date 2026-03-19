// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

namespace Aspose::Slides::Foss {

/// Internal representation of a notes slide's placeholder storage.
/// Tracks which placeholders are present and their text content.
class NotesSlidePart final {
public:
    NotesSlidePart() = default;

    /// Checks whether a placeholder of the given type exists.
    [[nodiscard]] bool has_placeholder(std::string_view type) const {
        return placeholders_.contains(std::string(type));
    }

    /// Adds a placeholder of the given type (no-op if already present).
    void add_placeholder(std::string_view type) {
        placeholders_.try_emplace(std::string(type));
    }

    /// Removes a placeholder of the given type (no-op if not present).
    void remove_placeholder(std::string_view type) {
        placeholders_.erase(std::string(type));
    }

    /// Sets the text content of a placeholder, creating it if needed.
    void set_placeholder_text(std::string_view type, std::string_view text) {
        placeholders_[std::string(type)] = std::string(text);
    }

    /// Gets the text content of a placeholder, or empty string if not present.
    [[nodiscard]] std::string get_placeholder_text(std::string_view type) const {
        auto it = placeholders_.find(std::string(type));
        return it != placeholders_.end() ? it->second : std::string{};
    }

private:
    std::unordered_map<std::string, std::string> placeholders_;
};

} // namespace Aspose::Slides::Foss
