// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/table_format.h>

namespace Aspose::Slides::Foss {

void TableFormat::init_internal(pugi::xml_node tbl_pr_element,
                                std::function<void()> save_callback) {
    fill_format_.init_internal(tbl_pr_element, std::move(save_callback));
}

} // namespace Aspose::Slides::Foss
