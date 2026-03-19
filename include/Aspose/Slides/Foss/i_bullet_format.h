// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

#include <Aspose/Slides/Foss/bullet_type.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/numbered_bullet_style.h>

namespace Aspose::Slides::Foss {

class IColorFormat;
class IFontData;
class ISlidesPicture;

/// Interface for paragraph bullet formatting properties.
class IBulletFormat {
public:
    virtual ~IBulletFormat() = default;

    /// Returns the bullet type of a paragraph with no inheritance.
    [[nodiscard]] virtual BulletType type() const = 0;
    /// Sets the bullet type of a paragraph with no inheritance.
    virtual void set_type(BulletType value) = 0;

    /// Returns the bullet character of a paragraph with no inheritance.
    [[nodiscard]] virtual const std::string& get_char() const = 0;
    /// Sets the bullet character of a paragraph with no inheritance.
    virtual void set_char(std::string value) = 0;

    /// Returns the bullet font name of a paragraph with no inheritance.
    [[nodiscard]] virtual const std::string& font_name() const = 0;
    /// Sets the bullet font name of a paragraph with no inheritance.
    virtual void set_font_name(std::string value) = 0;

    /// Returns the bullet height of a paragraph with no inheritance.
    /// Value NaN means the bullet inherits height from the first portion.
    [[nodiscard]] virtual float height() const = 0;
    /// Sets the bullet height of a paragraph with no inheritance.
    virtual void set_height(float value) = 0;

    /// Returns the color format of a bullet of a paragraph with no inheritance. Read-only.
    [[nodiscard]] virtual IColorFormat& color() = 0;
    /// Returns the color format of a bullet of a paragraph with no inheritance. Read-only.
    [[nodiscard]] virtual const IColorFormat& color() const = 0;

    /// Returns the picture used as a bullet in a paragraph with no inheritance. Read-only.
    [[nodiscard]] virtual ISlidesPicture& picture() = 0;
    /// Returns the picture used as a bullet in a paragraph with no inheritance. Read-only.
    [[nodiscard]] virtual const ISlidesPicture& picture() const = 0;

    /// Returns the first number used for a group of numbered bullets with no inheritance.
    [[nodiscard]] virtual int numbered_bullet_start_with() const = 0;
    /// Sets the first number used for a group of numbered bullets with no inheritance.
    virtual void set_numbered_bullet_start_with(int value) = 0;

    /// Returns the style of a numbered bullet with no inheritance.
    [[nodiscard]] virtual NumberedBulletStyle numbered_bullet_style() const = 0;
    /// Sets the style of a numbered bullet with no inheritance.
    virtual void set_numbered_bullet_style(NumberedBulletStyle value) = 0;

    /// Determines whether the bullet has own color or inherits it from the first portion.
    [[nodiscard]] virtual NullableBool is_bullet_hard_color() const = 0;
    /// Sets whether the bullet has own color or inherits it from the first portion.
    virtual void set_is_bullet_hard_color(NullableBool value) = 0;

    /// Determines whether the bullet has own font or inherits it from the first portion.
    [[nodiscard]] virtual NullableBool is_bullet_hard_font() const = 0;
    /// Sets whether the bullet has own font or inherits it from the first portion.
    virtual void set_is_bullet_hard_font(NullableBool value) = 0;
};

} // namespace Aspose::Slides::Foss
