// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include "Aspose/Slides/Foss/drawing/size.h"

#include <sstream>

namespace Aspose::Slides::Foss::Drawing {

std::string to_string(const Size& s) {
    std::ostringstream os;
    os << s;
    return os.str();
}

} // namespace Aspose::Slides::Foss::Drawing
