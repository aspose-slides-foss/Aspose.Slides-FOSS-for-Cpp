// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/notes_slide_part.h>

namespace pptx = Aspose::Slides::Foss::Internal::pptx;
namespace opc = Aspose::Slides::Foss::Internal::opc;

// Minimal valid notesSlide XML for testing.
static const std::string kSampleNotesXml = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<p:notes xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main"
         xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"
         xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main">
  <p:cSld name="TestNotes">
    <p:spTree>
      <p:nvGrpSpPr>
        <p:cNvPr id="1" name=""/>
        <p:cNvGrpSpPr/>
        <p:nvPr/>
      </p:nvGrpSpPr>
      <p:sp>
        <p:nvSpPr>
          <p:cNvPr id="2" name="Slide Image Placeholder 1"/>
          <p:cNvSpPr><a:spLocks noGrp="1"/></p:cNvSpPr>
          <p:nvPr><p:ph type="sldImg"/></p:nvPr>
        </p:nvSpPr>
        <p:spPr/>
      </p:sp>
      <p:sp>
        <p:nvSpPr>
          <p:cNvPr id="3" name="Notes Placeholder 2"/>
          <p:cNvSpPr><a:spLocks noGrp="1"/></p:cNvSpPr>
          <p:nvPr><p:ph type="body" idx="1"/></p:nvPr>
        </p:nvSpPr>
        <p:spPr/>
        <p:txBody>
          <a:bodyPr/>
          <a:lstStyle/>
          <a:p><a:r><a:t>Hello notes</a:t></a:r></a:p>
        </p:txBody>
      </p:sp>
    </p:spTree>
  </p:cSld>
</p:notes>)";

static const std::string kNotesXmlNoCsld = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<p:notes xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main">
</p:notes>)";

static const std::string kNotesXmlWithFooter = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<p:notes xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main"
         xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main">
  <p:cSld>
    <p:spTree>
      <p:nvGrpSpPr>
        <p:cNvPr id="1" name=""/>
        <p:cNvGrpSpPr/>
        <p:nvPr/>
      </p:nvGrpSpPr>
      <p:sp>
        <p:nvSpPr>
          <p:cNvPr id="2" name="Body"/>
          <p:cNvSpPr/>
          <p:nvPr><p:ph type="body"/></p:nvPr>
        </p:nvSpPr>
        <p:spPr/>
        <p:txBody>
          <a:bodyPr/>
          <a:lstStyle/>
          <a:p><a:endParaRPr/></a:p>
        </p:txBody>
      </p:sp>
      <p:sp>
        <p:nvSpPr>
          <p:cNvPr id="3" name="Footer"/>
          <p:cNvSpPr/>
          <p:nvPr><p:ph type="ftr"/></p:nvPr>
        </p:nvSpPr>
        <p:spPr/>
        <p:txBody>
          <a:bodyPr/>
          <a:lstStyle/>
          <a:p><a:r><a:t>My Footer</a:t></a:r></a:p>
        </p:txBody>
      </p:sp>
    </p:spTree>
  </p:cSld>
</p:notes>)";

class NotesSlidePartTest : public ::testing::Test {
protected:
    opc::InMemoryOpcPackage package_ = opc::InMemoryOpcPackage::create_new();

    void set_notes_xml(const std::string& part_name, const std::string& xml) {
        package_.set_part(part_name, xml);
    }
};

// ---------------------------------------------------------------------------
// Construction tests
// ---------------------------------------------------------------------------

TEST_F(NotesSlidePartTest, ConstructFromValidPart) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_EQ(part.part_name(), "ppt/notesSlides/notesSlide1.xml");
}

TEST_F(NotesSlidePartTest, ThrowsWhenPartNotFound) {
    EXPECT_THROW(
        pptx::NotesSlidePart(package_, "ppt/notesSlides/missing.xml"),
        std::runtime_error);
}

// ---------------------------------------------------------------------------
// Name property tests
// ---------------------------------------------------------------------------

TEST_F(NotesSlidePartTest, GetName) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_EQ(part.name(), "TestNotes");
}

TEST_F(NotesSlidePartTest, GetNameWhenNoCsld) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kNotesXmlNoCsld);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_EQ(part.name(), "");
}

TEST_F(NotesSlidePartTest, SetName) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.set_name("NewNotesName");
    EXPECT_EQ(part.name(), "NewNotesName");
}

// ---------------------------------------------------------------------------
// Placeholder tests
// ---------------------------------------------------------------------------

TEST_F(NotesSlidePartTest, HasPlaceholderBody) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_TRUE(part.has_placeholder("body"));
    EXPECT_TRUE(part.has_placeholder("sldImg"));
    EXPECT_FALSE(part.has_placeholder("ftr"));
}

