// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <any>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace Aspose::Slides::Foss {

class HeadingPair;

/// Interface representing properties of a presentation.
class IDocumentProperties {
public:
    virtual ~IDocumentProperties() = default;

    // -- Core string properties --

    /// Returns the app version. Read-only.
    [[nodiscard]] virtual const std::string& app_version() const noexcept = 0;

    /// Returns the name of the application.
    [[nodiscard]] virtual const std::string& name_of_application() const noexcept = 0;
    /// Sets the name of the application.
    virtual void set_name_of_application(std::string value) = 0;

    /// Returns the company property.
    [[nodiscard]] virtual const std::string& company() const noexcept = 0;
    /// Sets the company property.
    virtual void set_company(std::string value) = 0;

    /// Returns the manager property.
    [[nodiscard]] virtual const std::string& manager() const noexcept = 0;
    /// Sets the manager property.
    virtual void set_manager(std::string value) = 0;

    /// Returns the intended format of the presentation.
    [[nodiscard]] virtual const std::string& presentation_format() const noexcept = 0;
    /// Sets the intended format of the presentation.
    virtual void set_presentation_format(std::string value) = 0;

    /// Returns whether the presentation is shared between multiple people.
    [[nodiscard]] virtual bool shared_doc() const noexcept = 0;
    /// Sets whether the presentation is shared between multiple people.
    virtual void set_shared_doc(bool value) noexcept = 0;

    /// Returns the template of the application.
    [[nodiscard]] virtual const std::string& application_template() const noexcept = 0;
    /// Sets the template of the application.
    virtual void set_application_template(std::string value) = 0;

    /// Returns total editing time of the presentation.
    [[nodiscard]] virtual std::chrono::minutes total_editing_time() const noexcept = 0;
    /// Sets total editing time of the presentation.
    virtual void set_total_editing_time(std::chrono::minutes value) noexcept = 0;

    /// Returns the title of the presentation.
    [[nodiscard]] virtual const std::string& title() const noexcept = 0;
    /// Sets the title of the presentation.
    virtual void set_title(std::string value) = 0;

    /// Returns the subject of the presentation.
    [[nodiscard]] virtual const std::string& subject() const noexcept = 0;
    /// Sets the subject of the presentation.
    virtual void set_subject(std::string value) = 0;

    /// Returns the author of the presentation.
    [[nodiscard]] virtual const std::string& author() const noexcept = 0;
    /// Sets the author of the presentation.
    virtual void set_author(std::string value) = 0;

    /// Returns the keywords of the presentation.
    [[nodiscard]] virtual const std::string& keywords() const noexcept = 0;
    /// Sets the keywords of the presentation.
    virtual void set_keywords(std::string value) = 0;

    /// Returns the comments of the presentation.
    [[nodiscard]] virtual const std::string& comments() const noexcept = 0;
    /// Sets the comments of the presentation.
    virtual void set_comments(std::string value) = 0;

    /// Returns the category of the presentation.
    [[nodiscard]] virtual const std::string& category() const noexcept = 0;
    /// Sets the category of the presentation.
    virtual void set_category(std::string value) = 0;

    /// Returns the date the presentation was created. Values are in UTC.
    [[nodiscard]] virtual std::optional<std::chrono::system_clock::time_point> created_time() const noexcept = 0;
    /// Sets the date the presentation was created.
    virtual void set_created_time(std::optional<std::chrono::system_clock::time_point> value) noexcept = 0;

    /// Returns the date the presentation was last modified. Values are in UTC.
    [[nodiscard]] virtual std::optional<std::chrono::system_clock::time_point> last_saved_time() const noexcept = 0;
    /// Sets the date the presentation was last modified.
    virtual void set_last_saved_time(std::optional<std::chrono::system_clock::time_point> value) noexcept = 0;

    /// Returns the date the presentation was last printed.
    [[nodiscard]] virtual std::optional<std::chrono::system_clock::time_point> last_printed() const noexcept = 0;
    /// Sets the date the presentation was last printed.
    virtual void set_last_printed(std::optional<std::chrono::system_clock::time_point> value) noexcept = 0;

    /// Returns the name of the last person who modified the presentation.
    [[nodiscard]] virtual const std::string& last_saved_by() const noexcept = 0;
    /// Sets the name of the last person who modified the presentation.
    virtual void set_last_saved_by(std::string value) = 0;

