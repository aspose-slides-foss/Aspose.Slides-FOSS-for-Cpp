# Security policy

## Supported versions

Nothing has been released. No tag exists in this repository, there is no vcpkg port and no Conan
package in any registry, and the drafts under `packaging/` are not submittable. Every consumer today
builds from source, so the only code that receives security fixes is the current default branch.

| Version | Supported |
|---|---|
| The current default branch | yes |
| Anything built from an older commit | no — rebuild from the default branch |
| The `packaging/` drafts | not published anywhere; nothing to fix in a registry |

When the first release is tagged this table will list released versions instead, and this sentence
will be replaced by a support window.

Note that the version this project reports — `ASPOSE_SLIDES_FOSS_VERSION_STRING` in the generated
`<Aspose/Slides/Foss/version.h>`, currently `26.9.0` — comes from `CMakeLists.txt` and does **not**
identify a build. Quote the commit SHA (`git rev-parse HEAD`) in a report.

## Reporting a vulnerability

**Do not open a public issue for a security problem, and do not attach a proof-of-concept file to
one.**

Use GitHub's private vulnerability reporting on this repository:
[**Report a vulnerability**](https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp/security/advisories/new).
It opens a private advisory only the maintainers can read, and it lets you attach files and discuss
a fix before anything becomes public.

If that page is not available to you, open a public issue containing **only** the sentence "I would
like to report a security issue privately" and no details at all, and wait to be contacted.

Please include, as far as you can:

- the commit SHA you built,
- the compiler and version, the operating system and architecture, and the CMake options you
  configured with — in particular whether `pugixml` and `miniz` came from `FetchContent` or from an
  installed package, and which versions,
- a minimal program and, if one is needed, the `.pptx` that triggers it,
- what happens — a crash, a hang, a file written outside the directory you expected — and what you
  expected instead,
- the impact you believe it has.

A stack trace from a build with `-DASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS=ON` is worth a great deal
more than one from an optimised build: a memory-lifetime fault in an optimised build usually reads
the freed bytes intact and looks like nothing at all.

You will get an acknowledgement of the report. We cannot promise a fix deadline for a project with no
paid support contract behind it, but you will be told what is happening and when a fix lands, and you
will be credited in the advisory unless you ask not to be.

## What is in scope

This library parses untrusted input, in a language with no memory safety. A `.pptx` is a ZIP archive
full of XML; both layers are attacker-controlled when the file came from outside, and the library
opens the archive with miniz and parses the parts with pugixml. Reports about the handling of a
malicious or malformed presentation are in scope, including:

- a crafted archive or XML that causes a crash, a read or write out of bounds, a use after free, an
  unbounded allocation or an infinite loop,
- a part name or relationship target that escapes the package and reaches the file system — the
  classic `../` in a ZIP member name,
- a compression ratio or nesting depth that turns a small input into an exhausting amount of work or
  memory,
- XML processing that reaches the network or the local disk,
- anything that lets a presentation influence the process beyond the object model it is parsed into.

Reports against a build with AddressSanitizer or UndefinedBehaviorSanitizer enabled are welcome even
when the ordinary build shows nothing. That is the point of the sanitizer.

## What is out of scope

- **Missing capabilities.** `save()` throwing `std::invalid_argument` for a format it does not write,
  and the absent features listed in the README, are documented behaviour rather than
  vulnerabilities.
- **Vulnerabilities in pugixml or miniz themselves.** Report those to
  [pugixml](https://github.com/zeux/pugixml/security) and
  [miniz](https://github.com/richgel999/miniz) respectively. Tell us as well if this library's use of
  them makes an upstream issue reachable, or if the pinned version needs to move — that part is ours.
- **Vulnerabilities in the C++ standard library or the compiler.** Report those to their vendors.
- **Vulnerabilities in the commercial Aspose.Slides product**, which is different software. Report
  those through [Aspose support](https://forum.aspose.com/c/slides/11).
- **Findings from an automated scanner with no demonstrated impact on this library**, including
  reports about a dependency version with no path to it from this code.