TEST_F(NotesSlidePartTest, GetNotesTxbody) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    auto txbody = part.get_notes_txbody();
    EXPECT_FALSE(txbody.empty());
    // Check it has the expected text
    auto a_p = txbody.child("a:p");
    EXPECT_FALSE(a_p.empty());
    auto a_r = a_p.child("a:r");
    EXPECT_FALSE(a_r.empty());
    auto a_t = a_r.child("a:t");
    EXPECT_STREQ(a_t.text().as_string(), "Hello notes");
}

TEST_F(NotesSlidePartTest, GetNotesTxbodyWhenNoBody) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kNotesXmlNoCsld);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_TRUE(part.get_notes_txbody().empty());
}

TEST_F(NotesSlidePartTest, RemovePlaceholder) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kNotesXmlWithFooter);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_TRUE(part.has_placeholder("ftr"));
    part.remove_placeholder("ftr");
    EXPECT_FALSE(part.has_placeholder("ftr"));
    // Body should still be there
    EXPECT_TRUE(part.has_placeholder("body"));
}

TEST_F(NotesSlidePartTest, RemoveNonExistentPlaceholderIsNoop) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.remove_placeholder("hdr"); // doesn't exist, should not throw
    EXPECT_TRUE(part.has_placeholder("body"));
}

TEST_F(NotesSlidePartTest, AddPlaceholder) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_FALSE(part.has_placeholder("hdr"));
    part.add_placeholder("hdr");
    EXPECT_TRUE(part.has_placeholder("hdr"));
}

TEST_F(NotesSlidePartTest, AddPlaceholderAlreadyExistsIsNoop) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.add_placeholder("body"); // already exists
    EXPECT_TRUE(part.has_placeholder("body"));
}

TEST_F(NotesSlidePartTest, AddTextPlaceholderHasTxBody) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.add_placeholder("ftr");
    // Save and reload to verify structure
    part.save();
    pptx::NotesSlidePart reloaded(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_TRUE(reloaded.has_placeholder("ftr"));
}

TEST_F(NotesSlidePartTest, AddNonTextPlaceholderHasNoTxBody) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.add_placeholder("sldNum");
    // sldNum is not text-bearing, so no txBody initially
    EXPECT_TRUE(part.has_placeholder("sldNum"));
}

// ---------------------------------------------------------------------------
// Set placeholder text tests
// ---------------------------------------------------------------------------

TEST_F(NotesSlidePartTest, SetPlaceholderTextOnExisting) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.set_placeholder_text("body", "Updated notes text");

    auto txbody = part.get_notes_txbody();
    EXPECT_FALSE(txbody.empty());
    auto a_p = txbody.child("a:p");
    auto a_r = a_p.child("a:r");
    auto a_t = a_r.child("a:t");
    EXPECT_STREQ(a_t.text().as_string(), "Updated notes text");
}

TEST_F(NotesSlidePartTest, SetPlaceholderTextCreatesPlaceholder) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_FALSE(part.has_placeholder("hdr"));
    part.set_placeholder_text("hdr", "Header text");
    EXPECT_TRUE(part.has_placeholder("hdr"));
}

TEST_F(NotesSlidePartTest, SetPlaceholderTextEmpty) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.set_placeholder_text("body", "");

    auto txbody = part.get_notes_txbody();
    auto a_p = txbody.child("a:p");
    // Empty text should produce endParaRPr, not a:r
    EXPECT_TRUE(a_p.child("a:endParaRPr"));
    EXPECT_TRUE(a_p.child("a:r").empty());
}

// ---------------------------------------------------------------------------
// Save / round-trip tests
// ---------------------------------------------------------------------------

TEST_F(NotesSlidePartTest, SaveAndReload) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.set_name("SavedNotes");
    part.save();

    pptx::NotesSlidePart reloaded(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_EQ(reloaded.name(), "SavedNotes");
}

TEST_F(NotesSlidePartTest, SavePreservesPlaceholders) {
    set_notes_xml("ppt/notesSlides/notesSlide1.xml", kSampleNotesXml);
    pptx::NotesSlidePart part(package_, "ppt/notesSlides/notesSlide1.xml");
    part.add_placeholder("ftr");
    part.save();

    pptx::NotesSlidePart reloaded(package_, "ppt/notesSlides/notesSlide1.xml");
    EXPECT_TRUE(reloaded.has_placeholder("body"));
    EXPECT_TRUE(reloaded.has_placeholder("sldImg"));
    EXPECT_TRUE(reloaded.has_placeholder("ftr"));
}

// ---------------------------------------------------------------------------
// Static method tests
// ---------------------------------------------------------------------------

TEST_F(NotesSlidePartTest, ComputeRelativeTargetSameDir) {
    auto result = pptx::NotesSlidePart::compute_relative_target(
        "ppt/notesSlides/notesSlide1.xml",
        "ppt/notesSlides/notesSlide2.xml");
    EXPECT_EQ(result, "notesSlide2.xml");
}

TEST_F(NotesSlidePartTest, ComputeRelativeTargetUpAndDown) {
    auto result = pptx::NotesSlidePart::compute_relative_target(
        "ppt/notesSlides/notesSlide1.xml",
        "ppt/slides/slide1.xml");
    EXPECT_EQ(result, "../slides/slide1.xml");
}