    /// Returns the presentation revision number.
    [[nodiscard]] virtual int revision_number() const noexcept = 0;
    /// Sets the presentation revision number.
    virtual void set_revision_number(int value) noexcept = 0;

    /// Returns the content status of the presentation.
    [[nodiscard]] virtual const std::string& content_status() const noexcept = 0;
    /// Sets the content status of the presentation.
    virtual void set_content_status(std::string value) = 0;

    /// Returns the content type of the presentation.
    [[nodiscard]] virtual const std::string& content_type() const noexcept = 0;
    /// Sets the content type of the presentation.
    virtual void set_content_type(std::string value) = 0;

    /// Returns the HyperlinkBase document property.
    [[nodiscard]] virtual const std::string& hyperlink_base() const noexcept = 0;
    /// Sets the HyperlinkBase document property.
    virtual void set_hyperlink_base(std::string value) = 0;

    /// Indicates the display mode of the document thumbnail.
    [[nodiscard]] virtual bool scale_crop() const noexcept = 0;
    /// Sets the display mode of the document thumbnail.
    virtual void set_scale_crop(bool value) noexcept = 0;

    /// Indicates whether hyperlinks in the document are up-to-date.
    [[nodiscard]] virtual bool links_up_to_date() const noexcept = 0;
    /// Sets whether hyperlinks in the document are up-to-date.
    virtual void set_links_up_to_date(bool value) noexcept = 0;

    /// Specifies that one or more hyperlinks were updated exclusively in this part.
    [[nodiscard]] virtual bool hyperlinks_changed() const noexcept = 0;
    /// Sets whether hyperlinks were changed.
    virtual void set_hyperlinks_changed(bool value) noexcept = 0;

    /// Returns the total number of slides. Read-only.
    [[nodiscard]] virtual int slides() const noexcept = 0;

    /// Returns the number of hidden slides. Read-only.
    [[nodiscard]] virtual int hidden_slides() const noexcept = 0;

    /// Returns the number of slides containing notes. Read-only.
    [[nodiscard]] virtual int notes() const noexcept = 0;

    /// Returns the total number of paragraphs. Read-only.
    [[nodiscard]] virtual int paragraphs() const noexcept = 0;

    /// Returns the total number of words. Read-only.
    [[nodiscard]] virtual int words() const noexcept = 0;

    /// Returns the total number of multimedia clips. Read-only.
    [[nodiscard]] virtual int multimedia_clips() const noexcept = 0;

    /// Returns the titles of document parts. Read-only.
    [[nodiscard]] virtual const std::vector<std::string>& titles_of_parts() const noexcept = 0;

    /// Returns the heading pairs indicating grouping of document parts. Read-only.
    [[nodiscard]] virtual const std::vector<HeadingPair>& heading_pairs() const noexcept = 0;

    /// Returns the number of custom properties.
    [[nodiscard]] virtual int count_of_custom_properties() const noexcept = 0;

    /// Gets a custom property value by name. Returns true if the property exists.
    [[nodiscard]] virtual bool get_custom_property_value(std::string_view name, std::any& out_value) const = 0;

    /// Sets a custom property value by name.
    virtual void set_custom_property_value(std::string_view name, std::any value) = 0;

    /// Returns the name of the custom property at the given index.
    [[nodiscard]] virtual std::string get_custom_property_name(int index) const = 0;

    /// Removes a custom property by name. Returns true if removed.
    virtual bool remove_custom_property(std::string_view name) = 0;

    /// Returns whether a custom property with the given name exists.
    [[nodiscard]] virtual bool contains_custom_property(std::string_view name) const = 0;

    /// Removes all custom properties.
    virtual void clear_custom_properties() = 0;

    /// Clears all built-in properties, resetting them to defaults.
    virtual void clear_built_in_properties() = 0;

protected:
    IDocumentProperties() = default;
    IDocumentProperties(const IDocumentProperties&) = default;
    IDocumentProperties& operator=(const IDocumentProperties&) = default;
    IDocumentProperties(IDocumentProperties&&) = default;
    IDocumentProperties& operator=(IDocumentProperties&&) = default;
};

} // namespace Aspose::Slides::Foss
