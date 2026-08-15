// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the style of the numbered bullets.
enum class NumberedBulletStyle {
    NOT_DEFINED,
    BULLET_ALPHA_LC_PERIOD,
    BULLET_ALPHA_UC_PERIOD,
    BULLET_ARABIC_PAREN_RIGHT,
    BULLET_ARABIC_PERIOD,
    BULLET_ROMAN_LC_PAREN_BOTH,
    BULLET_ROMAN_LC_PAREN_RIGHT,
    BULLET_ROMAN_LC_PERIOD,
    BULLET_ROMAN_UC_PERIOD,
    BULLET_ALPHA_LC_PAREN_BOTH,
    BULLET_ALPHA_LC_PAREN_RIGHT,
    BULLET_ALPHA_UC_PAREN_BOTH,
    BULLET_ALPHA_UC_PAREN_RIGHT,
    BULLET_ARABIC_PAREN_BOTH,
    BULLET_ARABIC_PLAIN,
    BULLET_ROMAN_UC_PAREN_BOTH,
    BULLET_ROMAN_UC_PAREN_RIGHT,
    BULLET_SIMP_CHIN_PLAIN,
    BULLET_SIMP_CHIN_PERIOD,
    BULLET_CIRCLE_NUM_DB_PLAIN,
    BULLET_CIRCLE_NUM_WD_WHITE_PLAIN,
    BULLET_CIRCLE_NUM_WD_BLACK_PLAIN,
    BULLET_TRAD_CHIN_PLAIN,
    BULLET_TRAD_CHIN_PERIOD,
    BULLET_ARABIC_ALPHA_DASH,
    BULLET_ARABIC_ABJAD_DASH,
    BULLET_HEBREW_ALPHA_DASH,
    BULLET_KANJI_KOREAN_PLAIN,
    BULLET_KANJI_KOREAN_PERIOD,
    BULLET_ARABIC_DB_PLAIN,
    BULLET_ARABIC_DB_PERIOD,
    BULLET_THAI_ALPHA_PERIOD,
    BULLET_THAI_ALPHA_PAREN_RIGHT,
    BULLET_THAI_ALPHA_PAREN_BOTH,
    BULLET_THAI_NUM_PERIOD,
    BULLET_THAI_NUM_PAREN_RIGHT,
    BULLET_THAI_NUM_PAREN_BOTH,
    BULLET_HINDI_ALPHA_PERIOD,
    BULLET_HINDI_NUM_PERIOD,
    BULLET_KANJI_SIMP_CHIN_DB_PERIOD,
    BULLET_HINDI_NUM_PAREN_RIGHT,
    BULLET_HINDI_ALPHA1_PERIOD,
};

