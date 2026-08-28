# Conformance tests

These tests answer one question: **is the file we wrote a correct PPTX?**

They are separate from the rest of the suite because they assert on the *saved
package* — the ZIP, its parts, and the XML inside them — and never on the
library's own read-back.

## Why not just read the file back?

Because a reader and a writer that share a misunderstanding of the format agree
with each other perfectly.

If `save()` writes an element under the wrong name and `load()` looks for that
same wrong name, a round-trip test passes, the getters return what the setters
were given, and the file is still one that PowerPoint discards or refuses. The
suite is green and the product is broken, and nothing in the suite can tell you
so — there is no assertion anywhere that could fail.

The same applies to counting: a reader that reports the number of slide *parts*
in the ZIP will happily report three slides for a package in which only one is
registered in `p:sldIdLst`, which is the only place a consumer looks.

So the rule for everything in this directory is:

> Write the file. Open the bytes. Parse the XML. Assert on the elements and
> attributes.

If a test in here calls the presentation API to check the presentation API, it
is not doing its job.

## What the harness gives you

`conformance.h` — include it as `"conformance/conformance.h"`.

**Reading a package**

```cpp
conformance::Package pkg(path_to_pptx);

pkg.entry_names();                          // every member, sorted
pkg.has_entry("ppt/slides/slide1.xml");
pkg.entry_bytes("ppt/media/image1.png");    // raw bytes
pkg.entry_text("[Content_Types].xml");
pkg.xml("ppt/slides/slide1.xml");           // parsed once, cached
pkg.entries_matching("^ppt/media/");        // regex over member names
pkg.content_type_of("ppt/slides/slide1.xml");
pkg.relationship_targets("ppt/slides/_rels/slide1.xml.rels");
```

**Package-wide rules** — each returns a `::testing::AssertionResult`, so
`EXPECT_TRUE(...)` prints what went wrong rather than `false is not true`:

| Assertion | Rule |
|---|---|
| `AllRelationshipReferencesResolve` | every `r:id` / `r:embed` / `r:link` resolves to a `Relationship Id` in that part's own `.rels` |
| `EveryPartHasAContentType` | every part resolves a content type through an `Override` or a `Default` |
| `NoContentTypeOverrideDangles` | every `Override` names a part that is actually in the package |
| `PartContentTypesMatchEcma` | parts whose names follow an ECMA-376 convention carry the content type it requires |
| `PackageIsInternallyConsistent` | all four of the above |

The content-type rules are not pedantry. Per ISO/IEC 29500-2 the content type
*is* the part's identity: a slide part with no `Override` falls through to
`Default Extension="xml"`, which makes it `application/xml` — not a slide,
whatever its name and its contents say.

**Element-level assertions**

```cpp
ElementExists(pkg, part, xpath, {{"attr", "value"}, ...});
ElementAbsent(pkg, part, xpath);
ChildOrderIs(pkg, part, xpath, {"a:rPr", "a:t"});
CountMatches(pkg, part, xpath);
ChildNames(node);
```

XPath goes through pugixml, which is not namespace-aware, so name tests use the
literal prefixed name as it appears in the file: `//a:effectLst/a:outerShdw`,
not `//{...drawingml...}effectLst`.

`ChildOrderIs` exists because OOXML complex types are *sequences*. A consumer
that meets `<a:rPr>` after `<a:t>` is entitled to discard it, and usually does —
silently. Presence checks cannot see that class of fault.

**A fixture and a temp directory**

`saved_deck.h` gives you `conformance::SavedDeckTest`, a fixture with a
per-test temp directory and:

```cpp
auto pkg = save_and_inspect(pres);              // save, then open the bytes
auto path = save(pres, "deck.potx", SaveFormat::POTX);
```

It deliberately offers no "save and reopen through `Presentation`" helper.

## Adding a case

1. Pick the user-visible failure. Name the test after that, in words a user
   would recognise — `ACharacterBulletReachesTheFile`, not `TestBulletXml`.
2. Build the deck through the **public API only**. If the case cannot be
   reached from the public API, the case is not a user-visible defect.
3. Save with `save_and_inspect`.
4. Assert with the harness. Prefer the narrowest assertion that would actually
   have caught the fault, and add a `<<` message saying what the user sees when
   it fails.
5. **Run it against the unfixed code first and watch it fail.** A conformance
   test that has never failed is an assumption, not a test. If it passes before
   the fix, either the defect is not real or the test does not reach it — find
   out which before going further.

Regression guards — tests pinning behaviour that is already correct — are
welcome and are marked as such in a comment, so a reader can tell at a glance
which tests are describing a fault and which are holding ground.

## Fixtures

`tests/test_data/powerpoint_title_and_content.pptx` is a deck this library did
not write: hand-authored OOXML, with placeholders that carry a bare
`<p:spPr/>` and inherit their geometry from the layout. It exists because every
other `.pptx` path in the test tree names a file the library produced seconds
earlier, so the load path had never been fed anything but its own output.

Regenerate it with:

```sh
python tests/conformance/make_fixtures.py
python tests/conformance/validate.py tests/test_data/powerpoint_title_and_content.pptx
```

The generator is deterministic — fixed timestamps, fixed member order — so a
regeneration that changes nothing produces no diff.

## The out-of-process checks

Two things cannot run inside the test binary: a schema-aware third-party
reader, and an independent implementation of the package rules. Both live in
`tests/conformance/validate.py`.

```sh
# collect a corpus while the C++ suite runs
ASPOSE_SLIDES_FOSS_CONFORMANCE_OUT=out/conformance ./aspose_slides_foss_tests

# then check it from outside
python tests/conformance/validate.py out/conformance
```

`validate.py` re-implements the relationship and content-type rules from
scratch, and adds three that need the file on disk rather than the part table:

* the file's **extension matches the main part's content type** — PowerPoint
  refuses a package whose name and contents disagree, reporting that the file
  extension has changed;
* **relationship cardinality** — a part may hold at most one `comments`,
  `slideLayout`, `notesSlide` or `notesMaster` relationship;
* **slide registration** — every slide part is reachable from `p:sldIdLst`, and
  every `p:sldId` resolves to a part that is there.

It also loads every file with `python-pptx` if it is installed
(`pip install python-pptx`). Duplicating the rules is the point: an independent
implementation is what catches a harness that agrees with the writer by
accident. Exit status is 0 when everything passes, so CI can run it as its own
step.

Nothing under `include/` may depend on anything in this directory. The harness
is test-only.

## AddressSanitizer

Memory-lifetime faults are not reliably visible in an optimised build: reading
through a pointer to a freed object usually returns whatever the allocator left
behind, so the same defect crashes on one machine and returns plausible numbers
on another.

```sh
cmake -S . -B build-asan -DASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS=ON
cmake --build build-asan
```

CI should run the suite with this on at least once. A debug build is a weaker
but useful substitute on toolchains where the sanitizer is unavailable: the MSVC
debug heap fills freed blocks with a poison pattern, which turns some of the
same faults from intermittent into deterministic.
