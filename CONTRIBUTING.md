# Contributing

Thank you for considering a contribution. This document is specific to the **C++** edition of
Aspose.Slides FOSS; the .NET, Java and Python editions live in their own repositories, have their own
build systems and their own conventions, and a patch does not port between them unchanged.

## The one rule that is particular to this project

**A fix to a writer ships with a test that asserts on the produced `.pptx` package — not on what this
library reads back.**

A library agrees with itself for free. If the writer emits `<a:graphicFrameLocking>` where DrawingML
says `<a:graphicFrameLocks>`, and the matching reader looks for `<a:graphicFrameLocking>`, then every
property reads back exactly what was set, every round-trip test passes, and PowerPoint silently
discards the element on load. That defect was real and it lived in this repository. So did a slide
added to a deck opened from a file: `slides().size()` went up, the getters agreed, and the package
gained no part, no relationship and no `<p:sldId>`.

The same shape of mistake hides an `r:embed` that resolves to nothing, a part with no content type,
and an effect element missing an attribute its type requires. The object model is intact in memory,
so a test built on the object model sees nothing at all.

Unit tests of the object model are welcome and there are many, but they cannot close a writer bug.
Put the assertion in `tests/conformance/`, where the test opens the saved file as a ZIP archive and
reads the XML out of it. `tests/conformance/README.md` describes the harness in full.

## Prerequisites

- A **C++20** compiler.
- **CMake 3.20** or newer. 3.20.6 is built in CI on every push, so the floor is a tested claim rather
  than an aspiration.
- **Python 3** and `python-pptx` (`pip install python-pptx`), for the out-of-process checks below.
  Nothing in the library or the test binary needs Python; the checks that do are separate.

The build resolves **pugixml 1.14**, **miniz 3.0.2** and **GoogleTest 1.15.2** by looking for an
installed package first and cloning the pinned tag with CMake's `FetchContent` only when it finds
none. A first configure on a machine with no copies of those therefore needs network access and takes
a while.

## Build

```bash
git clone https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp.git
cd Aspose.Slides-FOSS-for-Cpp
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel 4
```

Give `--parallel` a number. With no number it means *unlimited* under the Makefile generators, not
"one job per core": the test suite is over a hundred translation units and Make starts compiling all
of them at once, which on a typical CI machine or laptop exhausts memory and gets the compiler killed.
Raise the 4 to suit the machine.

`--config Release` is what a multi-configuration generator (Visual Studio, Xcode) reads and
`CMAKE_BUILD_TYPE` is what the single-configuration ones read. Passing both is how one command line
serves every generator.

The options you are most likely to want:

| Option | Default | Effect |
|---|---|---|
| `ASPOSE_SLIDES_FOSS_BUILD_TESTS` | `ON` at top level | Build the test suite. `OFF`, or `-DBUILD_TESTING=OFF`, downloads no test framework at all. |
| `ASPOSE_SLIDES_FOSS_WARNINGS_AS_ERRORS` | `OFF` | Turn this project's own warnings into errors. See the note below before switching it on. |
| `ASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS` | `OFF` | Build library and tests with AddressSanitizer. |
| `ASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES` | `ON` | Allow `FetchContent` to supply a dependency that was not found. |
| `ASPOSE_SLIDES_FOSS_INSTALL` | `ON` at top level | Generate the install and export rules. |

**About warnings-as-errors.** The library compiles without a single warning under MSVC `/W4`, and CI
runs its two Windows legs with `ASPOSE_SLIDES_FOSS_WARNINGS_AS_ERRORS=ON` for that reason. The
`-Wall -Wextra` set GCC and Clang apply is a different set and has *not* been brought to zero, so
those legs run with it `OFF`. If you reduce the warning count on a GCC or Clang leg to zero, please
flip that leg in `.github/workflows/ci.yml` in the same pull request.

