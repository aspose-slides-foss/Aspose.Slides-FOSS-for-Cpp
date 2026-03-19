// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cmath>
#include <functional>
#include <string>

#include <Aspose/Slides/Foss/bullet_type.h>
#include <Aspose/Slides/Foss/i_bullet_format.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/numbered_bullet_style.h>
#include <Aspose/Slides/Foss/picture.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents paragraph bullet formatting properties.
class BulletFormat final : public IBulletFormat {
public:
    BulletFormat() = default;
    ~BulletFormat() override = default;

    /// Returns the bullet type.
    [[nodiscard]] BulletType type() const noexcept override { return type_; }
    void set_type(BulletType value) noexcept override { type_ = value; }

    /// Returns the bullet character.
    /// @note Alias: get_char() / set_char().
    [[nodiscard]] const std::string& character() const noexcept { return char_; }
    void set_character(std::string value) { char_ = std::move(value); }

    [[nodiscard]] const std::string& get_char() const noexcept override { return char_; }
    void set_char(std::string value) override { char_ = std::move(value); }

    /// Returns the bullet font name.
    [[nodiscard]] const std::string& font_name() const noexcept override { return font_name_; }
    void set_font_name(std::string value) override { font_name_ = std::move(value); }

    /// Returns the bullet height as a percentage. NaN means inherited.
    [[nodiscard]] float height() const noexcept override { return height_; }
    void set_height(float value) noexcept override { height_ = value; }

    /// Returns the bullet color format.
    [[nodiscard]] SimpleColorFormat& color() noexcept override { return color_; }
    [[nodiscard]] const SimpleColorFormat& color() const noexcept override { return color_; }

    /// Returns the numbered bullet start value.
    [[nodiscard]] int numbered_bullet_start_with() const noexcept override { return numbered_start_; }
    void set_numbered_bullet_start_with(int value) noexcept override { numbered_start_ = value; }

    /// Returns the numbered bullet style.
    [[nodiscard]] NumberedBulletStyle numbered_bullet_style() const noexcept override { return numbered_style_; }
    void set_numbered_bullet_style(NumberedBulletStyle value) noexcept override { numbered_style_ = value; }

    /// Returns whether the bullet has a hard-coded color.
    [[nodiscard]] NullableBool is_bullet_hard_color() const noexcept override { return hard_color_; }
    void set_is_bullet_hard_color(NullableBool value) noexcept override { hard_color_ = value; }

    /// Returns whether the bullet has a hard-coded font.
    [[nodiscard]] NullableBool is_bullet_hard_font() const noexcept override { return hard_font_; }
    void set_is_bullet_hard_font(NullableBool value) noexcept override { hard_font_ = value; }

    /// Returns the picture used as a bullet in a paragraph with no inheritance.
    [[nodiscard]] Picture& picture() noexcept override { return picture_; }
    [[nodiscard]] const Picture& picture() const noexcept override { return picture_; }

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an existing `<a:pPr>` XML node.
    /// @param ppr_element The `<a:pPr>` pugixml node.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node ppr_element,
                       std::function<void()> save_callback);

    /// Persist changes via the save callback.
    void save();

    /// Remove all bullet type child elements (buNone, buAutoNum, buChar, buBlip) from pPr.
    void remove_bullet_type_elements();

private:
    BulletType type_ = BulletType::NOT_DEFINED;
    std::string char_;
    std::string font_name_;
    float height_ = std::numeric_limits<float>::quiet_NaN();
    SimpleColorFormat color_;
    int numbered_start_ = 1;
    NumberedBulletStyle numbered_style_ = NumberedBulletStyle::NOT_DEFINED;
    NullableBool hard_color_ = NullableBool::NOT_DEFINED;
    NullableBool hard_font_ = NullableBool::NOT_DEFINED;
    Picture picture_{nullptr};

    pugi::xml_node ppr_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
