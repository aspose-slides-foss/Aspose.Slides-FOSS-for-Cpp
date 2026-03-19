// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace Aspose::Slides::Foss::Internal::xml {

/// Lightweight in-memory XML element for OOXML manipulation.
///
/// Element names use Clark notation: `{namespace-uri}local-name`.
/// Attributes are stored as simple name-value pairs.
class XmlElement final : public std::enable_shared_from_this<XmlElement> {
public:
    using Ptr = std::shared_ptr<XmlElement>;

    /// Construct an element with the given qualified name.
    explicit XmlElement(std::string name);

    /// @name Identity
    /// @{
    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    [[nodiscard]] std::string local_name() const;
    [[nodiscard]] std::string namespace_uri() const;
    /// @}

    /// @name Attributes
    /// @{
    [[nodiscard]] std::string get(std::string_view attr,
                                  std::string_view default_val = "") const;
    [[nodiscard]] std::optional<std::string> get_optional(
        std::string_view attr) const;
    void set(std::string_view attr, std::string_view value);
    void remove_attribute(std::string_view attr);
    [[nodiscard]] bool has_attribute(std::string_view attr) const;
    /// @}

    /// @name Text content
    /// @{
    [[nodiscard]] const std::string& text() const noexcept { return text_; }
    void set_text(std::string_view value) { text_ = std::string(value); }
    /// @}

    /// @name Children
    /// @{
    [[nodiscard]] const std::vector<Ptr>& children() const noexcept {
        return children_;
    }

    Ptr append_child(Ptr child);
    Ptr add_sub_element(std::string_view name);
    void insert_child(std::size_t index, Ptr child);
    void remove_child(const Ptr& child);
    void remove_child_at(std::size_t index);
    [[nodiscard]] Ptr find(std::string_view name) const;
    [[nodiscard]] std::vector<Ptr> find_all(std::string_view name) const;
    [[nodiscard]] std::optional<std::size_t> index_of(const Ptr& child) const;
    [[nodiscard]] std::size_t child_count() const noexcept {
        return children_.size();
    }
    /// @}

    /// @name Namespace map (for serialization)
    /// @{
    void set_namespace(std::string_view prefix, std::string_view uri);
    [[nodiscard]] const std::vector<std::pair<std::string, std::string>>&
    namespace_map() const noexcept {
        return nsmap_;
    }
    /// @}

    /// @name Serialization
    /// @{
    static Ptr parse(std::string_view xml);
    [[nodiscard]] std::string serialize(bool xml_declaration = true,
                                        bool pretty_print = true) const;
    /// @}

    /// Unescape XML entities (&amp;, &lt;, &gt;, &apos;, &quot;).
    static std::string unescape_xml(std::string_view input);

private:
    std::string name_;
    std::string text_;
    std::vector<std::pair<std::string, std::string>> attributes_;
    std::vector<Ptr> children_;
    std::vector<std::pair<std::string, std::string>> nsmap_;

    void serialize_impl(std::string& out, int indent, bool pretty) const;
    static std::string escape_xml(std::string_view input);
};

} // namespace Aspose::Slides::Foss::Internal::xml