/// Returns the string representation of a NumberedBulletStyle value.
constexpr std::string_view to_string_view(NumberedBulletStyle value) {
    switch (value) {
        case NumberedBulletStyle::NOT_DEFINED: return "NotDefined";
        case NumberedBulletStyle::BULLET_ALPHA_LC_PERIOD: return "BulletAlphaLCPeriod";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PERIOD: return "BulletAlphaUCPeriod";
        case NumberedBulletStyle::BULLET_ARABIC_PAREN_RIGHT: return "BulletArabicParenRight";
        case NumberedBulletStyle::BULLET_ARABIC_PERIOD: return "BulletArabicPeriod";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PAREN_BOTH: return "BulletRomanLCParenBoth";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PAREN_RIGHT: return "BulletRomanLCParenRight";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PERIOD: return "BulletRomanLCPeriod";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PERIOD: return "BulletRomanUCPeriod";
        case NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_BOTH: return "BulletAlphaLCParenBoth";
        case NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_RIGHT: return "BulletAlphaLCParenRight";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PAREN_BOTH: return "BulletAlphaUCParenBoth";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PAREN_RIGHT: return "BulletAlphaUCParenRight";
        case NumberedBulletStyle::BULLET_ARABIC_PAREN_BOTH: return "BulletArabicParenBoth";
        case NumberedBulletStyle::BULLET_ARABIC_PLAIN: return "BulletArabicPlain";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PAREN_BOTH: return "BulletRomanUCParenBoth";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PAREN_RIGHT: return "BulletRomanUCParenRight";
        case NumberedBulletStyle::BULLET_SIMP_CHIN_PLAIN: return "BulletSimpChinPlain";
        case NumberedBulletStyle::BULLET_SIMP_CHIN_PERIOD: return "BulletSimpChinPeriod";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_DB_PLAIN: return "BulletCircleNumDBPlain";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_WD_WHITE_PLAIN: return "BulletCircleNumWDWhitePlain";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_WD_BLACK_PLAIN: return "BulletCircleNumWDBlackPlain";
        case NumberedBulletStyle::BULLET_TRAD_CHIN_PLAIN: return "BulletTradChinPlain";
        case NumberedBulletStyle::BULLET_TRAD_CHIN_PERIOD: return "BulletTradChinPeriod";
        case NumberedBulletStyle::BULLET_ARABIC_ALPHA_DASH: return "BulletArabicAlphaDash";
        case NumberedBulletStyle::BULLET_ARABIC_ABJAD_DASH: return "BulletArabicAbjadDash";
        case NumberedBulletStyle::BULLET_HEBREW_ALPHA_DASH: return "BulletHebrewAlphaDash";
        case NumberedBulletStyle::BULLET_KANJI_KOREAN_PLAIN: return "BulletKanjiKoreanPlain";
        case NumberedBulletStyle::BULLET_KANJI_KOREAN_PERIOD: return "BulletKanjiKoreanPeriod";
        case NumberedBulletStyle::BULLET_ARABIC_DB_PLAIN: return "BulletArabicDBPlain";
        case NumberedBulletStyle::BULLET_ARABIC_DB_PERIOD: return "BulletArabicDBPeriod";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PERIOD: return "BulletThaiAlphaPeriod";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PAREN_RIGHT: return "BulletThaiAlphaParenRight";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PAREN_BOTH: return "BulletThaiAlphaParenBoth";
        case NumberedBulletStyle::BULLET_THAI_NUM_PERIOD: return "BulletThaiNumPeriod";
        case NumberedBulletStyle::BULLET_THAI_NUM_PAREN_RIGHT: return "BulletThaiNumParenRight";
        case NumberedBulletStyle::BULLET_THAI_NUM_PAREN_BOTH: return "BulletThaiNumParenBoth";
        case NumberedBulletStyle::BULLET_HINDI_ALPHA_PERIOD: return "BulletHindiAlphaPeriod";
        case NumberedBulletStyle::BULLET_HINDI_NUM_PERIOD: return "BulletHindiNumPeriod";
        case NumberedBulletStyle::BULLET_KANJI_SIMP_CHIN_DB_PERIOD: return "BulletKanjiSimpChinDBPeriod";
        case NumberedBulletStyle::BULLET_HINDI_NUM_PAREN_RIGHT: return "BulletHindiNumParenRight";
        case NumberedBulletStyle::BULLET_HINDI_ALPHA1_PERIOD: return "BulletHindiAlpha1Period";
    }
    return "Unknown";
}