TEST_F(NotesSlidePartTest, ComputeRelativeTargetDifferentBranch) {
    auto result = pptx::NotesSlidePart::compute_relative_target(
        "ppt/notesSlides/notesSlide1.xml",
        "ppt/notesMasters/notesMaster1.xml");
    EXPECT_EQ(result, "../notesMasters/notesMaster1.xml");
}

TEST_F(NotesSlidePartTest, FindNotesMasterPresent) {
    package_.set_part("ppt/notesMasters/notesMaster1.xml", "dummy");
    auto result = pptx::NotesSlidePart::find_notes_master(package_);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, "ppt/notesMasters/notesMaster1.xml");
}

TEST_F(NotesSlidePartTest, FindNotesMasterAbsent) {
    auto result = pptx::NotesSlidePart::find_notes_master(package_);
    EXPECT_FALSE(result.has_value());
}

TEST_F(NotesSlidePartTest, BuildNotesXml) {
    auto xml = pptx::NotesSlidePart::build_notes_xml();
    EXPECT_FALSE(xml.empty());

    // Verify it can be parsed
    pugi::xml_document doc;
    auto result = doc.load_buffer(xml.data(), xml.size());
    EXPECT_TRUE(result);

    auto notes = doc.child("p:notes");
    EXPECT_FALSE(notes.empty());

    auto sp_tree = notes.child("p:cSld").child("p:spTree");
    EXPECT_FALSE(sp_tree.empty());

    // Should have sldImg and body placeholders
    int ph_count = 0;
    for (auto sp : sp_tree.children("p:sp")) {
        auto ph = sp.child("p:nvSpPr").child("p:nvPr").child("p:ph");
        if (ph) ++ph_count;
    }
    EXPECT_EQ(ph_count, 2);
}

TEST_F(NotesSlidePartTest, CreateEmpty) {
    // Set up a slide part
    package_.set_part("ppt/slides/slide1.xml", "dummy");

    auto notes = pptx::NotesSlidePart::create_empty(
        package_, "ppt/slides/slide1.xml");

    EXPECT_EQ(notes.part_name(), "ppt/notesSlides/notesSlide1.xml");
    EXPECT_TRUE(notes.has_placeholder("body"));
    EXPECT_TRUE(notes.has_placeholder("sldImg"));

    // Check that content type was registered
    opc::ContentTypesManager ct_manager(package_);
    EXPECT_EQ(ct_manager.get_content_type("ppt/notesSlides/notesSlide1.xml"),
              opc::content_types::kNotesSlide);

    // Check that rels were created with slide relationship
    opc::RelationshipsManager rels(package_, "ppt/notesSlides/notesSlide1.xml");
    auto slide_rels = rels.get_relationships_by_type(opc::rel_types::kSlide);
    EXPECT_EQ(slide_rels.size(), 1u);
    EXPECT_EQ(slide_rels[0].target, "../slides/slide1.xml");
}

TEST_F(NotesSlidePartTest, CreateEmptyWithNotesMaster) {
    package_.set_part("ppt/slides/slide1.xml", "dummy");
    package_.set_part("ppt/notesMasters/notesMaster1.xml", "dummy");

    auto notes = pptx::NotesSlidePart::create_empty(
        package_, "ppt/slides/slide1.xml");

    opc::RelationshipsManager rels(package_, notes.part_name());
    auto master_rels = rels.get_relationships_by_type(opc::rel_types::kNotesMaster);
    EXPECT_EQ(master_rels.size(), 1u);
    EXPECT_EQ(master_rels[0].target, "../notesMasters/notesMaster1.xml");
}

TEST_F(NotesSlidePartTest, CreateEmptyFindsNextNumber) {
    // Pre-create notesSlide1
    auto xml = pptx::NotesSlidePart::build_notes_xml();
    package_.set_part("ppt/notesSlides/notesSlide1.xml", std::move(xml));
    package_.set_part("ppt/slides/slide2.xml", "dummy");

    auto notes = pptx::NotesSlidePart::create_empty(
        package_, "ppt/slides/slide2.xml");

    EXPECT_EQ(notes.part_name(), "ppt/notesSlides/notesSlide2.xml");
}

TEST_F(NotesSlidePartTest, Delete) {
    package_.set_part("ppt/slides/slide1.xml", "dummy");
    auto notes = pptx::NotesSlidePart::create_empty(
        package_, "ppt/slides/slide1.xml");

    auto part_name = notes.part_name();
    EXPECT_TRUE(package_.has_part(part_name));

    pptx::NotesSlidePart::remove(package_, part_name);

    EXPECT_FALSE(package_.has_part(part_name));

    // Content type should be removed
    opc::ContentTypesManager ct_manager(package_);
    EXPECT_EQ(ct_manager.get_content_type(part_name), "");
}