## Test

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel 4
ctest --test-dir build --build-config Release --output-on-failure --parallel 4
```

`ctest` is the entry point CI uses and the one to quote in a pull request. Everything is in one
binary, `aspose_slides_foss_tests`, which you can also run directly — `build/Release/` under a
multi-configuration generator, `build/` under a single-configuration one:

```bash
./build/aspose_slides_foss_tests                            # everything
./build/aspose_slides_foss_tests --gtest_filter='*Conformance*'
./build/aspose_slides_foss_tests --gtest_list_tests          # what is there
```

Three groups of tests share that binary:

| Directory | What it covers |
|---|---|
| `tests/Aspose.Slides.Foss.Tests` | unit tests of the object model |
| `tests/Aspose.Slides.Foss.IntegrationTests` | end-to-end use of the public API |
| `tests/conformance` | assertions against the produced `.pptx` package, never against read-back |

Run the whole binary rather than a filter before you push. A filter means a suite added later is
silently never run.

### The conformance suite, and the checks that cannot run inside it

Two things a C++ test binary cannot do are schema-aware validation and a read-back by third-party
software. Both live in `tests/conformance/validate.py`, which re-implements the package rules from
scratch — an independent implementation is what catches a harness that agrees with the writer by
accident — and then opens every file with `python-pptx`.

Set `ASPOSE_SLIDES_FOSS_CONFORMANCE_OUT` and every conformance test leaves a copy of every file it
wrote in that directory. Point the script at the result:

```bash
# collect a corpus while the suite runs
ASPOSE_SLIDES_FOSS_CONFORMANCE_OUT=$PWD/conformance-corpus \
  ctest --test-dir build --build-config Release --output-on-failure

# then check it from outside the process that produced it
python tests/conformance/validate.py conformance-corpus --require-python-pptx
```

It takes a directory or a single file. Exit status is 0 when everything passes.
`--require-python-pptx` turns "python-pptx is not installed" from a skip into a failure, which is
what CI passes: a check that silently does not run is not a check.

On top of the rules the in-process harness applies, `validate.py` adds three that need the file on
disk: the file's extension must match the main part's content type; a part may hold at most one
`comments`, `slideLayout`, `notesSlide` or `notesMaster` relationship; and every slide part must be
registered in `<p:sldIdLst>` with every `<p:sldId>` resolving to a part that exists.

### AddressSanitizer

Memory-lifetime faults are not reliably visible in an optimised build — a read through a pointer to a
freed object usually returns whatever the allocator left behind, so the same defect crashes on one
machine and returns plausible numbers on another. One such fault (a `pugi::xml_node` handed out into
a destroyed document) was in this library.

```bash
cmake -B build-asan -DCMAKE_BUILD_TYPE=RelWithDebInfo -DASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS=ON
cmake --build build-asan --parallel 4
ASAN_OPTIONS=detect_leaks=1:abort_on_error=1 ctest --test-dir build-asan --output-on-failure
```

CI runs this on Linux with Clang. On MSVC the same option compiles with `/fsanitize=address`.

### Checking the install, the way a consumer sees it

`examples/consumer/` is a project in its own right: it never adds this source tree, and the only
thing it is given is a prefix to look in. If `find_package` cannot see the package, or the exported
target does not carry its include directories, its C++ standard or its dependencies, this fails.

```bash
cmake --install build --config Release --prefix "$PWD/install"
cmake -S examples/consumer -B build-consumer -DCMAKE_PREFIX_PATH="$PWD/install"
cmake --build build-consumer --config Release
./build-consumer/consumer_example out.pptx        # build-consumer/Release/ on MSVC
python tests/conformance/validate.py out.pptx --require-python-pptx
```

Run this if you touch `CMakeLists.txt`, `cmake/`, the public headers or `packaging/`.

## Which compilers have to work

CI builds and runs the whole suite on every push and every pull request, on these seven legs:

| Runner image | Compiler | Warnings as errors |
|---|---|---|
| `ubuntu-22.04` | GCC | off |
| `ubuntu-22.04` | Clang | off |
| `ubuntu-24.04` | GCC | off |
| `ubuntu-24.04` | Clang | off |
| `macos-14` (arm64) | AppleClang | off |
| `windows-2022` | MSVC | **on** |
| `windows-2025` | MSVC | **on** |

The matrix names an image, not a compiler version: the image decides which compiler `gcc`, `clang`
or `cl` is, and that changes when GitHub updates it. The two Windows legs differ in the image, and
therefore in the MSVC toolset the image happens to carry — they are not pinned to a named Visual
Studio release, and a table here that named one would go stale the next time GitHub refreshes the
image.

Every leg prints `cmake --version` into the log, and CMake's own `The CXX compiler identification
is ...` line in the configure step names the compiler it selected. That line, not the table above,
is the record of what a given run built with.

Two further jobs run on every push: the suite under AddressSanitizer on `ubuntu-24.04` with Clang,
and a configure-build-test with **CMake 3.20.6**, the oldest version `cmake_minimum_required` and the
README claim.

Nothing beyond that list is tested, so nothing beyond it is claimed. If you know the library works
somewhere else, a pull request that adds the leg is more useful than a sentence saying so.

## What a good pull request looks like

1. **It fixes one thing.** A pull request that repairs a writer and also renames three files is two
   pull requests.
2. **It has a failing test first.** Write the test against the unfixed code, watch it fail, and put
   that failure output in the pull request description. A test that has never failed has not been
   shown to test anything.
3. **The test names the user-visible failure**, in the words a user would use:
   `APictureFrameResolvesTheImageItPointsAt`, not `TestPictureFrame3`. The name is the bug report.
4. **It builds its deck through the public API only.** If a case needs an internal member to be set
   up, it is testing the internals, not the artefact. Everything under `_internal/` is exactly that,
   whatever directory it is installed into.
5. **It says what it changed about the file.** "Writes `<a:graphicFrameLocks>` instead of
   `<a:graphicFrameLocking>` in `ppt/slides/slide1.xml`" is reviewable. "Fixed table locking" is not.
6. **It updates `CHANGELOG.md`** under `## [Unreleased]`, in the language a caller would use, if the
   change is one a caller can observe.