/// The ST_TextAutonumberScheme token for a numbered bullet style, or
/// nullptr when there is none.
///
/// These are not the display names to_string_view() returns; an invented
/// token makes PowerPoint refuse the file.
constexpr const char* numbered_bullet_style_to_ooxml(NumberedBulletStyle value) {
    switch (value) {
        case NumberedBulletStyle::BULLET_ALPHA_LC_PERIOD:         return "alphaLcPeriod";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PERIOD:         return "alphaUcPeriod";
        case NumberedBulletStyle::BULLET_ARABIC_PAREN_RIGHT:      return "arabicParenR";
        case NumberedBulletStyle::BULLET_ARABIC_PERIOD:           return "arabicPeriod";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PAREN_BOTH:     return "romanLcParenBoth";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PAREN_RIGHT:    return "romanLcParenR";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PERIOD:         return "romanLcPeriod";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PERIOD:         return "romanUcPeriod";
        case NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_BOTH:     return "alphaLcParenBoth";
        case NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_RIGHT:    return "alphaLcParenR";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PAREN_BOTH:     return "alphaUcParenBoth";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PAREN_RIGHT:    return "alphaUcParenR";
        case NumberedBulletStyle::BULLET_ARABIC_PAREN_BOTH:       return "arabicParenBoth";
        case NumberedBulletStyle::BULLET_ARABIC_PLAIN:            return "arabicPlain";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PAREN_BOTH:     return "romanUcParenBoth";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PAREN_RIGHT:    return "romanUcParenR";
        case NumberedBulletStyle::BULLET_SIMP_CHIN_PLAIN:         return "ea1ChsPlain";
        case NumberedBulletStyle::BULLET_SIMP_CHIN_PERIOD:        return "ea1ChsPeriod";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_DB_PLAIN:     return "circleNumDbPlain";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_WD_WHITE_PLAIN: return "circleNumWdWhitePlain";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_WD_BLACK_PLAIN: return "circleNumWdBlackPlain";
        case NumberedBulletStyle::BULLET_TRAD_CHIN_PLAIN:         return "ea1ChtPlain";
        case NumberedBulletStyle::BULLET_TRAD_CHIN_PERIOD:        return "ea1ChtPeriod";
        // ST_TextAutonumberScheme spells the three dash schemes with a
        // "Minus" suffix, not with the language name they carry here.
        case NumberedBulletStyle::BULLET_ARABIC_ALPHA_DASH:       return "arabic1Minus";
        case NumberedBulletStyle::BULLET_ARABIC_ABJAD_DASH:       return "arabic2Minus";
        case NumberedBulletStyle::BULLET_HEBREW_ALPHA_DASH:       return "hebrew2Minus";
        case NumberedBulletStyle::BULLET_KANJI_KOREAN_PLAIN:      return "ea1JpnKorPlain";
        case NumberedBulletStyle::BULLET_KANJI_KOREAN_PERIOD:     return "ea1JpnKorPeriod";
        case NumberedBulletStyle::BULLET_ARABIC_DB_PLAIN:         return "arabicDbPlain";
        case NumberedBulletStyle::BULLET_ARABIC_DB_PERIOD:        return "arabicDbPeriod";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PERIOD:       return "thaiAlphaPeriod";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PAREN_RIGHT:  return "thaiAlphaParenR";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PAREN_BOTH:   return "thaiAlphaParenBoth";
        case NumberedBulletStyle::BULLET_THAI_NUM_PERIOD:         return "thaiNumPeriod";
        case NumberedBulletStyle::BULLET_THAI_NUM_PAREN_RIGHT:    return "thaiNumParenR";
        case NumberedBulletStyle::BULLET_THAI_NUM_PAREN_BOTH:     return "thaiNumParenBoth";
        case NumberedBulletStyle::BULLET_HINDI_ALPHA_PERIOD:      return "hindiAlphaPeriod";
        case NumberedBulletStyle::BULLET_HINDI_NUM_PERIOD:        return "hindiNumPeriod";
        case NumberedBulletStyle::BULLET_KANJI_SIMP_CHIN_DB_PERIOD: return "ea1JpnChsDbPeriod";
        case NumberedBulletStyle::BULLET_HINDI_NUM_PAREN_RIGHT:   return "hindiNumParenR";
        case NumberedBulletStyle::BULLET_HINDI_ALPHA1_PERIOD:     return "hindiAlpha1Period";
        case NumberedBulletStyle::NOT_DEFINED:                    return nullptr;
    }
    return nullptr;
}

