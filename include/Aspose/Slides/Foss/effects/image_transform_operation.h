// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/effects/i_image_transform_operation.h>
#include <Aspose/Slides/Foss/pvi_object.h>

namespace Aspose::Slides::Foss::Effects {

/// Base class for image transform operations that participate in
/// property value inheritance via PVIObject.
class ImageTransformOperation : public PVIObject, public IImageTransformOperation {
public:
    ~ImageTransformOperation() override = default;

protected:
    ImageTransformOperation() = default;
};

} // namespace Aspose::Slides::Foss::Effects
