// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/text_frame.h>

#include <regex>
#include <sstream>
#include <string>

#include <Aspose/Slides/Foss/i_base_slide.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/paragraph_collection.h>
#include <Aspose/Slides/Foss/text_frame_format.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>

namespace Aspose::Slides::Foss {

struct TextFrame::Impl {
    ParagraphCollection paragraphs;
    TextFrameFormat format;
    IBaseSlide* slide = nullptr;
    IShape* parent_shape = nullptr;
    ICell* parent_cell = nullptr;
    pugi::xml_node txbody_element;
    Internal::pptx::SlidePart* slide_part = nullptr;
};

TextFrame::TextFrame() : impl_(std::make_unique<Impl>()) {}
TextFrame::~TextFrame() = default;
TextFrame::TextFrame(TextFrame&&) noexcept = default;
TextFrame& TextFrame::operator=(TextFrame&&) noexcept = default;

IParagraphCollection& TextFrame::paragraphs() {
    return impl_->paragraphs;
}

const IParagraphCollection& TextFrame::paragraphs() const {
    return impl_->paragraphs;
}

std::string TextFrame::text() const {
    const auto& paras = impl_->paragraphs;
    std::string result;
    for (std::size_t i = 0; i < paras.size(); ++i) {
        if (i > 0) result += '\n';
        result += paras[i].text();
    }
    return result;
}

void TextFrame::set_text(const std::string& value) {
    impl_->paragraphs.clear();

    // Split on \r\n, \r, or \n
    std::vector<std::string> lines;
    if (value.empty()) {
        lines.emplace_back("");
    } else {
        std::string::size_type start = 0;
        while (start <= value.size()) {
            auto pos = value.find_first_of("\r\n", start);
            if (pos == std::string::npos) {
                lines.push_back(value.substr(start));
                break;
            }
            lines.push_back(value.substr(start, pos - start));
            // Handle \r\n as a single line break
            if (pos + 1 < value.size() && value[pos] == '\r' && value[pos + 1] == '\n') {
                start = pos + 2;
            } else {
                start = pos + 1;
            }
        }
    }

    // Update XML if XML-backed.
    if (impl_->txbody_element) {
        // Remove existing <a:p> elements.
        auto node = impl_->txbody_element;
        std::vector<pugi::xml_node> to_remove;
        for (auto child = node.first_child(); child; child = child.next_sibling()) {
            std::string_view name = child.name();
            if (name == "a:p" || name == Internal::pptx::Elements::kAP) {
                to_remove.push_back(child);
            }
        }
        for (auto& n : to_remove) {
            node.remove_child(n);
        }

        // Create new <a:p> elements with <a:r><a:t>text</a:t></a:r>.
        for (auto& line : lines) {
            auto a_p = node.append_child("a:p");
            if (!line.empty()) {
                auto a_r = a_p.append_child("a:r");
                auto a_t = a_r.append_child("a:t");
                a_t.text().set(line.c_str());
            }
            a_p.append_child("a:endParaRPr");
        }

        if (impl_->slide_part) {
            impl_->slide_part->save();
        }

        // Re-initialize paragraphs from updated XML.
        impl_->paragraphs.init_internal(
            impl_->txbody_element, impl_->slide_part, impl_->slide);
        return;
    }

    for (auto& line : lines) {
        impl_->paragraphs.add(Paragraph(std::move(line)));
    }
}

ITextFrameFormat& TextFrame::text_frame_format() {
    return impl_->format;
}

const ITextFrameFormat& TextFrame::text_frame_format() const {
    return impl_->format;
}

IShape* TextFrame::parent_shape() {
    return impl_->parent_shape;
}

const IShape* TextFrame::parent_shape() const {
    return impl_->parent_shape;
}

ICell* TextFrame::parent_cell() {
    return impl_->parent_cell;
}

const ICell* TextFrame::parent_cell() const {
    return impl_->parent_cell;
}

ISlideComponent* TextFrame::as_i_slide_component() {
    return static_cast<ISlideComponent*>(this);
}

const ISlideComponent* TextFrame::as_i_slide_component() const {
    return static_cast<const ISlideComponent*>(this);
}

IBaseSlide* TextFrame::slide() {
    return impl_->slide;
}

const IBaseSlide* TextFrame::slide() const {
    return impl_->slide;
}

IPresentationComponent* TextFrame::as_i_presentation_component() {
    return static_cast<IPresentationComponent*>(this);
}

const IPresentationComponent* TextFrame::as_i_presentation_component() const {
    return static_cast<const IPresentationComponent*>(this);
}

IPresentation* TextFrame::presentation() {
    return nullptr;
}

const IPresentation* TextFrame::presentation() const {
    return nullptr;
}

void TextFrame::set_slide(IBaseSlide* slide) {
    impl_->slide = slide;
}

void TextFrame::set_parent_shape(IShape* shape) {
    impl_->parent_shape = shape;
}

void TextFrame::set_parent_cell(ICell* cell) {
    impl_->parent_cell = cell;
}

void TextFrame::init_internal(pugi::xml_node txbody_element,
                              Internal::pptx::SlidePart* slide_part,
                              IBaseSlide* parent_slide,
                              IShape* parent_shape) {
    impl_->txbody_element = txbody_element;
    impl_->slide_part = slide_part;
    impl_->slide = parent_slide;
    impl_->parent_shape = parent_shape;
    impl_->paragraphs.init_internal(txbody_element, slide_part, parent_slide);
    // Without this the frame's own formatting has no XML behind it, so on a
    // deck opened from a file every anchoring, margin and wrap setting was
    // accepted, read back, and never written.
    impl_->format.init_internal(txbody_element, [slide_part]() {
        if (slide_part) slide_part->save();
    });
}

} // namespace Aspose::Slides::Foss
