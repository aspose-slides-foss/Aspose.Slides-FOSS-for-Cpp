// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <ostream>
#include <string>

namespace Aspose::Slides::Foss::Drawing {

/// Represents an ARGB color, equivalent to System.Drawing.Color.
class Color {
public:
    /// Constructs a color with the given ARGB components (each 0-255).
    constexpr Color(uint8_t a = 255, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) noexcept
        : a_(a), r_(r), g_(g), b_(b) {}

    /// Creates a Color from ARGB components.
    static constexpr Color from_argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b) noexcept {
        return Color(a, r, g, b);
    }

    /// Returns the alpha component.
    [[nodiscard]] constexpr uint8_t a() const noexcept { return a_; }
    /// Returns the red component.
    [[nodiscard]] constexpr uint8_t r() const noexcept { return r_; }
    /// Returns the green component.
    [[nodiscard]] constexpr uint8_t g() const noexcept { return g_; }
    /// Returns the blue component.
    [[nodiscard]] constexpr uint8_t b() const noexcept { return b_; }

    constexpr bool operator==(const Color&) const noexcept = default;
    constexpr bool operator!=(const Color&) const noexcept = default;

    /// Returns a human-readable string representation.
    [[nodiscard]] std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const Color& c);

    // ---- Named color constants ----
    static const Color alice_blue;
    static const Color antique_white;
    static const Color aqua;
    static const Color aquamarine;
    static const Color azure;
    static const Color beige;
    static const Color bisque;
    static const Color black;
    static const Color blanched_almond;
    static const Color blue;
    static const Color blue_violet;
    static const Color brown;
    static const Color burly_wood;
    static const Color cadet_blue;
    static const Color chartreuse;
    static const Color chocolate;
    static const Color coral;
    static const Color cornflower_blue;
    static const Color cornsilk;
    static const Color crimson;
    static const Color cyan;
    static const Color dark_blue;
    static const Color dark_cyan;
    static const Color dark_goldenrod;
    static const Color dark_gray;
    static const Color dark_green;
    static const Color dark_khaki;
    static const Color dark_magenta;
    static const Color dark_olive_green;
    static const Color dark_orange;
    static const Color dark_orchid;
    static const Color dark_red;
    static const Color dark_salmon;
    static const Color dark_sea_green;
    static const Color dark_slate_blue;
    static const Color dark_slate_gray;
    static const Color dark_turquoise;
    static const Color dark_violet;
    static const Color deep_pink;
    static const Color deep_sky_blue;
    static const Color dim_gray;
    static const Color dodger_blue;
    static const Color firebrick;
    static const Color floral_white;
    static const Color forest_green;
    static const Color fuchsia;
    static const Color gainsboro;
    static const Color ghost_white;
    static const Color gold;
    static const Color goldenrod;
    static const Color gray;
    static const Color green;
    static const Color green_yellow;
    static const Color honeydew;
    static const Color hot_pink;
    static const Color indian_red;
    static const Color indigo;
    static const Color ivory;
    static const Color khaki;
    static const Color lavender;
    static const Color lavender_blush;
    static const Color lawn_green;
    static const Color lemon_chiffon;
    static const Color light_blue;
    static const Color light_coral;
    static const Color light_cyan;
    static const Color light_goldenrod_yellow;
    static const Color light_gray;
    static const Color light_green;
    static const Color light_pink;
    static const Color light_salmon;
    static const Color light_sea_green;
    static const Color light_sky_blue;
    static const Color light_slate_gray;
    static const Color light_steel_blue;
    static const Color light_yellow;
    static const Color lime;
    static const Color lime_green;
    static const Color linen;
    static const Color magenta;
    static const Color maroon;
    static const Color medium_aquamarine;
    static const Color medium_blue;
    static const Color medium_orchid;
    static const Color medium_purple;
    static const Color medium_sea_green;
    static const Color medium_slate_blue;
    static const Color medium_spring_green;
    static const Color medium_turquoise;
    static const Color medium_violet_red;
    static const Color midnight_blue;
    static const Color mint_cream;
    static const Color misty_rose;
    static const Color moccasin;
    static const Color navajo_white;
    static const Color navy;
    static const Color old_lace;
    static const Color olive;
    static const Color olive_drab;
    static const Color orange;
    static const Color orange_red;
    static const Color orchid;
    static const Color pale_goldenrod;
    static const Color pale_green;
    static const Color pale_turquoise;
    static const Color pale_violet_red;
    static const Color papaya_whip;
    static const Color peach_puff;
    static const Color peru;
    static const Color pink;
    static const Color plum;
    static const Color powder_blue;
    static const Color purple;
    static const Color red;
    static const Color rosy_brown;
    static const Color royal_blue;
    static const Color saddle_brown;
    static const Color salmon;
    static const Color sandy_brown;
    static const Color sea_green;
    static const Color sea_shell;
    static const Color sienna;
    static const Color silver;
    static const Color sky_blue;
    static const Color slate_blue;
    static const Color slate_gray;
    static const Color snow;
    static const Color spring_green;
    static const Color steel_blue;
    static const Color tan;
    static const Color teal;
    static const Color thistle;
    static const Color tomato;
    static const Color transparent;
    static const Color turquoise;
    static const Color violet;
    static const Color wheat;
    static const Color white;
    static const Color white_smoke;
    static const Color yellow;
    static const Color yellow_green;

private:
    uint8_t a_;
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
};

} // namespace Aspose::Slides::Foss::Drawing
