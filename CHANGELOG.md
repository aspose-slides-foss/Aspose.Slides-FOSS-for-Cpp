# Changelog

All notable changes to this project are documented here.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and the project uses
a CalVer version scheme — `YY.M.PATCH`, matching the other language editions of the library. The
version is the one in `CMakeLists.txt` and is written nowhere else.

The compatibility rule the installed CMake package enforces is `SameMinorVersion`. The major number
is a year and carries no compatibility meaning, so `find_package(AsposeSlidesFoss 26.9 CONFIG
REQUIRED)` accepts any `26.9.x` and rejects `26.10` — the only promise a monthly release train can
keep.

## [26.9.0]

This is the first entry. The library existed before it, but it wrote files that were wrong in ways
its own tests could not see: the writer and the reader shared the misunderstanding, so every getter
returned what its setter was given and the package was still one PowerPoint refused, discarded from,
or opened with the caller's work missing. The work below is what made the produced `.pptx` a package
other software can read, and what made the build produce something a project outside this tree can
consume.

**If you built against an earlier commit, read *Changed* first.** Calls that used to succeed now
throw, one accessor returns something different, and the CMake target has been renamed.

### Changed

- **`save()` refuses the formats it cannot write instead of writing a `.pptx` under the requested
  name.** It writes the six Office Open XML presentation formats — `PPTX`, `PPTM`, `PPSX`, `PPSM`,
  `POTX` and `POTM` — and throws `std::invalid_argument` for every other `SaveFormat` value, with a
  message naming the six that work. Previously `save("report.pdf", SaveFormat::PDF)` returned
  successfully having written a PowerPoint file called `report.pdf`, which PowerPoint then refused to
  open, reporting that the file extension had changed.
- **Each written format declares its own main-part content type.** The six share one package layout
  and differ only there, so a `.potx` is now genuinely a template and a `.ppsx` genuinely a
  slideshow, rather than all six claiming to be a presentation. The macro-enabled three are written
  without a VBA project, since macros are not supported; a macro-enabled package with no
  `vbaProject` part is valid and opens.
- **The file name and the format have to agree.** `save("deck.pptx", SaveFormat::POTX)` writes a
  correct template under a `.pptx` name, and PowerPoint refuses a file whose extension and content
  type disagree. Name the file for the format you asked for.
- **`Shape::get_xfrm()` no longer resolves placeholder inheritance.** It returns this shape's own
  `a:xfrm`, and an empty node when it has none. It previously returned the *inherited* element —
  which lives in a layout or master part shared by every slide that uses it, and must never be handed
  out for mutation. `Shape::get_inherited_xfrm()` is **removed**; `Shape::get_inherited_frame()`
  replaces it and returns a value. `x()`, `y()`, `width()` and `height()` still resolve inheritance
  and are unchanged.
- **`add_picture_frame` throws when the frame has no image behind it**, instead of writing an
  `<a:blip/>` with no `r:embed`. That was schema-valid and showed nothing: a correctly sized,
  correctly positioned shape with no picture in it and no error anywhere.
- **The CMake target is `AsposeSlidesFoss`**, with the alias `AsposeSlidesFoss::AsposeSlidesFoss`,
  and it is what both the build tree and the installed package offer. A project that pulled this one
  in with `add_subdirectory` and linked the old bare `aspose_slides_foss` name must change one line.
  The *library file* is still `libaspose_slides_foss.a` / `aspose_slides_foss.lib`.
- **miniz is a private dependency now.** It appears in no installed header. pugixml stays public,
  because 44 installed headers include `<pugixml.hpp>`; see the README.
- **The library is built as a static archive explicitly**, so `BUILD_SHARED_LIBS=ON` — which package
  managers set globally — no longer produces a shared library that exports no symbols. Nothing in the
  sources is annotated for export.
- **The test suite and its GoogleTest download are behind an option** that defaults off when this
  project is not the one being built. A project that adds this directory no longer inherits a test
  framework, 126 test translation units and another set of tests in its `ctest` run.

### Fixed

**Slides and the package**

