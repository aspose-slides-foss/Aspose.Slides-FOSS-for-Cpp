// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include "Aspose/Slides/Foss/drawing/point_f.h"

#include <sstream>

namespace Aspose::Slides::Foss::Drawing {

std::string to_string(const PointF& p) {
    std::ostringstream os;
    os << p;
    return os.str();
}

} // namespace Aspose::Slides::Foss::Drawing
