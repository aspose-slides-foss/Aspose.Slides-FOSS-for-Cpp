// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/presentation.h>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <stdexcept>
#include <unordered_map>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/comment_authors_part.h>
#include <Aspose/Slides/Foss/_internal/pptx/comments_part.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/layout_slide_part.h>
#include <Aspose/Slides/Foss/_internal/pptx/master_slide_part.h>
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/base_portion_format.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/paragraph_collection.h>
#include <Aspose/Slides/Foss/paragraph_format.h>
#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_collection.h>
#include <Aspose/Slides/Foss/portion_format.h>
#include <Aspose/Slides/Foss/text_alignment.h>
#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/text_strikethrough_type.h>
#include <Aspose/Slides/Foss/text_underline_type.h>
#include <Aspose/Slides/Foss/comment.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/image_utils.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/cell_format.h>
#include <Aspose/Slides/Foss/column.h>
#include <Aspose/Slides/Foss/column_collection.h>
#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/row.h>
#include <Aspose/Slides/Foss/row_collection.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/table.h>
#include <Aspose/Slides/Foss/three_d_format.h>
#include <Aspose/Slides/Foss/_internal/pptx/notes_slide_part.h>

namespace Aspose::Slides::Foss {

Presentation::Presentation() : masters_(this), slides_(this) {}

Presentation::Presentation(std::string_view path) : masters_(this), slides_(this) {
    namespace pptx = Internal::pptx;

    // Open the OPC package from file.
    auto pkg = std::make_unique<Internal::opc::InMemoryOpcPackage>(
        Internal::opc::InMemoryOpcPackage::open(std::filesystem::path(std::string(path))));
    owned_opc_package_ = std::move(pkg);
    opc_package_ = owned_opc_package_.get();

    // Detect source format from file extension.
    detect_source_format(path);

    // Find presentation part name via the package relationships.
    Internal::opc::RelationshipsManager root_rels(*opc_package_, "");
    std::string pres_part_name;
    auto root_rel_list = root_rels.get_relationships_by_type(
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument");
    if (!root_rel_list.empty()) {
        pres_part_name = root_rel_list.front().target;
        // Strip leading slash if present.
        if (!pres_part_name.empty() && pres_part_name.front() == '/') {
            pres_part_name = pres_part_name.substr(1);
        }
    }
    if (pres_part_name.empty()) {
        pres_part_name = "ppt/presentation.xml";
    }
    presentation_part_name_ = pres_part_name;

    // Parse presentation.xml to extract slide references.
    auto pres_content = opc_package_->get_part(pres_part_name);
    std::vector<SlideReference> slide_refs;
    if (pres_content) {
        pugi::xml_document doc;
        doc.load_buffer(pres_content->data(), pres_content->size());
        auto pres_node = doc.first_child();

        // Parse firstSlideNum attribute if present.
        auto first_sld_attr = pres_node.attribute("firstSlideNum");
        if (first_sld_attr) {
            first_slide_number_ = first_sld_attr.as_int(1);
        }

        // Try both prefixed and Clark-notation forms for sldIdLst.
        auto sld_id_lst = pres_node.child("p:sldIdLst");
        if (!sld_id_lst) {
            sld_id_lst = pres_node.child(pptx::Elements::kSldIdLst.c_str());
        }
        if (sld_id_lst) {
            for (auto child : sld_id_lst.children()) {
                SlideReference ref;
                auto id_attr = child.attribute("id");
                if (id_attr) {
                    ref.slide_id = std::strtoll(id_attr.as_string(), nullptr, 10);
                }
                // Try both r:id and Clark-notation.
                auto rid_attr = child.attribute("r:id");
                if (!rid_attr) {
                    rid_attr = child.attribute(pptx::Attributes::kRId.c_str());
                }
                if (rid_attr) {
                    ref.r_id = rid_attr.as_string();
                }
                slide_refs.push_back(std::move(ref));
            }
        }
    }

    // Initialize slides with layout resolution.
    slides_.init_internal(
        this, opc_package_, pres_part_name, std::move(slide_refs),
        [this](std::string_view layout_pn) -> LayoutSlide* {
            return resolve_layout_slide(layout_pn);
        });

    // --- Load comment authors ---
    if (opc_package_->has_part(pptx::kCommentAuthorsPartName)) {
        auto authors_part =
            std::make_unique<pptx::CommentAuthorsPart>(*opc_package_);
        comment_authors_.init_internal(
            *authors_part, *opc_package_, this);

        // --- Load comments for each slide ---
        for (std::size_t si = 0; si < slides_.size(); ++si) {
            auto& slide = slides_[si];
            int slide_num = static_cast<int>(si) + 1;
            std::string slide_part_name =
                "ppt/slides/slide" + std::to_string(slide_num) + ".xml";

            auto comments_part =
                pptx::CommentsPart::load_for_slide(*opc_package_, slide_part_name);
            if (!comments_part) continue;

            for (auto& cd : comments_part->get_comments()) {
                int32_t author_id = cd.author_id();
                // Find the matching author in our collection.
                for (std::size_t a = 0; a < comment_authors_.size(); ++a) {
                    auto& ca = comment_authors_[a];
                    if (ca.has_internal_data() &&
                        ca.internal_data()->id() == author_id) {
                        auto dt = pptx::str_to_dt(cd.dt_str());
                        auto tp = dt.value_or(
                            std::chrono::system_clock::now());
                        Drawing::PointF pos(
                            static_cast<float>(cd.pos_x()),
                            static_cast<float>(cd.pos_y()));
                        ca.comments().add_comment(
                            cd.text(), slide, pos, tp);
                        break;
                    }
                }
            }
        }

        // Keep the authors_part alive for the lifetime of the presentation.
        owned_authors_part_ = std::move(authors_part);
    }

    // --- Load document properties ---
    document_properties_.init_internal(*opc_package_);
}

Presentation::~Presentation() {
    dispose();
}

IPresentation* Presentation::presentation() { return this; }
const IPresentation* Presentation::presentation() const { return this; }

std::chrono::system_clock::time_point Presentation::current_date_time() const {
    return current_date_time_;
}

void Presentation::set_current_date_time(std::chrono::system_clock::time_point value) {
    current_date_time_ = value;
}

SlideCollection& Presentation::slides() noexcept { return slides_; }
const SlideCollection& Presentation::slides() const noexcept { return slides_; }

CommentAuthorCollection& Presentation::comment_authors() noexcept {
    return comment_authors_;
}

const CommentAuthorCollection& Presentation::comment_authors() const noexcept {
    return comment_authors_;
}

ImageCollection& Presentation::images() noexcept { return images_; }
const ImageCollection& Presentation::images() const noexcept { return images_; }

DocumentProperties& Presentation::document_properties() noexcept {
    return document_properties_;
}

const DocumentProperties& Presentation::document_properties() const noexcept {
    return document_properties_;
}

GlobalLayoutSlideCollection& Presentation::layout_slides() noexcept {
    return layout_slides_;
}

const GlobalLayoutSlideCollection& Presentation::layout_slides() const noexcept {
    return layout_slides_;
}

MasterSlideCollection& Presentation::masters() noexcept { return masters_; }
const MasterSlideCollection& Presentation::masters() const noexcept { return masters_; }

NotesSize& Presentation::notes_size() noexcept { return notes_size_; }
const NotesSize& Presentation::notes_size() const noexcept { return notes_size_; }

SourceFormat Presentation::source_format() const { return source_format_; }

int Presentation::first_slide_number() const { return first_slide_number_; }

void Presentation::set_first_slide_number(int value) { first_slide_number_ = value; }

IPresentationComponent* Presentation::as_i_presentation_component() { return this; }
const IPresentationComponent* Presentation::as_i_presentation_component() const {
    return this;
}

namespace {

namespace pptx_const = Internal::pptx;

/// Convert points to EMU string.
std::string to_emu_str(double points) {
    return std::to_string(static_cast<int>(std::round(points * pptx_const::kEmuPerPoint)));
}

/// Map TextAlignment to OOXML algn attribute value.
const char* alignment_to_ooxml_str(TextAlignment a) {
    switch (a) {
        case TextAlignment::LEFT:        return "l";
        case TextAlignment::CENTER:      return "ctr";
        case TextAlignment::RIGHT:       return "r";
        case TextAlignment::JUSTIFY:     return "just";
        case TextAlignment::JUSTIFY_LOW: return "justLow";
        case TextAlignment::DISTRIBUTED: return "dist";
        default: return nullptr;
    }
}

/// Map TextUnderlineType to OOXML u attribute value.
const char* underline_to_ooxml_str(TextUnderlineType t) {
    switch (t) {
        case TextUnderlineType::NONE:             return "none";
        case TextUnderlineType::WORDS:            return "words";
        case TextUnderlineType::SINGLE:           return "sng";
        case TextUnderlineType::DOUBLE:           return "dbl";
        case TextUnderlineType::HEAVY:            return "heavy";
        case TextUnderlineType::DOTTED:           return "dotted";
        case TextUnderlineType::HEAVY_DOTTED:     return "dottedHeavy";
        case TextUnderlineType::DASHED:           return "dash";
        case TextUnderlineType::HEAVY_DASHED:     return "dashHeavy";
        case TextUnderlineType::LONG_DASHED:      return "dashLong";
        case TextUnderlineType::HEAVY_LONG_DASHED:return "dashLongHeavy";
        case TextUnderlineType::DOT_DASH:         return "dotDash";
        case TextUnderlineType::HEAVY_DOT_DASH:   return "dotDashHeavy";
        case TextUnderlineType::DOT_DOT_DASH:     return "dotDotDash";
        case TextUnderlineType::HEAVY_DOT_DOT_DASH: return "dotDotDashHeavy";
        case TextUnderlineType::WAVY:             return "wavy";
        case TextUnderlineType::HEAVY_WAVY:       return "wavyHeavy";
        case TextUnderlineType::DOUBLE_WAVY:      return "wavyDbl";
        default: return nullptr;
    }
}

/// Map TextStrikethroughType to OOXML strike attribute value.
const char* strike_to_ooxml_str(TextStrikethroughType t) {
    switch (t) {
        case TextStrikethroughType::NONE:   return "noStrike";
        case TextStrikethroughType::SINGLE: return "sngStrike";
        case TextStrikethroughType::DOUBLE: return "dblStrike";
        default: return nullptr;
    }
}

/// Serialize a PortionFormat's properties onto an <a:rPr> XML node.
void serialize_rpr(pugi::xml_node rpr, IBasePortionFormat& fmt) {
    if (fmt.font_bold() == NullableBool::TRUE)
        rpr.append_attribute("b") = "1";
    else if (fmt.font_bold() == NullableBool::FALSE)
        rpr.append_attribute("b") = "0";

    if (fmt.font_italic() == NullableBool::TRUE)
        rpr.append_attribute("i") = "1";
    else if (fmt.font_italic() == NullableBool::FALSE)
        rpr.append_attribute("i") = "0";

    if (fmt.font_underline() != TextUnderlineType::NOT_DEFINED) {
        auto val = underline_to_ooxml_str(fmt.font_underline());
        if (val) rpr.append_attribute("u") = val;
    }

    if (fmt.strikethrough_type() != TextStrikethroughType::NOT_DEFINED) {
        auto val = strike_to_ooxml_str(fmt.strikethrough_type());
        if (val) rpr.append_attribute("strike") = val;
    }

    if (!std::isnan(fmt.font_height())) {
        rpr.append_attribute("sz") =
            std::to_string(static_cast<int>(std::round(fmt.font_height() * 100))).c_str();
    }

    // Solid fill color.
    if (fmt.fill_format().fill_type() == FillType::SOLID) {
        auto sf = rpr.append_child("a:solidFill");
        auto clr = fmt.fill_format().solid_fill_color().color();
        auto srgb = sf.append_child("a:srgbClr");
        char hex[8];
        snprintf(hex, sizeof(hex), "%02X%02X%02X", clr.r(), clr.g(), clr.b());
        srgb.append_attribute("val") = hex;
    }

    // Latin font.
    if (fmt.latin_font().has_value()) {
        auto node = rpr.append_child("a:latin");
        node.append_attribute("typeface") = fmt.latin_font()->font_name().c_str();
    }

    // East Asian font.
    if (fmt.east_asian_font().has_value()) {
        auto node = rpr.append_child("a:ea");
        node.append_attribute("typeface") = fmt.east_asian_font()->font_name().c_str();
    }

    // Complex script font.
    if (fmt.complex_script_font().has_value()) {
        auto node = rpr.append_child("a:cs");
        node.append_attribute("typeface") = fmt.complex_script_font()->font_name().c_str();
    }
}

/// Returns true if the portion format has any non-default properties.
bool has_rpr_properties(IBasePortionFormat& fmt) {
    return fmt.font_bold() != NullableBool::NOT_DEFINED ||
           fmt.font_italic() != NullableBool::NOT_DEFINED ||
           fmt.font_underline() != TextUnderlineType::NOT_DEFINED ||
           fmt.strikethrough_type() != TextStrikethroughType::NOT_DEFINED ||
           !std::isnan(fmt.font_height()) ||
           fmt.fill_format().fill_type() == FillType::SOLID ||
           fmt.latin_font().has_value() ||
           fmt.east_asian_font().has_value() ||
           fmt.complex_script_font().has_value();
}

/// Serialize a pugi::xml_document to a byte vector.
std::vector<uint8_t> serialize_xml(pugi::xml_document& doc) {
    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;
    doc.save(writer, "  ");
    return std::move(writer.result);
}

} // anonymous namespace

void Presentation::save(std::string_view path, SaveFormat /*format*/) {
    namespace opc = Internal::opc;
    namespace pptx = Internal::pptx;

    int img_counter = 1;

    // If we already have an OPC package (loaded from file), reuse it.
    // Otherwise create a new package from scratch.
    opc::InMemoryOpcPackage* pkg = nullptr;
    std::unique_ptr<opc::InMemoryOpcPackage> new_pkg;

    if (owned_opc_package_) {
        pkg = owned_opc_package_.get();
    } else {
        new_pkg = std::make_unique<opc::InMemoryOpcPackage>(
            opc::InMemoryOpcPackage::create_new());
        pkg = new_pkg.get();
    }

    const std::string pres_part = presentation_part_name_.empty()
        ? "ppt/presentation.xml" : presentation_part_name_;

    // --- Build presentation.xml ---
    if (!pkg->has_part(pres_part)) {

        // --- Emit minimal theme / slide-master / slide-layout ----------------
        // These are required by the OOXML spec for a valid presentation.

        const std::string theme_part   = "ppt/theme/theme1.xml";
        const std::string master_part  = "ppt/slideMasters/slideMaster1.xml";
        const std::string layout_part  = "ppt/slideLayouts/slideLayout1.xml";

        // Theme
        {
            const char* theme_xml =
                "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
                "<a:theme xmlns:a=\"http://schemas.openxmlformats.org/drawingml/2006/main\" name=\"Office Theme\">"
                "<a:themeElements>"
                "<a:clrScheme name=\"Office\">"
                "<a:dk1><a:sysClr val=\"windowText\" lastClr=\"000000\"/></a:dk1>"
                "<a:lt1><a:sysClr val=\"window\" lastClr=\"FFFFFF\"/></a:lt1>"
                "<a:dk2><a:srgbClr val=\"44546A\"/></a:dk2>"
                "<a:lt2><a:srgbClr val=\"E7E6E6\"/></a:lt2>"
                "<a:accent1><a:srgbClr val=\"4472C4\"/></a:accent1>"
                "<a:accent2><a:srgbClr val=\"ED7D31\"/></a:accent2>"
                "<a:accent3><a:srgbClr val=\"A5A5A5\"/></a:accent3>"
                "<a:accent4><a:srgbClr val=\"FFC000\"/></a:accent4>"
                "<a:accent5><a:srgbClr val=\"5B9BD5\"/></a:accent5>"
                "<a:accent6><a:srgbClr val=\"70AD47\"/></a:accent6>"
                "<a:hlink><a:srgbClr val=\"0563C1\"/></a:hlink>"
                "<a:folHlink><a:srgbClr val=\"954F72\"/></a:folHlink>"
                "</a:clrScheme>"
                "<a:fontScheme name=\"Office\">"
                "<a:majorFont><a:latin typeface=\"Calibri Light\"/><a:ea typeface=\"\"/><a:cs typeface=\"\"/></a:majorFont>"
                "<a:minorFont><a:latin typeface=\"Calibri\"/><a:ea typeface=\"\"/><a:cs typeface=\"\"/></a:minorFont>"
                "</a:fontScheme>"
                "<a:fmtScheme name=\"Office\">"
                "<a:fillStyleLst>"
                "<a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill>"
                "<a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill>"
                "<a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill>"
                "</a:fillStyleLst>"
                "<a:lnStyleLst>"
                "<a:ln w=\"6350\"><a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill></a:ln>"
                "<a:ln w=\"12700\"><a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill></a:ln>"
                "<a:ln w=\"19050\"><a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill></a:ln>"
                "</a:lnStyleLst>"
                "<a:effectStyleLst>"
                "<a:effectStyle><a:effectLst/></a:effectStyle>"
                "<a:effectStyle><a:effectLst/></a:effectStyle>"
                "<a:effectStyle><a:effectLst/></a:effectStyle>"
                "</a:effectStyleLst>"
                "<a:bgFillStyleLst>"
                "<a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill>"
                "<a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill>"
                "<a:solidFill><a:schemeClr val=\"phClr\"/></a:solidFill>"
                "</a:bgFillStyleLst>"
                "</a:fmtScheme>"
                "</a:themeElements>"
                "</a:theme>";
            std::string s(theme_xml);
            pkg->set_part(theme_part, std::vector<uint8_t>(s.begin(), s.end()));
        }

        // Slide master
        {
            const char* master_xml =
                "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
                "<p:sldMaster xmlns:a=\"http://schemas.openxmlformats.org/drawingml/2006/main\""
                " xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\""
                " xmlns:p=\"http://schemas.openxmlformats.org/presentationml/2006/main\">"
                "<p:cSld><p:spTree>"
                "<p:nvGrpSpPr><p:cNvPr id=\"1\" name=\"\"/><p:cNvGrpSpPr/><p:nvPr/></p:nvGrpSpPr>"
                "<p:grpSpPr/>"
                "</p:spTree></p:cSld>"
                "<p:clrMap bg1=\"lt1\" tx1=\"dk1\" bg2=\"lt2\" tx2=\"dk2\""
                " accent1=\"accent1\" accent2=\"accent2\" accent3=\"accent3\""
                " accent4=\"accent4\" accent5=\"accent5\" accent6=\"accent6\""
                " hlink=\"hlink\" folHlink=\"folHlink\"/>"
                "<p:sldLayoutIdLst>"
                "<p:sldLayoutId id=\"2147483649\" r:id=\"rId1\"/>"
                "</p:sldLayoutIdLst>"
                "</p:sldMaster>";
            std::string s(master_xml);
            pkg->set_part(master_part, std::vector<uint8_t>(s.begin(), s.end()));

            // master rels: layout + theme
            opc::RelationshipsManager master_rels(*pkg, master_part);
            master_rels.add_relationship(
                opc::rel_types::kSlideLayout, "../slideLayouts/slideLayout1.xml");
            master_rels.add_relationship(
                opc::rel_types::kTheme, "../theme/theme1.xml");
            master_rels.save();
        }

        // Slide layout
        {
            const char* layout_xml =
                "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
                "<p:sldLayout xmlns:a=\"http://schemas.openxmlformats.org/drawingml/2006/main\""
                " xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\""
                " xmlns:p=\"http://schemas.openxmlformats.org/presentationml/2006/main\""
                " type=\"blank\" preserve=\"1\">"
                "<p:cSld name=\"Blank\"><p:spTree>"
                "<p:nvGrpSpPr><p:cNvPr id=\"1\" name=\"\"/><p:cNvGrpSpPr/><p:nvPr/></p:nvGrpSpPr>"
                "<p:grpSpPr/>"
                "</p:spTree></p:cSld>"
                "</p:sldLayout>";
            std::string s(layout_xml);
            pkg->set_part(layout_part, std::vector<uint8_t>(s.begin(), s.end()));

            // layout rels: master
            opc::RelationshipsManager layout_rels(*pkg, layout_part);
            layout_rels.add_relationship(
                opc::rel_types::kSlideMaster, "../slideMasters/slideMaster1.xml");
            layout_rels.save();
        }

        // Content types for theme / master / layout
        {
            opc::ContentTypesManager ct(*pkg);
            ct.add_override(master_part,
                "application/vnd.openxmlformats-officedocument.presentationml.slideMaster+xml");
            ct.add_override(layout_part,
                "application/vnd.openxmlformats-officedocument.presentationml.slideLayout+xml");
            ct.add_override(theme_part,
                "application/vnd.openxmlformats-officedocument.theme+xml");
            ct.save();
        }

        // --- Build the actual presentation.xml -------------------------------

        pugi::xml_document doc;
        auto decl = doc.append_child(pugi::node_declaration);
        decl.append_attribute("version") = "1.0";
        decl.append_attribute("encoding") = "UTF-8";
        decl.append_attribute("standalone") = "yes";

        auto pres_node = doc.append_child("p:presentation");
        pres_node.append_attribute("xmlns:a") =
            std::string(pptx::ns_uri::kA).c_str();
        pres_node.append_attribute("xmlns:r") =
            std::string(pptx::ns_uri::kR).c_str();
        pres_node.append_attribute("xmlns:p") =
            std::string(pptx::ns_uri::kP).c_str();

        if (first_slide_number_ != 1) {
            pres_node.append_attribute("firstSlideNum") =
                std::to_string(first_slide_number_).c_str();
        }

        // sldMasterIdLst
        auto sld_master_id_lst = pres_node.append_child("p:sldMasterIdLst");
        auto sld_master_id = sld_master_id_lst.append_child("p:sldMasterId");
        sld_master_id.append_attribute("id") = "2147483648";

        auto sld_id_lst = pres_node.append_child("p:sldIdLst");

        // Add slide references and create slide parts.
        opc::RelationshipsManager pres_rels(*pkg, pres_part);

        // Presentation → slide master relationship
        auto master_rid = pres_rels.add_relationship(
            opc::rel_types::kSlideMaster, "slideMasters/slideMaster1.xml");
        sld_master_id.append_attribute("r:id") = master_rid.c_str();

        // Presentation → theme relationship
        pres_rels.add_relationship(
            opc::rel_types::kTheme, "theme/theme1.xml");

        int64_t slide_id = 256;

        for (std::size_t i = 0; i < slides_.size(); ++i) {
            int num = static_cast<int>(i) + 1;
            std::string slide_part_name =
                "ppt/slides/slide" + std::to_string(num) + ".xml";

            // Create minimal slide XML.
            pugi::xml_document slide_doc;
            auto sd = slide_doc.append_child(pugi::node_declaration);
            sd.append_attribute("version") = "1.0";
            sd.append_attribute("encoding") = "UTF-8";
            sd.append_attribute("standalone") = "yes";

            auto sld = slide_doc.append_child("p:sld");
            sld.append_attribute("xmlns:a") =
                std::string(pptx::ns_uri::kA).c_str();
            sld.append_attribute("xmlns:r") =
                std::string(pptx::ns_uri::kR).c_str();
            sld.append_attribute("xmlns:p") =
                std::string(pptx::ns_uri::kP).c_str();

            // Persist hidden flag: show="0" means hidden.
            if (slides_[i].hidden()) {
                sld.append_attribute("show") = "0";
            }

            auto cSld = sld.append_child("p:cSld");

            // Persist slide name on <p:cSld name="...">.
            if (!slides_[i].name().empty()) {
                cSld.append_attribute("name") = slides_[i].name().c_str();
            }
            auto spTree = cSld.append_child("p:spTree");
            auto nvGrpSpPr = spTree.append_child("p:nvGrpSpPr");
            auto cNvPr = nvGrpSpPr.append_child("p:cNvPr");
            cNvPr.append_attribute("id") = "1";
            cNvPr.append_attribute("name") = "";
            nvGrpSpPr.append_child("p:cNvGrpSpPr");
            nvGrpSpPr.append_child("p:nvPr");
            spTree.append_child("p:grpSpPr");

            // Serialize in-memory shapes into the spTree.
            auto& shapes = slides_[i].shapes();
            // Assign shape IDs (starting from 2; 1 is the group).
            int sid = 2;
            if (shapes.size() > 0) {
                std::unordered_map<const Shape*, int> id_map;
                for (std::size_t s = 0; s < shapes.size(); ++s) {
                    id_map[&shapes[s]] = sid++;
                }

                sid = 2;
                for (std::size_t s = 0; s < shapes.size(); ++s) {
                    auto& shape = shapes[s];
                    int cur_id = sid++;

                    if (auto* conn = dynamic_cast<Connector*>(&shape)) {
                        auto node = spTree.append_child("p:cxnSp");
                        shapes.build_connector_xml(
                            node, cur_id,
                            shape.name().empty()
                                ? "Connector " + std::to_string(cur_id)
                                : shape.name(),
                            shape.shape_type(),
                            shape.x(), shape.y(),
                            shape.width(), shape.height(), true);

                        // Override default adjustments with actual values.
                        if (conn->adjustments().size() > 0) {
                            auto av_lst = node.child("p:spPr")
                                              .child("a:prstGeom")
                                              .child("a:avLst");
                            if (av_lst) {
                                while (av_lst.first_child())
                                    av_lst.remove_child(av_lst.first_child());
                                for (std::size_t a = 0;
                                     a < conn->adjustments().size(); ++a) {
                                    auto& adj = conn->adjustments()[a];
                                    auto gd = av_lst.append_child("a:gd");
                                    gd.append_attribute("name") =
                                        adj.name().c_str();
                                    auto fmla = "val " +
                                        std::to_string(adj.raw_value());
                                    gd.append_attribute("fmla") = fmla.c_str();
                                }
                            }
                        }

                        // Write connection references.
                        auto cNvCxnSpPr = node.child("p:nvCxnSpPr")
                                              .child("p:cNvCxnSpPr");
                        if (cNvCxnSpPr) {
                            if (conn->start_shape_connected_to()) {
                                auto it = id_map.find(
                                    conn->start_shape_connected_to());
                                if (it != id_map.end()) {
                                    auto st = cNvCxnSpPr.append_child("a:stCxn");
                                    st.append_attribute("id") =
                                        std::to_string(it->second).c_str();
                                    st.append_attribute("idx") =
                                        std::to_string(
                                            conn->start_shape_connection_site_index())
                                            .c_str();
                                }
                            }
                            if (conn->end_shape_connected_to()) {
                                auto it = id_map.find(
                                    conn->end_shape_connected_to());
                                if (it != id_map.end()) {
                                    auto en = cNvCxnSpPr.append_child("a:endCxn");
                                    en.append_attribute("id") =
                                        std::to_string(it->second).c_str();
                                    en.append_attribute("idx") =
                                        std::to_string(
                                            conn->end_shape_connection_site_index())
                                            .c_str();
                                }
                            }
                        }
                    } else {
                        auto node = spTree.append_child("p:sp");
                        shapes.build_auto_shape_xml(
                            node, cur_id,
                            shape.name().empty()
                                ? "Shape " + std::to_string(cur_id)
                                : shape.name(),
                            shape.shape_type(),
                            shape.x(), shape.y(),
                            shape.width(), shape.height(), true);

                        // Serialize text frame content into the p:txBody.
                        if (auto* ashape = dynamic_cast<AutoShape*>(&shape)) {
                            auto* tf = ashape->text_frame();
                            if (tf && !tf->text().empty()) {
                                // Mark shape as text box.
                                auto nvSpPr = node.child("p:nvSpPr");
                                if (nvSpPr) {
                                    auto cNvSpPr = nvSpPr.child("p:cNvSpPr");
                                    if (cNvSpPr)
                                        cNvSpPr.append_attribute("txBox") = "1";
                                }

                                auto txbody = node.child("p:txBody");
                                if (txbody) {
                                    // Remove the default empty <a:p>.
                                    std::vector<pugi::xml_node> old_paras;
                                    for (auto ch = txbody.first_child(); ch;
                                         ch = ch.next_sibling()) {
                                        if (std::string_view(ch.name()) == "a:p") {
                                            old_paras.push_back(ch);
                                        }
                                    }
                                    for (auto& n : old_paras) txbody.remove_child(n);

                                    // Write paragraphs from the TextFrame.
                                    auto& paras = tf->paragraphs();
                                    for (std::size_t pi = 0; pi < paras.size();
                                         ++pi) {
                                        auto a_p = txbody.append_child("a:p");

                                        // Paragraph properties (alignment, etc.).
                                        // Default to center if not explicitly set
                                        // (matches .NET AddTextFrame behavior).
                                        auto& pf = paras[pi].paragraph_format();
                                        {
                                            auto pPr = a_p.append_child("a:pPr");
                                            auto actual_align = pf.alignment();
                                            if (actual_align == TextAlignment::NOT_DEFINED)
                                                actual_align = TextAlignment::CENTER;
                                            auto algn = alignment_to_ooxml_str(actual_align);
                                            if (algn) pPr.append_attribute("algn") = algn;
                                        }

                                        // Write individual portions with formatting.
                                        auto& portions = paras[pi].portions();
                                        for (std::size_t qi = 0; qi < portions.size(); ++qi) {
                                            auto& portion = portions[qi];
                                            if (portion.text().empty()) continue;
                                            auto a_r = a_p.append_child("a:r");

                                            // Serialize run properties if any are set.
                                            auto& pfmt = portion.portion_format();
                                            if (has_rpr_properties(pfmt)) {
                                                auto rpr = a_r.append_child("a:rPr");
                                                serialize_rpr(rpr, pfmt);
                                            }

                                            auto a_t = a_r.append_child("a:t");
                                            a_t.text().set(portion.text().c_str());
                                        }

                                        a_p.append_child("a:endParaRPr");
                                    }
                                }
                            }
                        }

                        // Write rotation if non-zero.
                        if (shape.rotation() != 0.0) {
                            auto xfrm = node.child("p:spPr").child("a:xfrm");
                            if (xfrm) {
                                auto rot_val = std::to_string(
                                    static_cast<int>(std::round(
                                        shape.rotation() * pptx::kRotationUnit)));
                                if (xfrm.attribute("rot")) {
                                    xfrm.attribute("rot").set_value(rot_val.c_str());
                                } else {
                                    xfrm.append_attribute("rot") = rot_val.c_str();
                                }
                            }
                        }

                        auto new_sp_pr = node.child("p:spPr");
                        if (new_sp_pr) {
                            // Serialize fill format from in-memory FillFormat.
                            if (shape.fill_format().fill_type() != FillType::NOT_DEFINED) {
                                shape.fill_format().serialize_to_xml(new_sp_pr);

                                // Handle picture fill image embedding.
                                if (shape.fill_format().fill_type() == FillType::PICTURE) {
                                    auto* img_ptr = shape.fill_format()
                                        .picture_fill_format().picture().image();
                                    if (img_ptr) {
                                        auto* pp_img = dynamic_cast<PPImage*>(img_ptr);
                                        if (pp_img) {
                                            // Assign part name if not set.
                                            if (pp_img->part_name().empty()) {
                                                auto ext = image_utils::guess_extension(
                                                    pp_img->raw_data());
                                                auto part_name = "ppt/media/image" +
                                                    std::to_string(img_counter++) +
                                                    "." + ext;
                                                pp_img->set_part_name(part_name);
                                            }
                                            // Write image data to package.
                                            auto data = pp_img->binary_data();
                                            pkg->set_part(pp_img->part_name(), data);

                                            // Add content type for image.
                                            opc::ContentTypesManager img_ct(*pkg);
                                            img_ct.add_default(
                                                image_utils::guess_extension(
                                                    pp_img->raw_data()),
                                                pp_img->content_type());
                                            img_ct.save();

                                            // Create relationship from slide to image.
                                            opc::RelationshipsManager slide_rels(
                                                *pkg, slide_part_name);
                                            auto img_target =
                                                "../media/" + pp_img->part_name().substr(
                                                    pp_img->part_name().rfind('/') + 1);
                                            auto img_rid =
                                                slide_rels.add_relationship(
                                                    opc::rel_types::kImage,
                                                    img_target);
                                            slide_rels.save();

                                            // Set r:embed on a:blip.
                                            auto blip_fill =
                                                new_sp_pr.child("a:blipFill");
                                            if (blip_fill) {
                                                auto blip =
                                                    blip_fill.child("a:blip");
                                                if (blip) {
                                                    blip.append_attribute("r:embed") =
                                                        img_rid.c_str();
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            // Serialize line format from in-memory LineFormat.
                            shape.line_format().serialize_to_xml(new_sp_pr);

                            // Serialize effects from in-memory EffectFormat.
                            if (!shape.effect_format().is_no_effects()) {
                                shape.effect_format().serialize_to_xml(new_sp_pr);
                            }

                            // Serialize 3D formatting from in-memory ThreeDFormat.
                            if (shape.three_d_format().has_data()) {
                                shape.three_d_format().serialize_to_xml(new_sp_pr);
                            }
                        }
                    }
                }
            }

            // Serialize in-memory tables into the spTree.
            for (std::size_t t = 0; t < shapes.table_count(); ++t) {
                auto& tbl = shapes.table_at(t);
                int tbl_id = sid++;

                auto gf = spTree.append_child("p:graphicFrame");

                // nvGraphicFramePr
                auto nv_gf_pr = gf.append_child("p:nvGraphicFramePr");
                auto c_nv_pr_tbl = nv_gf_pr.append_child("p:cNvPr");
                c_nv_pr_tbl.append_attribute("id") = std::to_string(tbl_id).c_str();
                auto tbl_name = "Table " + std::to_string(tbl_id);
                c_nv_pr_tbl.append_attribute("name") = tbl_name.c_str();
                auto c_nv_gf_pr = nv_gf_pr.append_child("p:cNvGraphicFramePr");
                auto gf_locking = c_nv_gf_pr.append_child("a:graphicFrameLocking");
                gf_locking.append_attribute("noGrp") = "1";
                nv_gf_pr.append_child("p:nvPr");

                // Compute total size
                double total_w = 0;
                for (std::size_t ci = 0; ci < tbl.columns().size(); ++ci)
                    total_w += tbl.columns()[ci].width();
                double total_h = 0;
                for (std::size_t ri = 0; ri < tbl.rows().size(); ++ri)
                    total_h += tbl.rows()[ri].height();

                // p:xfrm with table position
                auto xfrm = gf.append_child("p:xfrm");
                auto off = xfrm.append_child("a:off");
                off.append_attribute("x") = to_emu_str(tbl.offset_x_).c_str();
                off.append_attribute("y") = to_emu_str(tbl.offset_y_).c_str();
                auto ext = xfrm.append_child("a:ext");
                ext.append_attribute("cx") = to_emu_str(total_w).c_str();
                ext.append_attribute("cy") = to_emu_str(total_h).c_str();

                // a:graphic > a:graphicData > a:tbl
                auto graphic = gf.append_child("a:graphic");
                auto graphic_data = graphic.append_child("a:graphicData");
                graphic_data.append_attribute("uri") =
                    std::string(pptx_const::Elements::kTableUri).c_str();

                auto a_tbl = graphic_data.append_child("a:tbl");

                // a:tblPr
                auto tbl_pr = a_tbl.append_child("a:tblPr");
                if (tbl.first_row()) tbl_pr.append_attribute("firstRow") = "1";
                if (tbl.first_col()) tbl_pr.append_attribute("firstCol") = "1";
                if (tbl.last_row()) tbl_pr.append_attribute("lastRow") = "1";
                if (tbl.last_col()) tbl_pr.append_attribute("lastCol") = "1";
                if (tbl.horizontal_banding()) tbl_pr.append_attribute("bandRow") = "1";
                if (tbl.vertical_banding()) tbl_pr.append_attribute("bandCol") = "1";
                auto tbl_style_id = tbl_pr.append_child("a:tableStyleId");
                tbl_style_id.text().set("{5C22544A-7EE6-4342-B048-85BDC9FD1C3A}");

                // a:tblGrid
                auto tbl_grid = a_tbl.append_child("a:tblGrid");
                for (std::size_t ci = 0; ci < tbl.columns().size(); ++ci) {
                    auto grid_col = tbl_grid.append_child("a:gridCol");
                    grid_col.append_attribute("w") =
                        to_emu_str(tbl.columns()[ci].width()).c_str();
                }

                // Rows and cells
                for (std::size_t ri = 0; ri < tbl.rows().size(); ++ri) {
                    auto& row = tbl.rows()[ri];
                    auto tr = a_tbl.append_child("a:tr");
                    tr.append_attribute("h") = to_emu_str(row.height()).c_str();

                    for (std::size_t ci = 0; ci < row.size(); ++ci) {
                        auto& cell = row[ci];
                        auto tc = tr.append_child("a:tc");

                        // Write merge attributes
                        if (cell.col_span() > 1)
                            tc.append_attribute("gridSpan") =
                                std::to_string(cell.col_span()).c_str();
                        if (cell.row_span() > 1)
                            tc.append_attribute("rowSpan") =
                                std::to_string(cell.row_span()).c_str();
                        if (cell.h_merge())
                            tc.append_attribute("hMerge") = "1";
                        if (cell.v_merge())
                            tc.append_attribute("vMerge") = "1";

                        // txBody with cell text and paragraph formatting
                        auto txbody = tc.append_child("a:txBody");
                        txbody.append_child("a:bodyPr");
                        txbody.append_child("a:lstStyle");
                        if (cell.text_frame() &&
                            !cell.text_frame()->text().empty()) {
                            auto& paras = cell.text_frame()->paragraphs();
                            for (std::size_t pi = 0; pi < paras.size(); ++pi) {
                                auto p_el = txbody.append_child("a:p");
                                auto& pf = paras[pi].paragraph_format();
                                if (pf.alignment() != TextAlignment::NOT_DEFINED) {
                                    auto pPr = p_el.append_child("a:pPr");
                                    auto algn = alignment_to_ooxml_str(pf.alignment());
                                    if (algn) pPr.append_attribute("algn") = algn;
                                }
                                auto r_el = p_el.append_child("a:r");
                                auto t_el = r_el.append_child("a:t");
                                t_el.text().set(paras[pi].text().c_str());
                            }
                        } else {
                            auto p_el = txbody.append_child("a:p");
                            p_el.append_child("a:endParaRPr");
                        }

                        // tcPr with anchor, margins, borders, and fill
                        auto tc_pr = tc.append_child("a:tcPr");

                        // Cell text anchor type
                        if (cell.text_anchor_type() != TextAnchorType::NOT_DEFINED) {
                            const char* anc = nullptr;
                            switch (cell.text_anchor_type()) {
                                case TextAnchorType::TOP:         anc = "t"; break;
                                case TextAnchorType::CENTER:      anc = "ctr"; break;
                                case TextAnchorType::BOTTOM:      anc = "b"; break;
                                case TextAnchorType::JUSTIFIED:   anc = "just"; break;
                                case TextAnchorType::DISTRIBUTED: anc = "dist"; break;
                                default: break;
                            }
                            if (anc) tc_pr.append_attribute("anchor") = anc;
                        }

                        // Cell margins
                        if (cell.margin_left() != 0)
                            tc_pr.append_attribute("marL") =
                                to_emu_str(cell.margin_left()).c_str();
                        if (cell.margin_right() != 0)
                            tc_pr.append_attribute("marR") =
                                to_emu_str(cell.margin_right()).c_str();
                        if (cell.margin_top() != 0)
                            tc_pr.append_attribute("marT") =
                                to_emu_str(cell.margin_top()).c_str();
                        if (cell.margin_bottom() != 0)
                            tc_pr.append_attribute("marB") =
                                to_emu_str(cell.margin_bottom()).c_str();

                        auto& cf = cell.cell_format();

                        // Serialize borders
                        auto write_border = [&](const char* tag_name,
                                                const LineFormat& lf) {
                            if (lf.fill_format().fill_type() !=
                                    FillType::NOT_DEFINED ||
                                lf.width() != 0) {
                                auto ln = tc_pr.append_child(tag_name);
                                if (lf.width() != 0) {
                                    ln.append_attribute("w") =
                                        to_emu_str(lf.width()).c_str();
                                }
                                if (lf.fill_format().fill_type() ==
                                    FillType::SOLID) {
                                    auto sf = ln.append_child("a:solidFill");
                                    auto srgb = sf.append_child("a:srgbClr");
                                    char hex[8];
                                    snprintf(
                                        hex, sizeof(hex), "%02X%02X%02X",
                                        lf.fill_format()
                                            .solid_fill_color()
                                            .color()
                                            .r(),
                                        lf.fill_format()
                                            .solid_fill_color()
                                            .color()
                                            .g(),
                                        lf.fill_format()
                                            .solid_fill_color()
                                            .color()
                                            .b());
                                    srgb.append_attribute("val") = hex;
                                }
                            }
                        };
                        write_border("a:lnL", cf.border_left());
                        write_border("a:lnR", cf.border_right());
                        write_border("a:lnT", cf.border_top());
                        write_border("a:lnB", cf.border_bottom());

                        // Serialize cell fill
                        if (cf.fill_format().fill_type() == FillType::SOLID) {
                            auto sf = tc_pr.append_child("a:solidFill");
                            auto srgb = sf.append_child("a:srgbClr");
                            char hex[8];
                            snprintf(hex, sizeof(hex), "%02X%02X%02X",
                                     cf.fill_format().solid_fill_color().color().r(),
                                     cf.fill_format().solid_fill_color().color().g(),
                                     cf.fill_format().solid_fill_color().color().b());
                            srgb.append_attribute("val") = hex;
                        } else if (cf.fill_format().fill_type() == FillType::NO_FILL) {
                            tc_pr.append_child("a:noFill");
                        }
                    }
                }
            }

            pkg->set_part(slide_part_name, serialize_xml(slide_doc));

            // Content type for slide.
            opc::ContentTypesManager ct(*pkg);
            ct.add_override(slide_part_name, opc::content_types::kSlide);
            ct.save();

            // Slide → slide-layout relationship.
            {
                opc::RelationshipsManager slide_rels(*pkg, slide_part_name);
                slide_rels.add_relationship(
                    opc::rel_types::kSlideLayout,
                    "../slideLayouts/slideLayout1.xml");
                slide_rels.save();
            }

            // Relationship from presentation to slide.
            std::string rel_target =
                "slides/slide" + std::to_string(num) + ".xml";
            auto rid = pres_rels.add_relationship(
                opc::rel_types::kSlide, rel_target);

            // sldId entry.
            auto sld_id_node = sld_id_lst.append_child("p:sldId");
            sld_id_node.append_attribute("id") =
                std::to_string(slide_id++).c_str();
            sld_id_node.append_attribute("r:id") = rid.c_str();

            // --- Serialize notes slide (if present) ---
            auto* notes_ptr = slides_[i].notes_slide_manager().notes_slide();
            if (notes_ptr) {
                auto* notes_slide = dynamic_cast<NotesSlide*>(notes_ptr);
                if (notes_slide) {
                    // Create notes slide part in the package.
                    auto notes_part = pptx::NotesSlidePart::create_empty(
                        *pkg, slide_part_name);

                    // Set the notes text on the body placeholder.
                    auto notes_text = notes_slide->notes_text_frame().text();
                    if (!notes_text.empty()) {
                        notes_part.set_placeholder_text("body", notes_text);
                    }

                    // Copy placeholder state from the in-memory NotesSlidePart.
                    // Check each placeholder type used by the header/footer manager.
                    auto& hfm = notes_slide->header_footer_manager();
                    if (hfm.is_footer_visible()) {
                        notes_part.add_placeholder("ftr");
                    }
                    if (hfm.is_slide_number_visible()) {
                        notes_part.add_placeholder("sldNum");
                    }
                    if (hfm.is_date_time_visible()) {
                        notes_part.add_placeholder("dt");
                    }
                    if (hfm.is_header_visible()) {
                        notes_part.add_placeholder("hdr");
                    }

                    notes_part.save();

                    // Add relationship from slide to notes slide.
                    opc::RelationshipsManager slide_rels(*pkg, slide_part_name);
                    auto notes_rel_target = pptx::NotesSlidePart::compute_relative_target(
                        slide_part_name, notes_part.part_name());
                    slide_rels.add_relationship(
                        opc::rel_types::kNotesSlide, notes_rel_target);
                    slide_rels.save();
                }
            }
        }

        // Required slide-size and notes-size elements (OOXML spec §19.2.1.35, §19.2.1.26).
        auto sld_sz = pres_node.append_child("p:sldSz");
        sld_sz.append_attribute("cx") = "9144000";
        sld_sz.append_attribute("cy") = "6858000";
        sld_sz.append_attribute("type") = "screen4x3";

        auto notes_sz = pres_node.append_child("p:notesSz");
        notes_sz.append_attribute("cx") = "6858000";
        notes_sz.append_attribute("cy") = "9144000";

        pres_rels.save();
        pkg->set_part(pres_part, serialize_xml(doc));

        // Content type for presentation + default extensions.
        opc::ContentTypesManager ct(*pkg);
        ct.add_default("rels",
            "application/vnd.openxmlformats-package.relationships+xml");
        ct.add_default("xml", "application/xml");
        ct.add_override(pres_part, opc::content_types::kPresentation);
        ct.save();

        // Root relationships: presentation + docProps.
        opc::RelationshipsManager root_rels(*pkg, "");
        root_rels.add_relationship(opc::rel_types::kOfficeDocument, pres_part);
        root_rels.add_relationship(
            opc::rel_types::kCoreProperties, "docProps/core.xml");
        root_rels.add_relationship(
            opc::rel_types::kExtendedProperties, "docProps/app.xml");
        root_rels.save();

        // Content types for docProps.
        {
            opc::ContentTypesManager ct_dp(*pkg);
            ct_dp.add_override("docProps/core.xml",
                               opc::content_types::kCoreProperties);
            ct_dp.add_override("docProps/app.xml",
                               opc::content_types::kExtendedProperties);
            ct_dp.save();
        }
    }

    // --- Serialize comment authors ---
    if (comment_authors_.size() > 0) {
        pptx::CommentAuthorsPart authors_part(*pkg);

        // Map from in-memory author index to XML author ID.
        std::vector<int32_t> author_ids;
        for (std::size_t a = 0; a < comment_authors_.size(); ++a) {
            auto& ca = comment_authors_[a];
            if (ca.has_internal_data()) {
                author_ids.push_back(ca.internal_data()->id());
            } else {
                auto data = authors_part.add_author(ca.name(), ca.initials());
                author_ids.push_back(data.id());
            }
        }
        authors_part.save();

        // Register content type and relationship for comment authors.
        pptx::CommentAuthorsPart::ensure_registered(*pkg, pres_part);

        // --- Serialize comments per slide ---
        for (std::size_t si = 0; si < slides_.size(); ++si) {
            auto& slide = slides_[si];
            int slide_num = static_cast<int>(si) + 1;
            std::string slide_part_name =
                "ppt/slides/slide" + std::to_string(slide_num) + ".xml";

            // Collect all comments for this slide.
            bool has_comments = false;
            for (std::size_t a = 0; a < comment_authors_.size(); ++a) {
                auto& ca = comment_authors_[a];
                for (std::size_t c = 0; c < ca.comments().size(); ++c) {
                    if (ca.comments()[c].slide() == &slide) {
                        has_comments = true;
                        break;
                    }
                }
                if (has_comments) break;
            }

            if (!has_comments) continue;

            // Create or load the comments part for this slide.
            opc::RelationshipsManager slide_rels(*pkg, slide_part_name);
            auto comments_part = pptx::CommentsPart::create_for_slide(
                *pkg, slide_part_name, &slide_rels);
            slide_rels.save();

            // Add each comment for this slide.
            for (std::size_t a = 0; a < comment_authors_.size(); ++a) {
                auto& ca = comment_authors_[a];
                int32_t aid = author_ids[a];
                for (std::size_t c = 0; c < ca.comments().size(); ++c) {
                    auto& comment = ca.comments()[c];
                    if (comment.slide() != &slide) continue;

                    auto idx = authors_part.next_comment_idx(aid);
                    auto dt_str = pptx::dt_to_str(comment.created_time());
                    comments_part.add_comment(
                        aid, idx,
                        comment.text(),
                        static_cast<double>(comment.position().x),
                        static_cast<double>(comment.position().y),
                        dt_str);
                }
            }

            authors_part.save();
            comments_part.save();
        }
    }

    // --- Serialize document properties ---
    if (!document_properties_.package_) {
        document_properties_.package_ = pkg;
    }
    document_properties_.save_to_package();

    // --- Write the ZIP file to disk ---
    pkg->save(std::filesystem::path(std::string(path)));
}

void Presentation::dispose() {
    if (disposed_) return;
    disposed_ = true;

    master_slides_map_.reset();
    layout_slides_map_.reset();
    owned_layout_slides_.clear();
    owned_master_slides_.clear();
    opc_package_ = nullptr;
}

// ---------------------------------------------------------------------------
// detect_source_format
// ---------------------------------------------------------------------------

void Presentation::detect_source_format(std::string_view path) {
    // Convert to lowercase for case-insensitive matching.
    std::string lower(path);
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    if (lower.ends_with(".pptx") || lower.ends_with(".pptm") ||
        lower.ends_with(".ppsx") || lower.ends_with(".potx")) {
        source_format_ = SourceFormat::PPTX;
    } else if (lower.ends_with(".ppt")) {
        source_format_ = SourceFormat::PPT;
    } else if (lower.ends_with(".odp")) {
        source_format_ = SourceFormat::ODP;
    }
}

// ---------------------------------------------------------------------------
// ensure_layout_slides_parsed
// ---------------------------------------------------------------------------

void Presentation::ensure_layout_slides_parsed() {
    // Already parsed — nothing to do.
    if (layout_slides_map_) return;

    // No OPC package bound — nothing to parse (e.g. default-constructed presentation).
    if (!opc_package_) {
        layout_slides_map_ = std::make_unique<
            std::unordered_map<std::string, LayoutSlide*>>();
        master_slides_map_ = std::make_unique<
            std::unordered_map<std::string, MasterSlide*>>();
        return;
    }

    master_slides_map_ = std::make_unique<
        std::unordered_map<std::string, MasterSlide*>>();
    layout_slides_map_ = std::make_unique<
        std::unordered_map<std::string, LayoutSlide*>>();

    // Resolve presentation-level relationships.
    Internal::opc::RelationshipsManager pres_rels(
        *opc_package_, presentation_part_name_);

    // Iterate master references from the MasterSlideCollection.
    for (std::size_t mi = 0; mi < masters_.size(); ++mi) {
        // Nothing to do here — masters are already loaded by their collection.
        // But we need the relationship data to find master part names.
    }

    // Find all slide master relationships from the presentation.
    auto master_rels = pres_rels.get_relationships_by_type(
        Internal::opc::rel_types::kSlideMaster);

    for (const auto& master_rel : master_rels) {
        // Resolve the master part name.
        std::string master_part_name;
        if (!master_rel.target.empty() && master_rel.target.front() == '/') {
            master_part_name = master_rel.target.substr(1);
        } else {
            // Relative to presentation directory.
            auto slash_pos = presentation_part_name_.rfind('/');
            if (slash_pos != std::string::npos) {
                master_part_name = presentation_part_name_.substr(0, slash_pos + 1)
                    + master_rel.target;
            } else {
                master_part_name = master_rel.target;
            }
        }

        // Parse the master slide part.
        Internal::pptx::MasterSlidePart master_part(*opc_package_, master_part_name);

        // Parse layout slides for this master.
        std::vector<ILayoutSlide*> master_layouts;
        for (const auto& layout_part_name : master_part.layout_part_names()) {
            // Skip if already parsed (shared layouts).
            if (layout_slides_map_->contains(layout_part_name)) {
                master_layouts.push_back((*layout_slides_map_)[layout_part_name]);
                continue;
            }

            Internal::pptx::LayoutSlidePart layout_part(
                *opc_package_, layout_part_name);

            auto layout = std::make_unique<LayoutSlide>(this);
            layout->set_name(layout_part.name());
            // Master slide will be set after all masters are created.

            auto* layout_ptr = layout.get();
            (*layout_slides_map_)[layout_part_name] = layout_ptr;
            master_layouts.push_back(layout_ptr);
            owned_layout_slides_.push_back(std::move(layout));
        }

        // Create master slide object.
        auto master = std::make_unique<MasterSlide>();
        master->set_name(master_part.name());
        master->layout_slides().init_internal(master_layouts);

        auto* master_ptr = master.get();
        (*master_slides_map_)[master_part_name] = master_ptr;
        owned_master_slides_.push_back(std::move(master));
    }

    // Second pass: resolve master slide references for layout slides.
    if (opc_package_) {
        for (const auto& [layout_part_name, layout_ptr] : *layout_slides_map_) {
            Internal::pptx::LayoutSlidePart layout_part(
                *opc_package_, layout_part_name);
            auto master_name = layout_part.master_part_name();
            if (!master_name.empty()) {
                auto it = master_slides_map_->find(master_name);
                if (it != master_slides_map_->end()) {
                    layout_ptr->set_master_slide(it->second);
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// resolve_layout_slide / resolve_master_slide
// ---------------------------------------------------------------------------

LayoutSlide* Presentation::resolve_layout_slide(std::string_view part_name) {
    ensure_layout_slides_parsed();
    auto it = layout_slides_map_->find(std::string(part_name));
    if (it != layout_slides_map_->end()) return it->second;
    return nullptr;
}

MasterSlide* Presentation::resolve_master_slide(std::string_view part_name) {
    ensure_layout_slides_parsed();
    auto it = master_slides_map_->find(std::string(part_name));
    if (it != master_slides_map_->end()) return it->second;
    return nullptr;
}

} // namespace Aspose::Slides::Foss
