// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/drawing/color.h>

#include <iomanip>
#include <sstream>

namespace Aspose::Slides::Foss::Drawing {

std::string Color::to_string() const {
    std::ostringstream os;
    if (a_ == 255) {
        os << "Color(r=" << static_cast<int>(r_)
           << ", g=" << static_cast<int>(g_)
           << ", b=" << static_cast<int>(b_) << ")";
    } else {
        os << "Color(a=" << static_cast<int>(a_)
           << ", r=" << static_cast<int>(r_)
           << ", g=" << static_cast<int>(g_)
           << ", b=" << static_cast<int>(b_) << ")";
    }
    return os.str();
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
    return os << c.to_string();
}

// Named color constants (matching System.Drawing.Color / CSS named colors)
const Color Color::alice_blue{255, 240, 248, 255};
const Color Color::antique_white{255, 250, 235, 215};
const Color Color::aqua{255, 0, 255, 255};
const Color Color::aquamarine{255, 127, 255, 212};
const Color Color::azure{255, 240, 255, 255};
const Color Color::beige{255, 245, 245, 220};
const Color Color::bisque{255, 255, 228, 196};
const Color Color::black{255, 0, 0, 0};
const Color Color::blanched_almond{255, 255, 235, 205};
const Color Color::blue{255, 0, 0, 255};
const Color Color::blue_violet{255, 138, 43, 226};
const Color Color::brown{255, 165, 42, 42};
const Color Color::burly_wood{255, 222, 184, 135};
const Color Color::cadet_blue{255, 95, 158, 160};
const Color Color::chartreuse{255, 127, 255, 0};
const Color Color::chocolate{255, 210, 105, 30};
const Color Color::coral{255, 255, 127, 80};
const Color Color::cornflower_blue{255, 100, 149, 237};
const Color Color::cornsilk{255, 255, 248, 220};
const Color Color::crimson{255, 220, 20, 60};
const Color Color::cyan{255, 0, 255, 255};
const Color Color::dark_blue{255, 0, 0, 139};
const Color Color::dark_cyan{255, 0, 139, 139};
const Color Color::dark_goldenrod{255, 184, 134, 11};
const Color Color::dark_gray{255, 169, 169, 169};
const Color Color::dark_green{255, 0, 100, 0};
const Color Color::dark_khaki{255, 189, 183, 107};
const Color Color::dark_magenta{255, 139, 0, 139};
const Color Color::dark_olive_green{255, 85, 107, 47};
const Color Color::dark_orange{255, 255, 140, 0};
const Color Color::dark_orchid{255, 153, 50, 204};
const Color Color::dark_red{255, 139, 0, 0};
const Color Color::dark_salmon{255, 233, 150, 122};
const Color Color::dark_sea_green{255, 143, 188, 143};
const Color Color::dark_slate_blue{255, 72, 61, 139};
const Color Color::dark_slate_gray{255, 47, 79, 79};
const Color Color::dark_turquoise{255, 0, 206, 209};
const Color Color::dark_violet{255, 148, 0, 211};
const Color Color::deep_pink{255, 255, 20, 147};
const Color Color::deep_sky_blue{255, 0, 191, 255};
const Color Color::dim_gray{255, 105, 105, 105};
const Color Color::dodger_blue{255, 30, 144, 255};
const Color Color::firebrick{255, 178, 34, 34};
const Color Color::floral_white{255, 255, 250, 240};
const Color Color::forest_green{255, 34, 139, 34};
const Color Color::fuchsia{255, 255, 0, 255};
const Color Color::gainsboro{255, 220, 220, 220};
const Color Color::ghost_white{255, 248, 248, 255};
const Color Color::gold{255, 255, 215, 0};
const Color Color::goldenrod{255, 218, 165, 32};
const Color Color::gray{255, 128, 128, 128};
const Color Color::green{255, 0, 128, 0};
const Color Color::green_yellow{255, 173, 255, 47};
const Color Color::honeydew{255, 240, 255, 240};
const Color Color::hot_pink{255, 255, 105, 180};
const Color Color::indian_red{255, 205, 92, 92};
const Color Color::indigo{255, 75, 0, 130};
const Color Color::ivory{255, 255, 255, 240};
const Color Color::khaki{255, 240, 230, 140};
const Color Color::lavender{255, 230, 230, 250};
const Color Color::lavender_blush{255, 255, 240, 245};
const Color Color::lawn_green{255, 124, 252, 0};
const Color Color::lemon_chiffon{255, 255, 250, 205};
const Color Color::light_blue{255, 173, 216, 230};
const Color Color::light_coral{255, 240, 128, 128};
const Color Color::light_cyan{255, 224, 255, 255};
const Color Color::light_goldenrod_yellow{255, 250, 250, 210};
const Color Color::light_gray{255, 211, 211, 211};
const Color Color::light_green{255, 144, 238, 144};
const Color Color::light_pink{255, 255, 182, 193};
const Color Color::light_salmon{255, 255, 160, 122};
const Color Color::light_sea_green{255, 32, 178, 170};
const Color Color::light_sky_blue{255, 135, 206, 250};
const Color Color::light_slate_gray{255, 119, 136, 153};
const Color Color::light_steel_blue{255, 176, 196, 222};
const Color Color::light_yellow{255, 255, 255, 224};
const Color Color::lime{255, 0, 255, 0};
const Color Color::lime_green{255, 50, 205, 50};
const Color Color::linen{255, 250, 240, 230};
const Color Color::magenta{255, 255, 0, 255};
const Color Color::maroon{255, 128, 0, 0};
const Color Color::medium_aquamarine{255, 102, 205, 170};
const Color Color::medium_blue{255, 0, 0, 205};
const Color Color::medium_orchid{255, 186, 85, 211};
const Color Color::medium_purple{255, 147, 112, 219};
const Color Color::medium_sea_green{255, 60, 179, 113};
const Color Color::medium_slate_blue{255, 123, 104, 238};
const Color Color::medium_spring_green{255, 0, 250, 154};
const Color Color::medium_turquoise{255, 72, 209, 204};
const Color Color::medium_violet_red{255, 199, 21, 133};
const Color Color::midnight_blue{255, 25, 25, 112};
const Color Color::mint_cream{255, 245, 255, 250};
const Color Color::misty_rose{255, 255, 228, 225};
const Color Color::moccasin{255, 255, 228, 181};
const Color Color::navajo_white{255, 255, 222, 173};
const Color Color::navy{255, 0, 0, 128};
const Color Color::old_lace{255, 253, 245, 230};
const Color Color::olive{255, 128, 128, 0};
const Color Color::olive_drab{255, 107, 142, 35};
const Color Color::orange{255, 255, 165, 0};
const Color Color::orange_red{255, 255, 69, 0};
const Color Color::orchid{255, 218, 112, 214};
const Color Color::pale_goldenrod{255, 238, 232, 170};
const Color Color::pale_green{255, 152, 251, 152};
const Color Color::pale_turquoise{255, 175, 238, 238};
const Color Color::pale_violet_red{255, 219, 112, 147};
const Color Color::papaya_whip{255, 255, 239, 213};
const Color Color::peach_puff{255, 255, 218, 185};
const Color Color::peru{255, 205, 133, 63};
const Color Color::pink{255, 255, 192, 203};
const Color Color::plum{255, 221, 160, 221};
const Color Color::powder_blue{255, 176, 224, 230};
const Color Color::purple{255, 128, 0, 128};
const Color Color::red{255, 255, 0, 0};
const Color Color::rosy_brown{255, 188, 143, 143};
const Color Color::royal_blue{255, 65, 105, 225};
const Color Color::saddle_brown{255, 139, 69, 19};
const Color Color::salmon{255, 250, 128, 114};
const Color Color::sandy_brown{255, 244, 164, 96};
const Color Color::sea_green{255, 46, 139, 87};
const Color Color::sea_shell{255, 255, 245, 238};
const Color Color::sienna{255, 160, 82, 45};
const Color Color::silver{255, 192, 192, 192};
const Color Color::sky_blue{255, 135, 206, 235};
const Color Color::slate_blue{255, 106, 90, 205};
const Color Color::slate_gray{255, 112, 128, 144};
const Color Color::snow{255, 255, 250, 250};
const Color Color::spring_green{255, 0, 255, 127};
const Color Color::steel_blue{255, 70, 130, 180};
const Color Color::tan{255, 210, 180, 140};
const Color Color::teal{255, 0, 128, 128};
const Color Color::thistle{255, 216, 191, 216};
const Color Color::tomato{255, 255, 99, 71};
const Color Color::transparent{0, 255, 255, 255};
const Color Color::turquoise{255, 64, 224, 208};
const Color Color::violet{255, 238, 130, 238};
const Color Color::wheat{255, 245, 222, 179};
const Color Color::white{255, 255, 255, 255};
const Color Color::white_smoke{255, 245, 245, 245};
const Color Color::yellow{255, 255, 255, 0};
const Color Color::yellow_green{255, 154, 205, 50};

} // namespace Aspose::Slides::Foss::Drawing
