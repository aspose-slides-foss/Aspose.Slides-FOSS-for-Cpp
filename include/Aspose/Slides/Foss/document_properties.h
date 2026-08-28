// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <any>
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <Aspose/Slides/Foss/heading_pair.h>
#include <Aspose/Slides/Foss/i_document_properties.h>

namespace Aspose::Slides::Foss::Internal::opc {
class OpcPackage;
class InMemoryOpcPackage;
} // namespace Aspose::Slides::Foss::Internal::opc
namespace Aspose::Slides::Foss::Internal::pptx {
class CorePropertiesPart;
class AppPropertiesPart;
class CustomPropertiesPart;
} // namespace Aspose::Slides::Foss::Internal::pptx

namespace Aspose::Slides::Foss {

/// Represents properties of a presentation.
class DocumentProperties final : public IDocumentProperties {
public:
    DocumentProperties();
    DocumentProperties(const DocumentProperties&) = delete;
    DocumentProperties& operator=(const DocumentProperties&) = delete;
    ~DocumentProperties() override;
    DocumentProperties(DocumentProperties&&) noexcept;
    DocumentProperties& operator=(DocumentProperties&&) noexcept;

    // -- Core string properties --

    /// Returns the title of the presentation.
    [[nodiscard]] const std::string& title() const noexcept override;
    /// Sets the title of the presentation.
    void set_title(std::string value) override;

    /// Returns the subject of the presentation.
    [[nodiscard]] const std::string& subject() const noexcept override;
    /// Sets the subject of the presentation.
    void set_subject(std::string value) override;

    /// Returns the author of the presentation.
    [[nodiscard]] const std::string& author() const noexcept override;
    /// Sets the author of the presentation.
    void set_author(std::string value) override;

    /// Returns the keywords of the presentation.
    [[nodiscard]] const std::string& keywords() const noexcept override;
    /// Sets the keywords of the presentation.
    void set_keywords(std::string value) override;

    /// Returns the comments of the presentation.
    [[nodiscard]] const std::string& comments() const noexcept override;
    /// Sets the comments of the presentation.
    void set_comments(std::string value) override;

    /// Returns the category of the presentation.
    [[nodiscard]] const std::string& category() const noexcept override;
    /// Sets the category of the presentation.
    void set_category(std::string value) override;

    /// Returns the content status of the presentation.
    [[nodiscard]] const std::string& content_status() const noexcept override;
    /// Sets the content status of the presentation.
    void set_content_status(std::string value) override;

    /// Returns the content type of the presentation.
    [[nodiscard]] const std::string& content_type() const noexcept override;
    /// Sets the content type of the presentation.
    void set_content_type(std::string value) override;

    /// Returns the name of the last person who modified the presentation.
    [[nodiscard]] const std::string& last_saved_by() const noexcept override;
    /// Sets the name of the last person who modified the presentation.
    void set_last_saved_by(std::string value) override;

    // -- Revision number --

    /// Returns the presentation revision number.
    [[nodiscard]] int revision_number() const noexcept override;
    /// Sets the presentation revision number.
    void set_revision_number(int value) noexcept override;

    // -- Date/time properties --

    /// Returns the date the presentation was created. Values are in UTC.
    [[nodiscard]] std::optional<std::chrono::system_clock::time_point> created_time() const noexcept override;
    /// Sets the date the presentation was created.
    void set_created_time(std::optional<std::chrono::system_clock::time_point> value) noexcept override;

    /// Returns the date the presentation was last modified. Values are in UTC.
    [[nodiscard]] std::optional<std::chrono::system_clock::time_point> last_saved_time() const noexcept override;
    /// Sets the date the presentation was last modified.
    void set_last_saved_time(std::optional<std::chrono::system_clock::time_point> value) noexcept override;

    /// Returns the date the presentation was last printed.
    [[nodiscard]] std::optional<std::chrono::system_clock::time_point> last_printed() const noexcept override;
    /// Sets the date the presentation was last printed.
    void set_last_printed(std::optional<std::chrono::system_clock::time_point> value) noexcept override;