- **Adding or removing a slide on a deck opened from a file changes the file.** `add_empty_slide()`,
  `insert_empty_slide()`, `remove()` and `remove_at()` previously only edited the in-memory
  collection: an added slide got no part, no relationship and no `<p:sldId>`, and a removed one kept
  all three. `slides().size()` changed, the save reported success, and the package did not move.
  Removing now also takes out the part's relationships and its content-type `Override`, since an
  `Override` naming a part that is gone makes the package one a strict consumer rejects.
- **Relationship attributes are written as `r:id` and `r:embed`.** Two code paths built them by
  expanding the relationships namespace into Clark notation, and pugixml stores an attribute name
  verbatim — so the file carried an attribute literally called `{http://…/relationships}embed`.
  Braces and slashes are not name characters, so the part no longer parsed at all.
- **`docProps/app.xml` describes the deck that was actually saved.** `Slides`, `HiddenSlides`,
  `Notes`, `Paragraphs` and `Words` were written from fields only ever populated when a file was
  opened, so a deck built from scratch shipped `<Slides>0</Slides>` however much was in it. They are
  now recounted at save time over the parts `<p:sldIdLst>` registers — a part in the ZIP that no
  `<p:sldId>` points at is not a slide of the deck — which is what any reader of the file would
  count.

**Pictures**

- **A picture frame on a deck built in memory is written as `p:pic`.** The save loop had a branch for
  connectors and an `else` that emitted `p:sp` for everything else, so a picture frame was saved as
  an auto shape: no `p:pic`, no bytes under `ppt/media/`, no image relationship, and an empty
  rectangle where the picture should have been.

**Text**

- **Paragraph, bullet and text-frame formatting reaches the file on a deck opened from a file.**
  Anchoring, frame and paragraph margins, indent, depth, spacing, the line-break and punctuation
  flags and the whole bullet were accepted, read back correctly from memory, and written nowhere. The
  setters were inline in the headers and only assigned members, and the paragraph format was bound to
  an `<a:pPr>` that most paragraphs in a real file do not have — so it was bound to an empty node and
  every setter was a no-op that reported success.
- **The same properties reach the file on a deck built in memory**, where a separate serialiser knew
  about one paragraph property and no text-frame properties at all. It also wrote `algn="ctr"` on
  every paragraph whose alignment had never been set, so "centred" and "inherit from the layout"
  produced identical XML and there was no way to ask for the second.
- **Moving a paragraph keeps every portion it had.** The move constructor deleted everything past the
  first portion, and both `ParagraphCollection::add` and `::insert` take their argument by value — so
  attaching a paragraph to a text frame destroyed its formatting, which made a differently formatted
  span inside a paragraph impossible to produce through the API.

**Lines**

- **Every line property is written**, on both paths. Arrowheads, cap style, compound style, pen
  alignment, join style, miter limit and custom dash patterns were accepted by the setters, read back
  by the getters and never written, so a line described in detail arrived as a plain stroke. On a
  loaded deck none of the setters reached the XML at all — setting a width produced a shape with no
  `<a:ln>` whatsoever.
- **Opening a deck reads every line property back.** Only `@w`, `a:prstDash` and the fill were read,
  and a setter rewrites the whole `<a:ln>` from the model in one pass — so on a loaded deck, setting
  any one line property deleted every other one, silently, leaving a valid package.

**Effects**

- **All eight shape effects are serialised.** Inner shadow, preset shadow, reflection and fill
  overlay were left unimplemented in the serialiser, so a shape built in memory saved an empty
  `<a:effectLst/>`: the call succeeded, the object reported the values back, and the file carried no
  effect.
- **Every effect element gets the children and attributes its type requires.** Outer shadow, inner
  shadow, preset shadow and glow each require exactly one colour child; soft edge requires `@rad` and
  preset shadow `@prst`. Enabling an effect on a loaded deck created an empty element, and PowerPoint
  refuses such a file outright.
- **Effect setters on a newly created element take effect.** Setting an attribute through
  `attribute(name).set_value()` is a silent no-op when the element has no such attribute yet, which
  is exactly the state of a freshly enabled effect — so blur, soft edge and all nine outer-shadow
  properties were accepted and dropped.
