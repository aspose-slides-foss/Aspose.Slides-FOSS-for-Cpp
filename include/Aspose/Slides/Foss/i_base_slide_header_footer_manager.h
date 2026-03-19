// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_base_header_footer_manager.h>

namespace Aspose::Slides::Foss {

/// Interface for slide-level header/footer management, adding slide number support.
class IBaseSlideHeaderFooterManager : public IBaseHeaderFooterManager {
public:
    /// Gets whether the slide number placeholder is present.
    [[nodiscard]] virtual bool is_slide_number_visible() const = 0;

    /// Sets slide number placeholder visibility.
    virtual void set_slide_number_visibility(bool is_visible) = 0;
};

} // namespace Aspose::Slides::Foss
