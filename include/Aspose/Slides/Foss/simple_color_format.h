// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>
#include <utility>

#include <Aspose/Slides/Foss/color_format.h>

namespace Aspose::Slides::Foss {

/// A simple concrete implementation of ColorFormat backed by an sRGB color.
class SimpleColorFormat final : public ColorFormat {
public:
    SimpleColorFormat() = default;

    // A colour handed out by reference is mutated in place by the caller, so
    // the owner needs a way to hear about it (see set_on_changed). A *copy* is
    // a different object and is not bound to the original's owner, so the
    // callback is deliberately not carried across copies or moves.
    SimpleColorFormat(const SimpleColorFormat& other)
        : color_type_(other.color_type_),
          color_(other.color_),
          preset_color_(other.preset_color_),
          scheme_color_(other.scheme_color_) {}

    SimpleColorFormat& operator=(const SimpleColorFormat& other) {
        if (this != &other) {
            color_type_ = other.color_type_;
            color_ = other.color_;
            preset_color_ = other.preset_color_;
            scheme_color_ = other.scheme_color_;
            notify();
        }
        return *this;
    }

    SimpleColorFormat(SimpleColorFormat&& other) noexcept
        : color_type_(other.color_type_),
          color_(other.color_),
          preset_color_(other.preset_color_),
          scheme_color_(other.scheme_color_) {}

    SimpleColorFormat& operator=(SimpleColorFormat&& other) noexcept {
        if (this != &other) {
            color_type_ = other.color_type_;
            color_ = other.color_;
            preset_color_ = other.preset_color_;
            scheme_color_ = other.scheme_color_;
            notify();
        }
        return *this;
    }

    /// Install a callback invoked whenever this colour changes.
    ///
    /// Owners that back this colour with XML use it to keep the element in
    /// step: the colour is reached through a reference (`shadow_color()`,
    /// `solid_fill_color()`, …) and mutated without the owner being called at
    /// all, so without this there is no moment at which the owner could write
    /// the new value out.
    void set_on_changed(std::function<void()> callback) {
        on_changed_ = std::move(callback);
    }

    [[nodiscard]] ColorType color_type() const override { return color_type_; }
    void set_color_type(ColorType value) override {
        color_type_ = value;
        notify();
    }

    [[nodiscard]] Drawing::Color color() const override { return color_; }
    void set_color(const Drawing::Color& value) override {
        color_ = value;
        color_type_ = ColorType::RGB;
        notify();
    }

    [[nodiscard]] PresetColor preset_color() const override { return preset_color_; }
    void set_preset_color(PresetColor value) override {
        preset_color_ = value;
        notify();
    }

    [[nodiscard]] SchemeColor scheme_color() const override { return scheme_color_; }
    void set_scheme_color(SchemeColor value) override {
        scheme_color_ = value;
        notify();
    }

private:
    void notify() const {
        if (on_changed_) on_changed_();
    }

    ColorType color_type_ = ColorType::NOT_DEFINED;
    Drawing::Color color_;
    PresetColor preset_color_ = PresetColor::NOT_DEFINED;
    SchemeColor scheme_color_ = SchemeColor::NOT_DEFINED;
    std::function<void()> on_changed_;
};

} // namespace Aspose::Slides::Foss