- **A reflection starts at the defaults its schema type declares.** Three members sat at the C++ zero
  and were written out as explicit values: `@stA`, `@endPos` and `@fadeDir`. Writing `stA="0"` beside
  `endA="0"` makes the reflection fully transparent at both ends — the element is in the file, the
  schema is satisfied, PowerPoint reports the effect, and the user sees nothing.

**3-D**

- **`a:scene3d` is written with both the children it requires.** It is a sequence of exactly one
  `a:camera` followed by exactly one `a:lightRig`, and each was written only when its own properties
  had been set — so setting a light rig and nothing else produced a file PowerPoint refuses to open,
  and setting only a camera produced the mirror image.
- **`a:lightRig/@dir` is always written**, defaulting when the caller chose a rig but no direction.
  `<a:lightRig rig="threePt"/>` alone is invalid and PowerPoint refuses it.
- **Extrusion height, contour width and the extrusion and contour colours are written.** All four
  were settable, readable and absent from the file; the two colours are handed out by reference and
  mutated in place, so nothing was ever notified that they had changed.

**Tables**

- **A table's graphic frame is locked with `a:graphicFrameLocks`**, the element DrawingML defines.
  `a:graphicFrameLocking` is not a name in the schema — that is the *type* name — so PowerPoint
  tolerated the unknown element and silently discarded it, the frames were never locked, and a strict
  consumer rejected the part.

**Comments**

- **Saving a commented deck that was opened from a file reuses its comments part.** A fresh part was
  created unconditionally, leaving the original in place with a second `comments` relationship on the
  same slide. A slide may carry at most one, and PowerPoint refuses such a package outright.
- **A reply is still a reply after a save.** `set_parent_comment()` assigned a field and nothing
  else, so the package carried two independent flat comments and reopening it gave no parent on
  either. Threading is now written where the format puts it — a `p15:threadingInfo` with a
  `p15:parentCm` in the comment's extension list — and read back, so a thread survives a round trip
  instead of flattening on the first re-save.

**Crashes and memory**

- **Enumerating the shapes of a deck this library did not write no longer reads freed memory.**
  Resolving a placeholder's inherited geometry parsed the layout part into a `pugi::xml_document`
  declared as a local and returned a node into it; a `pugi::xml_node` is a non-owning handle, so the
  caller then read the position and size out of a destroyed document. It needs a placeholder with no
  `a:xfrm` of its own, which is the normal shape of a PowerPoint-authored slide, and an optimised
  build usually reads the intact freed bytes and returns the right numbers — so the fault was
  invisible until it was not.
- **Setting a position on an inheriting placeholder gives that shape its own `a:xfrm`** instead of
  mutating the one in the layout, a part shared by every slide that uses it.
- **The exporter registry is built on first use.** It held its map in a class static while exporters
  registered themselves from a namespace-scope initialiser in another translation unit; the order of
  dynamic initialisation across translation units is unspecified, so registration could run before
  the map was constructed — an access violation before `main()`.
- **Compiler warnings in the library sources are fixed**, including `::tolower` called on a plain
  `char`, which is undefined for any byte above 0x7F on a signed-`char` platform.

### Added

- **A conformance test suite** — tests that write a file through the public API, open it as a ZIP
  archive and assert on the XML inside, never asking the library to read its own output back. Every
  assertion in the harness is calibrated in `harness_self_test.cpp` against a package that satisfies
  it and a package with one deliberate fault injected, so no detector is trusted without having been
  shown to fail. `tests/conformance/README.md` describes it.
- **An out-of-process validator**, `tests/conformance/validate.py`, which re-implements the package
  rules from scratch, adds three that need the file on disk (extension against main-part content
  type, relationship cardinality, slide registration in `<p:sldIdLst>`), and reads every file back
  with `python-pptx` — software that shares none of this library's assumptions.
- **The first committed `.pptx` fixture this library did not write**,
  `tests/test_data/powerpoint_title_and_content.pptx`, whose placeholders carry a bare `<p:spPr/>`
  and inherit their geometry from the layout. Until it existed, every `.pptx` path in the test tree
  named a file the library had produced seconds earlier, so the load path had only ever been fed its
  own output. `make_fixtures.py` regenerates it deterministically.
