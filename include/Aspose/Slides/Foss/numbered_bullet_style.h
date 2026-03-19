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

} // namespace Aspose::Slides::Foss
