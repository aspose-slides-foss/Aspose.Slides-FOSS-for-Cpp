// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/effects/image_transform_operation.h>
#include <Aspose/Slides/Foss/effects/i_image_transform_operation.h>
#include <Aspose/Slides/Foss/i_slide_component.h>
#include <Aspose/Slides/Foss/i_presentation_component.h>
#include <Aspose/Slides/Foss/pvi_object.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Effects;

namespace {

/// Concrete subclass to test the abstract ImageTransformOperation base.
class TestableImageTransformOperation : public ImageTransformOperation {
public:
    TestableImageTransformOperation() = default;
};

} // namespace

// ---------------------------------------------------------------------------
// ImageTransformOperation: inherits IImageTransformOperation
// ---------------------------------------------------------------------------
TEST(ImageTransformOperationTest, IsIImageTransformOperation) {
    TestableImageTransformOperation op;
    IImageTransformOperation* iop = &op;
    EXPECT_EQ(iop, static_cast<IImageTransformOperation*>(&op));
}

// ---------------------------------------------------------------------------
// ImageTransformOperation: inherits ISlideComponent via PVIObject
// ---------------------------------------------------------------------------
TEST(ImageTransformOperationTest, IsISlideComponent) {
    TestableImageTransformOperation op;
    ISlideComponent* isc = &op;
    EXPECT_EQ(isc, static_cast<ISlideComponent*>(&op));
}

// ---------------------------------------------------------------------------
// ImageTransformOperation: inherits IPresentationComponent via PVIObject
// ---------------------------------------------------------------------------
TEST(ImageTransformOperationTest, IsIPresentationComponent) {
    TestableImageTransformOperation op;
    IPresentationComponent* ipc = &op;
    EXPECT_NE(ipc, nullptr);
}

// ---------------------------------------------------------------------------
// ImageTransformOperation: default slide() returns nullptr
// ---------------------------------------------------------------------------
TEST(ImageTransformOperationTest, DefaultSlideIsNull) {
    TestableImageTransformOperation op;
    EXPECT_EQ(op.slide(), nullptr);
}

// ---------------------------------------------------------------------------
// ImageTransformOperation: default presentation() returns nullptr
// ---------------------------------------------------------------------------
TEST(ImageTransformOperationTest, DefaultPresentationIsNull) {
    TestableImageTransformOperation op;
    EXPECT_EQ(op.presentation(), nullptr);
}
