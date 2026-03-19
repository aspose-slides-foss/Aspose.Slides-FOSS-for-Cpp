// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/notes_size.h>

#include <cmath>
#include <string>
#include <string_view>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// XML tag constant
// ---------------------------------------------------------------------------

static constexpr std::string_view kNotesSz = "p:notesSz";

// ---------------------------------------------------------------------------
// NotesSize – XML-backed internal methods
// ---------------------------------------------------------------------------

void NotesSize::init_internal(pugi::xml_node presentation_element,
                              std::function<void()> save_callback) {
    presentation_element_ = presentation_element;
    save_callback_ = std::move(save_callback);

    // Read initial values from XML if present.
    auto notes_sz = presentation_element_.child(std::string(kNotesSz).c_str());
    if (notes_sz) {
        auto cx = notes_sz.attribute("cx");
        auto cy = notes_sz.attribute("cy");
        if (cx) width_ = cx.as_llong() / kEmuPerPoint;
        if (cy) height_ = cy.as_llong() / kEmuPerPoint;
    }
}

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

double NotesSize::width() const {
    return width_;
}

void NotesSize::set_width(double value) {
    width_ = value;
    if (presentation_element_) {
        auto notes_sz = presentation_element_.child(std::string(kNotesSz).c_str());
        if (!notes_sz)
            notes_sz = presentation_element_.append_child(std::string(kNotesSz).c_str());

        auto attr = notes_sz.attribute("cx");
        auto emu = static_cast<long long>(std::round(value * kEmuPerPoint));
        if (attr) attr.set_value(emu);
        else notes_sz.append_attribute("cx").set_value(emu);
        save();
    }
}

void NotesSize::set_height(double value) {
    height_ = value;
    if (presentation_element_) {
        auto notes_sz = presentation_element_.child(std::string(kNotesSz).c_str());
        if (!notes_sz)
            notes_sz = presentation_element_.append_child(std::string(kNotesSz).c_str());

        auto attr = notes_sz.attribute("cy");
        auto emu = static_cast<long long>(std::round(value * kEmuPerPoint));
        if (attr) attr.set_value(emu);
        else notes_sz.append_attribute("cy").set_value(emu);
        save();
    }
}

double NotesSize::height() const {
    return height_;
}

Drawing::SizeF NotesSize::size() const {
    return {static_cast<float>(width_), static_cast<float>(height_)};
}

void NotesSize::set_size(Drawing::SizeF value) {
    width_ = value.width;
    height_ = value.height;
    if (presentation_element_) {
        auto notes_sz = presentation_element_.child(std::string(kNotesSz).c_str());
        if (!notes_sz)
            notes_sz = presentation_element_.append_child(std::string(kNotesSz).c_str());

        auto set_or_add = [](pugi::xml_node node, const char* name, long long val) {
            auto attr = node.attribute(name);
            if (attr) {
                attr.set_value(val);
            } else {
                node.append_attribute(name).set_value(val);
            }
        };

        set_or_add(notes_sz, "cx",
                   static_cast<long long>(std::round(width_ * kEmuPerPoint)));
        set_or_add(notes_sz, "cy",
                   static_cast<long long>(std::round(height_ * kEmuPerPoint)));
        save();
    }
}

void NotesSize::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss
