// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_heading_pair.h>

#include <ostream>
#include <string>

namespace Aspose::Slides::Foss {

/// Represents a 'Heading pair' property of the document.
/// It indicates the group name of document parts and the number of parts in group.
class HeadingPair final : public IHeadingPair {
public:
    HeadingPair() = default;
    HeadingPair(std::string name, int count) : name_(std::move(name)), count_(count) {}

    /// Returns the group name of document parts. Read-only.
    [[nodiscard]] const std::string& name() const override { return name_; }

    /// Returns the number of parts in group. Read-only.
    [[nodiscard]] int count() const override { return count_; }

    bool operator==(const HeadingPair& other) const {
        return name_ == other.name_ && count_ == other.count_;
    }
    bool operator!=(const HeadingPair& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& os, const HeadingPair& hp) {
        return os << "HeadingPair(name=" << hp.name_ << ", count=" << hp.count_ << ")";
    }

private:
    std::string name_;
    int count_ = 0;
};

} // namespace Aspose::Slides::Foss
