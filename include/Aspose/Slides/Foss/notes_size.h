// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/drawing/size_f.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Specifies the size of the notes slide.
class NotesSize final {
public:
    NotesSize() = default;
    ~NotesSize() = default;
    NotesSize(NotesSize&&) noexcept = default;
    NotesSize& operator=(NotesSize&&) noexcept = default;

    /// Internal initialization — binds the notes size to the presentation XML.
    /// @param presentation_element The <p:presentation> XML element containing <p:notesSz>.
    /// @param save_callback Callback to persist changes.
    void init_internal(pugi::xml_node presentation_element,
                       std::function<void()> save_callback);

    /// Returns the width of the notes slide in points.
    [[nodiscard]] double width() const;
    /// Sets the width of the notes slide in points.
    void set_width(double value);

    /// Returns the height of the notes slide in points.
    [[nodiscard]] double height() const;
    /// Sets the height of the notes slide in points.
    void set_height(double value);

    /// Returns the size of the notes slide in points. Read/write.
    [[nodiscard]] Drawing::SizeF size() const;
    /// Sets the size of the notes slide in points.
    void set_size(Drawing::SizeF value);

    /// Save changes via the save callback.
    void save();

private:
    /// 1 point = 12700 EMUs.
    static constexpr double kEmuPerPoint = 12700.0;

    /// Default notes slide dimensions in points.
    static constexpr double kDefaultWidth = 720.0;
    static constexpr double kDefaultHeight = 540.0;

    double width_ = kDefaultWidth;
    double height_ = kDefaultHeight;

    pugi::xml_node presentation_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
