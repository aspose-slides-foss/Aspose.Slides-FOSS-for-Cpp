# Packaging

Three registries, at two different stages.

| Directory | Registry | State |
|---|---|---|
| `nuget/` | nuget.org | **Real.** It builds, packs and is asserted on; the release workflow publishes from it. |
| `vcpkg/` | `microsoft/vcpkg` | **Draft. Do not submit.** |
| `conan/` | `conan-io/conan-center-index` | **Draft. Do not submit.** |

All three are kept beside the code they describe, so that a change to the build
system which would break packaging is visible in the same pull request — not
discovered months later by whoever tries to publish.

---

## `nuget/` — the Windows binary package

`Aspose.Slides.Cpp.FOSS` carries prebuilt MSVC static libraries. Unlike the two
drafts below, it needs no tag and no external review: it is built here and pushed
from this repository's own release workflow.

```sh
python packaging/nuget/pack.py --work build/nuget-pack
python packaging/nuget/check_package.py build/nuget-pack/package/Aspose.Slides.Cpp.FOSS.<version>.nupkg
```

What it contains, and why:

| | |
|---|---|
| Platforms | **x64** and **Win32** |
| Configurations | **Debug** and **Release** |
| Toolset | built with **v143** (Visual Studio 2022), the **oldest** toolset supported — never the newest available, because a static archive links only into a consumer whose toolset is the same or newer |
| C runtime | `/MD` and `/MDd`, passed explicitly rather than inherited from CMake's default |
| Libraries | `aspose_slides_foss.lib`, **`pugixml.lib`** and **`miniz.lib`**, per platform and configuration |
| Headers | ours plus **pugixml's**, shipped once — the two platforms' header trees are compared and must be identical |

**Three libraries, not one.** A static archive carries no dependency information,
so whoever links it has to name pugixml and miniz as well. pugixml is also in the
public interface — 44 installed headers include `<pugixml.hpp>` — so its *headers*
travel in the package too, and a consumer compiles against them. See "Public
headers and pugixml" in the top-level `README.md`.

**Four builds, one package.** That is why packing is a script rather than a
workflow step: the same command runs on a developer's machine and in CI, or the
thing CI publishes is not the thing anyone has tested.

### The mistake this packaging is written to avoid

NuGet imports `build/native/<PackageId>.targets` and **nothing else**. A targets
file one directory deeper, or spelled with different casing, is carried in the
package and never read: the consumer gets no include path and no library, and the
first sign of trouble is a missing header in their own code.

The sibling `Aspose.Cells.Cpp.FOSS` package ships its targets at
`build/native/Aspose.Cells.Cpp.FOSS/aspose.cells.cpp.foss.targets`, which is
exactly that. It packs, it pushes, it installs, and it does nothing.

So the path is asserted rather than trusted, twice over: `check_package.py` fails
if the file is not at the one path NuGet reads, and `examples/nuget-consumer/`
builds a real Visual Studio project that names the package and no paths at all —
if NuGet cannot find the targets, that project does not compile.

### `-DASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES=ON`, unlike the drafts

The two package managers below turn fetching **off**, because each resolves
dependencies itself and a build that quietly clones its own pugixml produces a
package the manager cannot see into. NuGet has no such mechanism for native C++
dependencies, so this package has to carry pugixml and miniz itself. The opposite
setting for the opposite reason.

---

## `vcpkg/` and `conan/` — drafts

**Do not submit these from this repository.** Neither is submittable, and both say
so in the places that matter:

| Blocker | Where it bites |
|---|---|
| No release has been tagged | `vcpkg_from_github(REF ...)` and Conan's `source()` both need an immutable tag. This repository has **no tags at all**, so both currently point at one that does not exist. |
| No source archive checksum | `SHA512` in `portfile.cmake` is a placeholder. It can only be computed from the archive GitHub produces for a real tag — so it is blocked behind the row above. |
| Registry submission is a pull request against someone else's repository | vcpkg ports go to `microsoft/vcpkg`, Conan recipes to `conan-io/conan-center-index`. Each has its own review, its own CI and its own naming and versioning rules, and neither accepts a package from an untagged repository. |

The NuGet package above is not blocked by any of these, which is why it is real
and these are drafts: it is built from the working tree and published from this
repository, so it needs no tag in someone else's registry and no third-party
review. A tag will exist once a release is cut, and at that point the first two
rows can be closed — in that order.

### What they assume about the build

Both configure with `-DASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES=OFF`, for the reason
above, and with `-DASPOSE_SLIDES_FOSS_BUILD_TESTS=OFF`, so no test framework is
downloaded or built in a packaging run.

### Dependencies a consumer inherits

pugixml is a **public** dependency: 44 of this library's installed headers include
`<pugixml.hpp>`, so anyone who includes them compiles against pugixml too. Both
the port and the recipe declare it as an ordinary dependency and not as a private
one; a manifest that hid it would produce packages that fail to compile at the
consumer's first `#include`.

miniz is used only inside the implementation. It is still declared, because a
static archive does not carry its dependencies and the consumer's final link needs
it.

### Checking a draft without submitting it

vcpkg, against a local checkout used as an overlay port:

```sh
vcpkg install aspose-slides-foss --overlay-ports=packaging/vcpkg
```

Conan, from the recipe directory:

```sh
conan create packaging/conan --version <version>
```