    // -- App properties (string) --

    /// Returns the app version. Read-only.
    [[nodiscard]] const std::string& app_version() const noexcept override;

    /// Returns the name of the application.
    [[nodiscard]] const std::string& name_of_application() const noexcept override;
    /// Sets the name of the application.
    void set_name_of_application(std::string value) override;

    /// Returns the company property.
    [[nodiscard]] const std::string& company() const noexcept override;
    /// Sets the company property.
    void set_company(std::string value) override;

    /// Returns the manager property.
    [[nodiscard]] const std::string& manager() const noexcept override;
    /// Sets the manager property.
    void set_manager(std::string value) override;

    /// Returns the intended format of the presentation.
    [[nodiscard]] const std::string& presentation_format() const noexcept override;
    /// Sets the intended format of the presentation.
    void set_presentation_format(std::string value) override;

    /// Returns the template of the application.
    [[nodiscard]] const std::string& application_template() const noexcept override;
    /// Sets the template of the application.
    void set_application_template(std::string value) override;

    /// Returns the HyperlinkBase document property.
    [[nodiscard]] const std::string& hyperlink_base() const noexcept override;
    /// Sets the HyperlinkBase document property.
    void set_hyperlink_base(std::string value) override;

    // -- Total editing time --

    /// Returns total editing time of the presentation.
    [[nodiscard]] std::chrono::minutes total_editing_time() const noexcept override;
    /// Sets total editing time of the presentation.
    void set_total_editing_time(std::chrono::minutes value) noexcept override;

    // -- Boolean app properties --

    /// Determines whether the presentation is shared between multiple people.
    [[nodiscard]] bool shared_doc() const noexcept override;
    /// Sets whether the presentation is shared between multiple people.
    void set_shared_doc(bool value) noexcept override;

    /// Indicates the display mode of the document thumbnail.
    [[nodiscard]] bool scale_crop() const noexcept override;
    /// Sets the display mode of the document thumbnail.
    void set_scale_crop(bool value) noexcept override;

    /// Indicates whether hyperlinks in the document are up-to-date.
    [[nodiscard]] bool links_up_to_date() const noexcept override;
    /// Sets whether hyperlinks in the document are up-to-date.
    void set_links_up_to_date(bool value) noexcept override;

    /// Specifies that one or more hyperlinks were updated exclusively in this part.
    [[nodiscard]] bool hyperlinks_changed() const noexcept override;
    /// Sets whether hyperlinks were changed.
    void set_hyperlinks_changed(bool value) noexcept override;

    // -- Read-only statistics --

    /// Returns the total number of slides. Read-only.
    [[nodiscard]] int slides() const noexcept override;

    /// Returns the number of hidden slides. Read-only.
    [[nodiscard]] int hidden_slides() const noexcept override;

    /// Returns the number of slides containing notes. Read-only.
    [[nodiscard]] int notes() const noexcept override;

    /// Returns the total number of paragraphs. Read-only.
    [[nodiscard]] int paragraphs() const noexcept override;

    /// Returns the total number of words. Read-only.
    [[nodiscard]] int words() const noexcept override;

    /// Returns the total number of multimedia clips. Read-only.
    [[nodiscard]] int multimedia_clips() const noexcept override;

    // -- Heading pairs and titles of parts --

    /// Returns the heading pairs indicating grouping of document parts. Read-only.
    [[nodiscard]] const std::vector<HeadingPair>& heading_pairs() const noexcept override;

    /// Returns the titles of document parts. Read-only.
    [[nodiscard]] const std::vector<std::string>& titles_of_parts() const noexcept override;

    // -- Custom properties --

    /// Returns the number of custom properties.
    [[nodiscard]] int count_of_custom_properties() const noexcept override;

