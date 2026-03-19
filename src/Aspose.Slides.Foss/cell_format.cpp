// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/cell_format.h>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::Elements;

void CellFormat::init_internal(pugi::xml_node tc_pr_element,
                               std::function<void()> save_callback) {
    // Initialize the fill format from the tcPr element.
    fill_format_.init_internal(tc_pr_element, save_callback);

    // Initialize each border line format with the appropriate OOXML tag.
    border_left_.init_internal(tc_pr_element, save_callback, "a:lnL");
    border_top_.init_internal(tc_pr_element, save_callback, "a:lnT");
    border_right_.init_internal(tc_pr_element, save_callback, "a:lnR");
    border_bottom_.init_internal(tc_pr_element, save_callback, "a:lnB");
    border_diag_down_.init_internal(tc_pr_element, save_callback, "a:lnTlToBr");
    border_diag_up_.init_internal(tc_pr_element, save_callback, "a:lnBlToTr");
}

} // namespace Aspose::Slides::Foss
