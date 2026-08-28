// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/document_properties.h>

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/app_properties_part.h>
#include <Aspose/Slides/Foss/_internal/pptx/core_properties_part.h>
#include <Aspose/Slides/Foss/_internal/pptx/custom_properties_part.h>

namespace Aspose::Slides::Foss {

DocumentProperties::DocumentProperties() = default;
DocumentProperties::~DocumentProperties() = default;
DocumentProperties::DocumentProperties(DocumentProperties&&) noexcept = default;
DocumentProperties& DocumentProperties::operator=(DocumentProperties&&) noexcept = default;

// -- Internal OPC bridge --

void DocumentProperties::init_internal(Internal::opc::OpcPackage& package) {
    package_ = &package;
    core_part_.reset();
    app_part_.reset();
    custom_part_.reset();

    // Load core properties
    auto& core = ensure_core();
    title_ = core.title.value_or("");
    subject_ = core.subject.value_or("");
    author_ = core.creator.value_or("");
    keywords_ = core.keywords.value_or("");
    comments_ = core.description.value_or("");
    category_ = core.category.value_or("");
    content_status_ = core.content_status.value_or("");
    content_type_ = core.content_type.value_or("");
    last_saved_by_ = core.last_modified_by.value_or("");
    if (core.revision) {
        try { revision_number_ = std::stoi(*core.revision); }
        catch (...) { revision_number_ = 0; } // best-effort parse
    } else {
        revision_number_ = 0;
    }
    created_time_ = core.created;
    last_saved_time_ = core.modified;
    last_printed_ = core.last_printed;

    // Load app properties
    auto& app = ensure_app();
    name_of_application_ = app.application.value_or("");
    app_version_ = app.app_version.value_or("16.0000");
    company_ = app.company.value_or("");
    manager_ = app.manager.value_or("");
    presentation_format_ = app.presentation_format.value_or("");
    application_template_ = app.template_name.value_or("");
    hyperlink_base_ = app.hyperlink_base.value_or("");
    total_editing_time_ = std::chrono::minutes(app.total_time.value_or(0));
    shared_doc_ = app.shared_doc.value_or(false);
    scale_crop_ = app.scale_crop.value_or(false);
    links_up_to_date_ = app.links_up_to_date.value_or(false);
    hyperlinks_changed_ = app.hyperlinks_changed.value_or(false);
    slides_count_ = app.slides.value_or(0);
    hidden_slides_count_ = app.hidden_slides.value_or(0);
    notes_count_ = app.notes.value_or(0);
    paragraphs_count_ = app.paragraphs.value_or(0);
    words_count_ = app.words.value_or(0);
    multimedia_clips_count_ = app.mm_clips.value_or(0);

    heading_pairs_.clear();
    for (const auto& hp : app.heading_pairs) {
        heading_pairs_.emplace_back(hp.name, hp.count);
    }
    titles_of_parts_ = app.titles_of_parts;

    // Load custom properties
    auto& custom = ensure_custom();
    custom_property_names_.clear();
    custom_properties_.clear();
    for (int32_t i = 0; i < custom.count(); ++i) {
        auto name = custom.get_name(i);
        auto value = custom.get_value(name);
        custom_property_names_.push_back(name);
        if (value) {
            custom_properties_[name] = std::visit(
                [](auto&& v) -> std::any { return v; }, *value);
        }
    }
}

Internal::pptx::CorePropertiesPart& DocumentProperties::ensure_core() {
    if (!core_part_) {
        core_part_ = std::make_unique<Internal::pptx::CorePropertiesPart>(
            *package_);
    }
    return *core_part_;
}

Internal::pptx::AppPropertiesPart& DocumentProperties::ensure_app() {
    if (!app_part_) {
        app_part_ = std::make_unique<Internal::pptx::AppPropertiesPart>(
            *package_);
    }
    return *app_part_;
}

Internal::pptx::CustomPropertiesPart& DocumentProperties::ensure_custom() {
    if (!custom_part_) {
        custom_part_ = std::make_unique<Internal::pptx::CustomPropertiesPart>(
            *package_);
    }
    return *custom_part_;
}

namespace {

/// Number of whitespace-separated tokens in @p text.
int count_words(std::string_view text) {
    int words = 0;
    bool in_word = false;
    for (unsigned char ch : text) {
        const bool space = std::isspace(ch) != 0;
        if (!space && !in_word) ++words;
        in_word = !space;
    }
    return words;
}

} // namespace

/// The slide parts the presentation actually registers, in `p:sldIdLst` order.
///
/// A slide-shaped part in the ZIP is not a slide of the deck: what makes it
/// one is a `<p:sldId>` whose `r:id` resolves to it. An orphan part that
/// survives a deletion would otherwise be counted, and docProps would disagree
/// with what opens.
static std::vector<std::string> registered_slide_parts(
    const Internal::opc::InMemoryOpcPackage& package,
    std::string_view presentation_part) {
    std::vector<std::string> result;

    auto content = package.get_part(std::string(presentation_part));
    if (!content) return result;
    pugi::xml_document doc;
    if (!doc.load_buffer(content->data(), content->size())) return result;

    auto slash = presentation_part.rfind('/');
    const std::string base =
        slash == std::string_view::npos
            ? std::string{}
            : std::string(presentation_part.substr(0, slash + 1));

    Internal::opc::RelationshipsManager rels(
        const_cast<Internal::opc::InMemoryOpcPackage&>(package),
        std::string(presentation_part));

    for (auto sld_id :
         doc.document_element().child("p:sldIdLst").children("p:sldId")) {
        auto r_id = sld_id.attribute("r:id").as_string("");
        if (!*r_id) continue;
        auto rel = rels.get_relationship(r_id);
        if (!rel) continue;
        result.push_back(rel->target.starts_with("/")
                             ? rel->target.substr(1)
                             : base + rel->target);
    }
    return result;
}

void DocumentProperties::refresh_statistics(
    const Internal::opc::InMemoryOpcPackage& package,
    std::string_view presentation_part) {
    int slides = 0;
    int hidden = 0;
    int notes = 0;
    int paragraphs = 0;
    int words = 0;

    const auto slide_parts = registered_slide_parts(package, presentation_part);

    for (const auto& name : package.get_part_names()) {
        const bool is_slide =
            std::find(slide_parts.begin(), slide_parts.end(), name) !=
            slide_parts.end();
        const bool is_notes = name.starts_with("ppt/notesSlides/notesSlide") &&
                              name.ends_with(".xml");
        if (!is_slide && !is_notes) continue;

        if (is_slide) ++slides;
        if (is_notes) ++notes;

        auto content = package.get_part(name);
        if (!content) continue;

        pugi::xml_document doc;
        if (!doc.load_buffer(content->data(), content->size())) continue;

        // A hidden slide carries show="0" on p:sld; the attribute defaults to
        // true and is normally absent.
        if (is_slide) {
            auto show = doc.document_element().attribute("show");
            if (show && !show.as_bool(true)) ++hidden;
        }

        // Count what the file actually says, so the two serialisers cannot
        // disagree with docProps about the same deck.
        for (auto node : doc.select_nodes("//a:p")) {
            (void)node;
            ++paragraphs;
        }
        for (auto node : doc.select_nodes("//a:t")) {
            words += count_words(node.node().text().as_string());
        }
    }

    slides_count_ = slides;
    hidden_slides_count_ = hidden;
    notes_count_ = notes;
    paragraphs_count_ = paragraphs;
    words_count_ = words;
}

void DocumentProperties::save_to_package() {
    // Always create parts when saving so properties set on a new presentation
    // are persisted, not just those loaded from an existing file.
    {
        auto& core = ensure_core();
        auto to_opt = [](const std::string& s) -> std::optional<std::string> {
            return s.empty() ? std::nullopt : std::optional(s);
        };
        core.title = to_opt(title_);
        core.subject = to_opt(subject_);
        core.creator = to_opt(author_);
        core.keywords = to_opt(keywords_);
        core.description = to_opt(comments_);
        core.category = to_opt(category_);
        core.content_status = to_opt(content_status_);
        core.content_type = to_opt(content_type_);
        core.last_modified_by = to_opt(last_saved_by_);
        core.revision = revision_number_ != 0
            ? std::optional(std::to_string(revision_number_))
            : std::nullopt;
        core.created = created_time_;
        core.modified = last_saved_time_;
        core.last_printed = last_printed_;
        core.mark_dirty();
        core.save();
    }

    {
        auto& app = ensure_app();
        auto to_opt = [](const std::string& s) -> std::optional<std::string> {
            return s.empty() ? std::nullopt : std::optional(s);
        };
        app.application = to_opt(name_of_application_);
        app.app_version = to_opt(app_version_);
        app.company = to_opt(company_);
        app.manager = to_opt(manager_);
        app.presentation_format = to_opt(presentation_format_);
        app.template_name = to_opt(application_template_);
        app.hyperlink_base = to_opt(hyperlink_base_);
        app.total_time = static_cast<int>(total_editing_time_.count());
        app.shared_doc = shared_doc_;
        app.scale_crop = scale_crop_;
        app.links_up_to_date = links_up_to_date_;
        app.hyperlinks_changed = hyperlinks_changed_;
        app.slides = slides_count_;
        app.hidden_slides = hidden_slides_count_;
        app.notes = notes_count_;
        app.paragraphs = paragraphs_count_;
        app.words = words_count_;
        app.mm_clips = multimedia_clips_count_;

        app.heading_pairs.clear();
        for (const auto& hp : heading_pairs_) {
            app.heading_pairs.push_back({hp.name(), hp.count()});
        }
        app.titles_of_parts = titles_of_parts_;
        app.mark_dirty();
        app.save();
    }

    if (!custom_property_names_.empty()) {
        auto& custom = ensure_custom();
        custom.clear();
        for (const auto& name : custom_property_names_) {
            auto it = custom_properties_.find(name);
            if (it == custom_properties_.end()) continue;
            const auto& val = it->second;
            // Convert std::any back to CustomPropertyValue
            using CPV = Internal::pptx::CustomPropertyValue;
            if (auto* s = std::any_cast<std::string>(&val)) {
                custom.set_value(name, CPV{*s});
            } else if (auto* i32 = std::any_cast<int32_t>(&val)) {
                custom.set_value(name, CPV{*i32});
            } else if (auto* i = std::any_cast<int>(&val)) {
                custom.set_value(name, CPV{static_cast<int32_t>(*i)});
            } else if (auto* d = std::any_cast<double>(&val)) {
                custom.set_value(name, CPV{*d});
            } else if (auto* b = std::any_cast<bool>(&val)) {
                custom.set_value(name, CPV{*b});
            } else if (auto* tp = std::any_cast<Internal::pptx::CustomTimePoint>(&val)) {
                custom.set_value(name, CPV{*tp});
            }
        }
        custom.save();
    }
}

// -- Core string properties --

const std::string& DocumentProperties::title() const noexcept { return title_; }
void DocumentProperties::set_title(std::string value) { title_ = std::move(value); }

const std::string& DocumentProperties::subject() const noexcept { return subject_; }
void DocumentProperties::set_subject(std::string value) { subject_ = std::move(value); }

const std::string& DocumentProperties::author() const noexcept { return author_; }
void DocumentProperties::set_author(std::string value) { author_ = std::move(value); }

const std::string& DocumentProperties::keywords() const noexcept { return keywords_; }
void DocumentProperties::set_keywords(std::string value) { keywords_ = std::move(value); }

const std::string& DocumentProperties::comments() const noexcept { return comments_; }
void DocumentProperties::set_comments(std::string value) { comments_ = std::move(value); }

const std::string& DocumentProperties::category() const noexcept { return category_; }
void DocumentProperties::set_category(std::string value) { category_ = std::move(value); }

const std::string& DocumentProperties::content_status() const noexcept { return content_status_; }
void DocumentProperties::set_content_status(std::string value) { content_status_ = std::move(value); }

const std::string& DocumentProperties::content_type() const noexcept { return content_type_; }
void DocumentProperties::set_content_type(std::string value) { content_type_ = std::move(value); }

const std::string& DocumentProperties::last_saved_by() const noexcept { return last_saved_by_; }
void DocumentProperties::set_last_saved_by(std::string value) { last_saved_by_ = std::move(value); }

// -- Revision number --

int DocumentProperties::revision_number() const noexcept { return revision_number_; }
void DocumentProperties::set_revision_number(int value) noexcept { revision_number_ = value; }

// -- Date/time properties --

std::optional<std::chrono::system_clock::time_point> DocumentProperties::created_time() const noexcept {
    return created_time_;
}
void DocumentProperties::set_created_time(std::optional<std::chrono::system_clock::time_point> value) noexcept {
    created_time_ = value;
}

std::optional<std::chrono::system_clock::time_point> DocumentProperties::last_saved_time() const noexcept {
    return last_saved_time_;
}
void DocumentProperties::set_last_saved_time(std::optional<std::chrono::system_clock::time_point> value) noexcept {
    last_saved_time_ = value;
}

std::optional<std::chrono::system_clock::time_point> DocumentProperties::last_printed() const noexcept {
    return last_printed_;
}
void DocumentProperties::set_last_printed(std::optional<std::chrono::system_clock::time_point> value) noexcept {
    last_printed_ = value;
}

// -- App properties (string) --

const std::string& DocumentProperties::app_version() const noexcept { return app_version_; }

const std::string& DocumentProperties::name_of_application() const noexcept { return name_of_application_; }
void DocumentProperties::set_name_of_application(std::string value) { name_of_application_ = std::move(value); }

const std::string& DocumentProperties::company() const noexcept { return company_; }
void DocumentProperties::set_company(std::string value) { company_ = std::move(value); }

const std::string& DocumentProperties::manager() const noexcept { return manager_; }
void DocumentProperties::set_manager(std::string value) { manager_ = std::move(value); }

const std::string& DocumentProperties::presentation_format() const noexcept { return presentation_format_; }
void DocumentProperties::set_presentation_format(std::string value) { presentation_format_ = std::move(value); }

const std::string& DocumentProperties::application_template() const noexcept { return application_template_; }
void DocumentProperties::set_application_template(std::string value) { application_template_ = std::move(value); }

const std::string& DocumentProperties::hyperlink_base() const noexcept { return hyperlink_base_; }
void DocumentProperties::set_hyperlink_base(std::string value) { hyperlink_base_ = std::move(value); }

// -- Total editing time --

std::chrono::minutes DocumentProperties::total_editing_time() const noexcept { return total_editing_time_; }
void DocumentProperties::set_total_editing_time(std::chrono::minutes value) noexcept { total_editing_time_ = value; }

// -- Boolean app properties --

bool DocumentProperties::shared_doc() const noexcept { return shared_doc_; }
void DocumentProperties::set_shared_doc(bool value) noexcept { shared_doc_ = value; }

bool DocumentProperties::scale_crop() const noexcept { return scale_crop_; }
void DocumentProperties::set_scale_crop(bool value) noexcept { scale_crop_ = value; }

bool DocumentProperties::links_up_to_date() const noexcept { return links_up_to_date_; }
void DocumentProperties::set_links_up_to_date(bool value) noexcept { links_up_to_date_ = value; }

bool DocumentProperties::hyperlinks_changed() const noexcept { return hyperlinks_changed_; }
void DocumentProperties::set_hyperlinks_changed(bool value) noexcept { hyperlinks_changed_ = value; }

// -- Read-only statistics --

int DocumentProperties::slides() const noexcept { return slides_count_; }
int DocumentProperties::hidden_slides() const noexcept { return hidden_slides_count_; }
int DocumentProperties::notes() const noexcept { return notes_count_; }
int DocumentProperties::paragraphs() const noexcept { return paragraphs_count_; }
int DocumentProperties::words() const noexcept { return words_count_; }
int DocumentProperties::multimedia_clips() const noexcept { return multimedia_clips_count_; }

// -- Heading pairs and titles of parts --

const std::vector<HeadingPair>& DocumentProperties::heading_pairs() const noexcept {
    return heading_pairs_;
}

const std::vector<std::string>& DocumentProperties::titles_of_parts() const noexcept {
    return titles_of_parts_;
}

// -- Custom properties --

int DocumentProperties::count_of_custom_properties() const noexcept {
    return static_cast<int>(custom_property_names_.size());
}

bool DocumentProperties::get_custom_property_value(std::string_view name, std::any& out_value) const {
    auto it = custom_properties_.find(std::string(name));
    if (it != custom_properties_.end()) {
        out_value = it->second;
        return true;
    }
    return false;
}

void DocumentProperties::set_custom_property_value(std::string_view name, std::any value) {
    auto key = std::string(name);
    if (custom_properties_.find(key) == custom_properties_.end()) {
        custom_property_names_.push_back(key);
    }
    custom_properties_[key] = std::move(value);
}

std::string DocumentProperties::get_custom_property_name(int index) const {
    if (index < 0 || index >= static_cast<int>(custom_property_names_.size())) {
        throw std::out_of_range("Custom property index out of range");
    }
    return custom_property_names_[static_cast<std::size_t>(index)];
}

bool DocumentProperties::remove_custom_property(std::string_view name) {
    auto key = std::string(name);
    auto it = custom_properties_.find(key);
    if (it == custom_properties_.end()) {
        return false;
    }
    custom_properties_.erase(it);
    auto name_it = std::find(custom_property_names_.begin(), custom_property_names_.end(), key);
    if (name_it != custom_property_names_.end()) {
        custom_property_names_.erase(name_it);
    }
    return true;
}

bool DocumentProperties::contains_custom_property(std::string_view name) const {
    return custom_properties_.find(std::string(name)) != custom_properties_.end();
}

void DocumentProperties::clear_custom_properties() {
    custom_property_names_.clear();
    custom_properties_.clear();
}

// -- Built-in property operations --

void DocumentProperties::clear_built_in_properties() {
    // Reset core properties
    title_.clear();
    subject_.clear();
    author_.clear();
    keywords_.clear();
    comments_.clear();
    category_.clear();
    content_status_.clear();
    content_type_.clear();
    last_saved_by_.clear();
    revision_number_ = 0;
    created_time_.reset();
    last_saved_time_.reset();
    last_printed_.reset();

    // Reset app properties
    name_of_application_.clear();
    company_.clear();
    manager_.clear();
    presentation_format_.clear();
    application_template_.clear();
    hyperlink_base_.clear();
    total_editing_time_ = std::chrono::minutes{0};
    shared_doc_ = false;
    scale_crop_ = false;
    links_up_to_date_ = false;
    hyperlinks_changed_ = false;
}

} // namespace Aspose::Slides::Foss