7. **It keeps the sources list in step.** `CMakeLists.txt` lists source files explicitly rather than
   globbing them, because a glob is evaluated once at configure time and a file added afterwards is
   silently absent from the build. A new `.cpp` goes in `ASPOSE_SLIDES_FOSS_SOURCES`, a new test
   `.cpp` in `ASPOSE_SLIDES_FOSS_TEST_SOURCES`.
8. **It does not add a dependency without discussion.** The library depends on pugixml and miniz and
   nothing else. Open an issue and make the case before writing the code.
9. **It does not widen the public headers' dependency on pugixml.** 44 installed headers already
   include `<pugixml.hpp>`; the README explains why and what removing it would take. A new public
   header that does not need the type should not include it, and a new public member should not take
   or return a `pugi::` type if it can avoid it.

### Behaviour that is deliberate, not a bug

Before filing a fix for one of these, please open an issue instead — they are decisions with
reasoning behind them, and the reasoning is in the source:

- `save()` throws `std::invalid_argument` for the `SaveFormat` values it does not write. It will not
  write a presentation package under a name that claims to be PDF, ODP or an image.
- The macro-enabled formats (`PPTM`, `PPSM`, `POTM`) are written **without** a VBA project. A
  macro-enabled package that carries no `vbaProject` part is still valid and still opens.
- `Shape::get_xfrm()` returns this shape's own `a:xfrm` and an empty node when it has none. It does
  not resolve placeholder inheritance; `Shape::get_inherited_frame()` does, and returns a value.
- `add_picture_frame` throws rather than writing a picture frame with no image behind it.
- The library is built as a **static** archive even when `BUILD_SHARED_LIBS=ON`. Nothing in the
  sources is annotated for symbol export, so a shared build would export nothing.

## C++ conventions in this repository

- Follow the layout and naming of the code you are changing. Types are `PascalCase`, functions and
  variables `snake_case`, data members carry a trailing underscore, headers are `snake_case.h` under
  `include/Aspose/Slides/Foss/`, and the matching source is at the same relative path under
  `src/Aspose.Slides.Foss/`.
- Anything under an `_internal/` directory is not public API, even though it is installed.
- Every public header carries the SPDX licence identifier the existing headers carry.
- Prefer defining a setter out of line in the `.cpp`. Several defects in this repository's history
  were inline setters in headers that assigned a member and never touched the XML.

## Commits

- Write the commit subject as a sentence saying what the change does to the software; the existing
  history is the model.
- Sign nothing off; there is no CLA and no DCO check.

## Licence

By contributing you agree that your contribution is licensed under the
[MIT License](LICENSE), the same terms as the rest of the project.
