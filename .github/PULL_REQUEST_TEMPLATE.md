<!--
Thank you for the pull request. CONTRIBUTING.md has the detail; this template is the short form.
Delete any section that genuinely does not apply, rather than leaving it blank.
-->

## What this changes

<!-- One or two sentences. If it changes what ends up in the .pptx, name the part and the element:
     "writes <a:graphicFrameLocks> instead of <a:graphicFrameLocking> in ppt/slides/slide1.xml". -->

Closes #

## Why

<!-- The user-visible problem. What did someone see happen, and what did they expect? -->

## How it was verified

<!-- Paste the failing test output from BEFORE the fix, and the passing run after it. A test that
     has never failed has not been shown to test anything. -->

```
```

## Checklist

- [ ] `cmake --build build --config Release` is clean.
- [ ] `ctest --test-dir build --build-config Release --output-on-failure` passes — the whole
      binary, not a filter.
- [ ] **If this changes what is written to the file**, there is a test in `tests/conformance/` that
      opens the produced `.pptx` and asserts on its XML. A test that reads the value back through
      this library does not count.
- [ ] The test is named after the user-visible failure, not after the method it calls.
- [ ] The out-of-process check passes over a corpus this build produced:
      `ASPOSE_SLIDES_FOSS_CONFORMANCE_OUT=$PWD/corpus ctest --test-dir build --build-config Release`
      then `python tests/conformance/validate.py corpus --require-python-pptx`.
- [ ] A new source file is listed in `ASPOSE_SLIDES_FOSS_SOURCES`, a new test file in
      `ASPOSE_SLIDES_FOSS_TEST_SOURCES`. The lists are explicit on purpose: a glob is evaluated once
      at configure time and a file added afterwards is silently absent from the build.
- [ ] `CHANGELOG.md` is updated under `## [Unreleased]` if a caller can observe this change.
- [ ] No new dependency, and no new `#include <pugixml.hpp>` in a public header.
- [ ] If `CMakeLists.txt`, `cmake/`, the public headers or `packaging/` changed: the install and
      `examples/consumer` still work — see "Checking the install" in CONTRIBUTING.md.
- [ ] No generated files, build output or test artefacts are in the diff.

## Anything a reviewer should look at closely

<!-- A decision you were unsure about, a case you did not cover, a behaviour you changed on
     purpose. Say it here rather than letting it be found. -->