- **An installable, consumable CMake package.** `project()` carries a `VERSION` and generates
  `<Aspose/Slides/Foss/version.h>`; `install(TARGETS … EXPORT)`, `install(DIRECTORY include/)`,
  `install(EXPORT)` and `export(EXPORT)` produce `AsposeSlidesFossConfig.cmake` and a
  `SameMinorVersion` version file, so a consumer needs nothing but a prefix and
  `find_package(AsposeSlidesFoss CONFIG REQUIRED)`. pugixml and miniz are looked for as installed
  packages first and installed into the same prefix when they had to be fetched, so
  `find_dependency` resolves either way.
- **`examples/consumer/`** — a project that finds the installed package and writes a presentation
  with it, built and run against a fresh install on every CI run. It is the check that the install
  rules produce something usable from outside this build tree.
- **A CycloneDX software bill of materials**, generated by the build from the same variables that
  drive dependency resolution, so it cannot describe a dependency set the build did not use. It is
  installed into the documentation directory and uploaded by CI.
- **Continuous integration.** The repository had none. Every push and pull request builds and runs
  the whole suite on Ubuntu 22.04 and 24.04 with GCC and Clang, on macOS with AppleClang and on
  Windows with MSVC from Visual Studio 2022 and 2025; validates every package the conformance tests
  wrote with `validate.py`; installs the project; and builds and runs `examples/consumer` against
  that install. Separate jobs run the suite under AddressSanitizer and build with CMake 3.20.6, the
  oldest version the project claims to support. Actions are pinned to commit SHAs.
- **`-DASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS=ON`**, and `-DASPOSE_SLIDES_FOSS_WARNINGS_AS_ERRORS=ON`
  for a build that fails on a warning.
- **A NuGet package, `Aspose.Slides.Cpp.FOSS`**, carrying prebuilt MSVC static libraries: **x64 and
  Win32, Debug and Release**, built against the DLL C runtime (`/MD` and `/MDd`). It ships
  `pugixml.lib` and `miniz.lib` beside ours and **pugixml's headers as well as ours**, because a
  static archive carries no dependency information and pugixml is in this library's public interface.
  `packaging/nuget/pack.py` builds all four and packs them; `packaging/nuget/check_package.py`
  asserts on the result; and `examples/nuget-consumer/` is a Visual Studio project that names the
  package and no paths at all, so it fails to compile if NuGet cannot find the package's `.targets`
  where it must be. Set your project's C++ language standard to `stdcpp20` or later — the headers are
  C++20, and the package warns rather than letting the compiler fail inside them.
- **Draft vcpkg and Conan packaging**, under `packaging/`, kept beside the code so a build-system
  change that breaks packaging shows up in the same pull request. **Neither is submittable and
  neither has been submitted**: the source archive checksum both registries need can only be computed
  from the archive a real tag produces. `packaging/README.md` states the blockers.
- **Community documentation** — this changelog, `CONTRIBUTING.md`, `SECURITY.md`,
  `CODE_OF_CONDUCT.md`, issue forms and a pull request template.

### Known limitations

Not defects introduced here, and not scheduled. The README lists what is absent in full; these are
the ones most likely to surprise someone, because the API accepts the call:

- **`slides().add_clone()` does not carry the source shapes' text.** The clone is registered in
  `<p:sldIdLst>`, the part is written, the shape is there with its geometry and its style, and its
  paragraphs arrive empty.
- **`masters().add_clone()` does not reach the file.** The collection reports two masters
  afterwards; the package holds one.
- **There is no API for the slide size, for group shapes, for hyperlinks, for slide backgrounds or
  for themes**, and none for saving to a stream or adding an image from a path or a stream — the only
  overload takes `std::span<const std::uint8_t>`.
- **No charts, SmartArt, OLE objects, mathematical text, animations, transitions, VBA macros or
  digital signatures**, and no rendering or conversion of any kind.

[26.9.0]: https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp/releases/tag/v26.9.0
