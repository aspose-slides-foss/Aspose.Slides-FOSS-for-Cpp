# Packaging drafts

**These are drafts. Do not submit them from this repository.**

`vcpkg/` and `conan/` hold a port and a recipe for the two C++ package
registries. They are kept here, beside the code they describe, so that a change
to the build system that would break packaging is visible in the same pull
request — not discovered months later by whoever tries to publish.

Neither is submittable yet, and both say so in the places that matter:

| Blocker | Where it bites |
|---|---|
| No release has been tagged | `vcpkg_from_github(REF ...)` and Conan's `source()` both need an immutable tag. Both currently point at a tag that does not exist. |
| No source archive checksum | `SHA512` in `portfile.cmake` is a placeholder. It can only be computed from the archive GitHub produces for a real tag. |
| Registry submission is a pull request against someone else's repository | vcpkg ports go to `microsoft/vcpkg`, Conan recipes to `conan-io/conan-center-index`. Each has its own review, its own CI and its own naming and versioning rules, and neither accepts a package from an untagged repository. |

## What they assume about the build

Both configure with `-DASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES=OFF`. A package
manager resolves dependencies itself; a build that quietly clones its own copy
of pugixml would produce a package whose contents the manager cannot see, and
which its consumers cannot audit or patch. With the option off, the build fails
loudly when a dependency is missing instead of reaching for the network.

Both also configure with `-DASPOSE_SLIDES_FOSS_BUILD_TESTS=OFF`, so no test
framework is downloaded or built in a packaging run.

## Dependencies a consumer inherits

pugixml is a **public** dependency: 44 of this library's installed headers
include `<pugixml.hpp>`, so anyone who includes them compiles against pugixml
too. Both the port and the recipe therefore declare it as an ordinary
dependency and not as a private one; a manifest that hid it would produce
packages that fail to compile at the consumer's first `#include`. See
"Public headers and pugixml" in the top-level `README.md` for why it is there
and what removing it would take.

miniz is used only inside the implementation. It is still declared, because a
static archive does not carry its dependencies and the consumer's final link
needs it.

## Checking a draft without submitting it

vcpkg, against a local checkout used as an overlay port:

```sh
vcpkg install aspose-slides-foss --overlay-ports=packaging/vcpkg
```

Conan, from the recipe directory:

```sh
conan create packaging/conan --version 0.1.0
```

Both need the release blockers above resolved first; until then the source step
is the step that fails.
