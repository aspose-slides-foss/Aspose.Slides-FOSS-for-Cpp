// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_base_portion_format.h>
#include <Aspose/Slides/Foss/i_hyperlink_container.h>

namespace Aspose::Slides::Foss {

/// Interface for text portion formatting properties with no inheritance applied.
///
/// Combines the base portion formatting accessors from IBasePortionFormat
/// with hyperlink support from IHyperlinkContainer.
class IPortionFormat : public virtual IBasePortionFormat,
                       public virtual IHyperlinkContainer {
public:
    ~IPortionFormat() override = default;

protected:
    IPortionFormat() = default;
};

} // namespace Aspose::Slides::Foss
