// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/cell_collection.h>

#include <Aspose/Slides/Foss/i_base_slide.h>

namespace Aspose::Slides::Foss {

IPresentation* CellCollection::presentation() {
    if (parent_slide_ != nullptr) {
        return parent_slide_->presentation();
    }
    return nullptr;
}

const IPresentation* CellCollection::presentation() const {
    if (parent_slide_ != nullptr) {
        return parent_slide_->presentation();
    }
    return nullptr;
}

} // namespace Aspose::Slides::Foss
