// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_layout_slide_collection.h>

namespace Aspose::Slides::Foss {

/// Interface for a collection of layout slides owned by a master slide.
///
/// Extends ILayoutSlideCollection without adding new members;
/// serves as a marker type for master-slide-specific layout collections.
class IMasterLayoutSlideCollection : public virtual ILayoutSlideCollection {
public:
    ~IMasterLayoutSlideCollection() override = default;

protected:
    IMasterLayoutSlideCollection() = default;
};

} // namespace Aspose::Slides::Foss
