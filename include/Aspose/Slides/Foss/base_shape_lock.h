// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

/// Base class for shape locks that determine which operations are disabled on a shape.
class BaseShapeLock {
public:
    virtual ~BaseShapeLock() = default;

protected:
    BaseShapeLock() = default;
};

} // namespace Aspose::Slides::Foss