/// The NumberedBulletStyle an ST_TextAutonumberScheme token names, or
/// NOT_DEFINED when the token is not one of them.
///
/// The inverse of numbered_bullet_style_to_ooxml: a bullet read out of a
/// file has to come back as the style it was written as, or re-saving the
/// paragraph silently renumbers it.
constexpr NumberedBulletStyle numbered_bullet_style_from_ooxml(
    std::string_view ooxml) {
    if (ooxml == "alphaLcPeriod")         return NumberedBulletStyle::BULLET_ALPHA_LC_PERIOD;
    if (ooxml == "alphaUcPeriod")         return NumberedBulletStyle::BULLET_ALPHA_UC_PERIOD;
    if (ooxml == "arabicParenR")          return NumberedBulletStyle::BULLET_ARABIC_PAREN_RIGHT;
    if (ooxml == "arabicPeriod")          return NumberedBulletStyle::BULLET_ARABIC_PERIOD;
    if (ooxml == "romanLcParenBoth")      return NumberedBulletStyle::BULLET_ROMAN_LC_PAREN_BOTH;
    if (ooxml == "romanLcParenR")         return NumberedBulletStyle::BULLET_ROMAN_LC_PAREN_RIGHT;
    if (ooxml == "romanLcPeriod")         return NumberedBulletStyle::BULLET_ROMAN_LC_PERIOD;
    if (ooxml == "romanUcPeriod")         return NumberedBulletStyle::BULLET_ROMAN_UC_PERIOD;
    if (ooxml == "alphaLcParenBoth")      return NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_BOTH;
    if (ooxml == "alphaLcParenR")         return NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_RIGHT;
    if (ooxml == "alphaUcParenBoth")      return NumberedBulletStyle::BULLET_ALPHA_UC_PAREN_BOTH;
    if (ooxml == "alphaUcParenR")         return NumberedBulletStyle::BULLET_ALPHA_UC_PAREN_RIGHT;
    if (ooxml == "arabicParenBoth")       return NumberedBulletStyle::BULLET_ARABIC_PAREN_BOTH;
    if (ooxml == "arabicPlain")           return NumberedBulletStyle::BULLET_ARABIC_PLAIN;
    if (ooxml == "romanUcParenBoth")      return NumberedBulletStyle::BULLET_ROMAN_UC_PAREN_BOTH;
    if (ooxml == "romanUcParenR")         return NumberedBulletStyle::BULLET_ROMAN_UC_PAREN_RIGHT;
    if (ooxml == "ea1ChsPlain")           return NumberedBulletStyle::BULLET_SIMP_CHIN_PLAIN;
    if (ooxml == "ea1ChsPeriod")          return NumberedBulletStyle::BULLET_SIMP_CHIN_PERIOD;
    if (ooxml == "circleNumDbPlain")      return NumberedBulletStyle::BULLET_CIRCLE_NUM_DB_PLAIN;
    if (ooxml == "circleNumWdWhitePlain") return NumberedBulletStyle::BULLET_CIRCLE_NUM_WD_WHITE_PLAIN;
    if (ooxml == "circleNumWdBlackPlain") return NumberedBulletStyle::BULLET_CIRCLE_NUM_WD_BLACK_PLAIN;
    if (ooxml == "ea1ChtPlain")           return NumberedBulletStyle::BULLET_TRAD_CHIN_PLAIN;
    if (ooxml == "ea1ChtPeriod")          return NumberedBulletStyle::BULLET_TRAD_CHIN_PERIOD;
    if (ooxml == "arabic1Minus")          return NumberedBulletStyle::BULLET_ARABIC_ALPHA_DASH;
    if (ooxml == "arabic2Minus")          return NumberedBulletStyle::BULLET_ARABIC_ABJAD_DASH;
    if (ooxml == "hebrew2Minus")          return NumberedBulletStyle::BULLET_HEBREW_ALPHA_DASH;
    if (ooxml == "ea1JpnKorPlain")        return NumberedBulletStyle::BULLET_KANJI_KOREAN_PLAIN;
    if (ooxml == "ea1JpnKorPeriod")       return NumberedBulletStyle::BULLET_KANJI_KOREAN_PERIOD;
    if (ooxml == "arabicDbPlain")         return NumberedBulletStyle::BULLET_ARABIC_DB_PLAIN;
    if (ooxml == "arabicDbPeriod")        return NumberedBulletStyle::BULLET_ARABIC_DB_PERIOD;
    if (ooxml == "thaiAlphaPeriod")       return NumberedBulletStyle::BULLET_THAI_ALPHA_PERIOD;
    if (ooxml == "thaiAlphaParenR")       return NumberedBulletStyle::BULLET_THAI_ALPHA_PAREN_RIGHT;
    if (ooxml == "thaiAlphaParenBoth")    return NumberedBulletStyle::BULLET_THAI_ALPHA_PAREN_BOTH;
    if (ooxml == "thaiNumPeriod")         return NumberedBulletStyle::BULLET_THAI_NUM_PERIOD;
    if (ooxml == "thaiNumParenR")         return NumberedBulletStyle::BULLET_THAI_NUM_PAREN_RIGHT;
    if (ooxml == "thaiNumParenBoth")      return NumberedBulletStyle::BULLET_THAI_NUM_PAREN_BOTH;
    if (ooxml == "hindiAlphaPeriod")      return NumberedBulletStyle::BULLET_HINDI_ALPHA_PERIOD;
    if (ooxml == "hindiNumPeriod")        return NumberedBulletStyle::BULLET_HINDI_NUM_PERIOD;
    if (ooxml == "ea1JpnChsDbPeriod")     return NumberedBulletStyle::BULLET_KANJI_SIMP_CHIN_DB_PERIOD;
    if (ooxml == "hindiNumParenR")        return NumberedBulletStyle::BULLET_HINDI_NUM_PAREN_RIGHT;
    if (ooxml == "hindiAlpha1Period")     return NumberedBulletStyle::BULLET_HINDI_ALPHA1_PERIOD;
    return NumberedBulletStyle::NOT_DEFINED;
}

} // namespace Aspose::Slides::Foss
