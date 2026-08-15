// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file test_png.h
/// @brief A real 1x1 PNG, built in code so image tests need no fixture file.

#include <cstdint>
#include <vector>

namespace conformance {

/// A valid single-pixel PNG of the given colour.
///
/// Real PNG bytes rather than a placeholder: a writer is entitled to sniff the
/// signature to decide the media extension, and a test that feeds it garbage
/// would exercise a path no user takes.
[[nodiscard]] std::vector<std::uint8_t> one_pixel_png(std::uint8_t r,
                                                      std::uint8_t g,
                                                      std::uint8_t b);

} // namespace conformance