    /// Gets a custom property value by name. Returns the value via out parameter.
    /// Returns true if the property exists, false otherwise.
    [[nodiscard]] bool get_custom_property_value(std::string_view name, std::any& out_value) const override;

    /// Sets a custom property value by name.
    void set_custom_property_value(std::string_view name, std::any value) override;

    /// Returns the name of the custom property at the given index.
    [[nodiscard]] std::string get_custom_property_name(int index) const override;

    /// Removes a custom property by name. Returns true if removed.
    bool remove_custom_property(std::string_view name) override;

    /// Returns whether a custom property with the given name exists.
    [[nodiscard]] bool contains_custom_property(std::string_view name) const override;

    /// Removes all custom properties.
    void clear_custom_properties() override;

    // -- Built-in property operations --

    /// Clears all built-in properties, resetting them to defaults.
    void clear_built_in_properties() override;

private:
    friend class Presentation;

    /// Initialize with an OPC package, loading all properties from parts.
    void init_internal(Internal::opc::OpcPackage& package);

    /// Lazily create and return the core properties part.
    Internal::pptx::CorePropertiesPart& ensure_core();

    /// Lazily create and return the app properties part.
    Internal::pptx::AppPropertiesPart& ensure_app();

    /// Lazily create and return the custom properties part.
    Internal::pptx::CustomPropertiesPart& ensure_custom();

    /// Serialize all loaded parts back to the package.
    void save_to_package();

    /// Recount the deck statistics `docProps/app.xml` reports, by reading the
    /// slide parts that were just written into @p package.
    ///
    /// Slides, notes, paragraphs and words are facts about the deck, not
    /// properties the caller sets, and they are only right if they are
    /// recomputed at save time. Counting the produced XML rather than the
    /// object model also keeps them true whichever serialiser wrote the
    /// slides.
    /// @param presentation_part Name of the main presentation part, whose
    ///        `p:sldIdLst` decides which parts count as slides of this deck.
    void refresh_statistics(const Internal::opc::InMemoryOpcPackage& package,
                            std::string_view presentation_part =
                                "ppt/presentation.xml");

    // OPC package binding
    Internal::opc::OpcPackage* package_ = nullptr;
    std::unique_ptr<Internal::pptx::CorePropertiesPart> core_part_;
    std::unique_ptr<Internal::pptx::AppPropertiesPart> app_part_;
    std::unique_ptr<Internal::pptx::CustomPropertiesPart> custom_part_;

    // Core properties
    std::string title_;
    std::string subject_;
    std::string author_;
    std::string keywords_;
    std::string comments_;
    std::string category_;
    std::string content_status_;
    std::string content_type_;
    std::string last_saved_by_;
    int revision_number_ = 0;
    std::optional<std::chrono::system_clock::time_point> created_time_;
    std::optional<std::chrono::system_clock::time_point> last_saved_time_;
    std::optional<std::chrono::system_clock::time_point> last_printed_;

    // App properties
    std::string app_version_ = "16.0000";
    std::string name_of_application_;
    std::string company_;
    std::string manager_;
    std::string presentation_format_;
    std::string application_template_;
    std::string hyperlink_base_;
    std::chrono::minutes total_editing_time_{0};
    bool shared_doc_ = false;
    bool scale_crop_ = false;
    bool links_up_to_date_ = false;
    bool hyperlinks_changed_ = false;

    // Read-only statistics
    int slides_count_ = 0;
    int hidden_slides_count_ = 0;
    int notes_count_ = 0;
    int paragraphs_count_ = 0;
    int words_count_ = 0;
    int multimedia_clips_count_ = 0;

    // Heading pairs and titles of parts
    std::vector<HeadingPair> heading_pairs_;
    std::vector<std::string> titles_of_parts_;

    // Custom properties (ordered by insertion via vector of keys)
    std::vector<std::string> custom_property_names_;
    std::unordered_map<std::string, std::any> custom_properties_;
};

} // namespace Aspose::Slides::Foss
