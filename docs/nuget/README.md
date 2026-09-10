# Aspose.Slides FOSS for C++

[![NuGet](https://img.shields.io/nuget/v/Aspose.Slides.Cpp.FOSS.svg)](https://www.nuget.org/packages/Aspose.Slides.Cpp.FOSS/)
[![Downloads](https://img.shields.io/nuget/dt/Aspose.Slides.Cpp.FOSS.svg)](https://www.nuget.org/packages/Aspose.Slides.Cpp.FOSS/)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

A free, MIT-licensed C++ library for creating, reading and editing PowerPoint `.pptx` presentations.
It builds the Office Open XML package itself, so it needs no PowerPoint installation, no COM interop
and no proprietary runtime.

Everything below is verified by opening the file it produced and asserting on the XML inside — never
by asking the library to read its own output back.

[![Aspose.Slides FOSS for C++](https://raw.githubusercontent.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp/main/docs/media/banner-readme.png)](https://products.aspose.org/slides/cpp/)

[Product page](https://products.aspose.org/slides/cpp/) | [Source](https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp) | [Issues](https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp/issues) | [Free support](https://forum.aspose.com/c/slides/11)

## Install

In the Visual Studio Package Manager Console:

```powershell
Install-Package Aspose.Slides.Cpp.FOSS
```

There is no `dotnet add package` for a C++ project: this is a native package, and it is consumed by a
`.vcxproj` through NuGet's own import. Installing it adds the include directory and the libraries to
your project; nothing else is needed.

## What is in the package

| | |
|---|---|
| Platforms | **x64** and **Win32** |
| Configurations | **Debug** and **Release** |
| Toolset | MSVC, **v142 or newer** — the headers are C++20 |
| C runtime | `/MD` and `/MDd` (the DLL runtime, which is the Visual Studio default) |
| Linkage | static archives — `aspose_slides_foss.lib`, plus `pugixml.lib` and `miniz.lib` |

**pugixml is part of the interface, not an implementation detail.** 44 of the headers you include
also include `<pugixml.hpp>`, so its headers ship in this package and are on your include path. That
is why the package carries three libraries rather than one.

Set your project's **C++ Language Standard** to `stdcpp20` or later. If you leave it at the default,
compilation fails inside these headers, which looks like a fault in the library and is not.

For Linux and macOS, build from source or use the vcpkg port or the Conan recipe — see the
repository.

## Quick start

```cpp
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/text_frame.h>

int main() {
    Aspose::Slides::Foss::Presentation presentation;

    auto& shape = presentation.slides()[0].shapes().add_auto_shape(
        Aspose::Slides::Foss::ShapeType::RECTANGLE, 50, 50, 400, 100);
    shape.add_text_frame("Hello from Aspose.Slides FOSS");

    presentation.save("hello.pptx", Aspose::Slides::Foss::SaveFormat::PPTX);
}
```

`presentation.h` forward-declares the types its collections return, so a program that reaches through
`slides()[0].shapes()` includes `slide.h` and `shape_collection.h` as well. That is deliberate: the
headers are C++20 and including one does not drag in the rest.

## What it does

- **Presentations** — create, open a file, save to a file.
- **Slides** — add, insert, remove, clone, hide. Sections, including reordering slides with them.
- **Masters and layouts** — enumerate them, and clone a master.
- **Shapes** — AutoShapes, connectors bound by connection site, tables with cell merging, picture
  frames.
- **Text** — text frames, paragraphs and portions; character and paragraph formatting; bullets.
- **Appearance** — solid, gradient, pattern and picture fills; full line formatting; all eight visual
  effects; 3-D formatting with camera and light rig.
- **Pictures** — added from a `std::span<const std::uint8_t>`.
- **Notes and comments** — speaker notes, and comments with their authors and threading.
- **Document properties** — core, extended and custom.
- **Round-trip** — parts the library does not model are preserved verbatim.

## What it does not do

Stated plainly, because a library that fails silently is worse than one that says no.

- **No rendering or conversion of any kind.** No PDF, image, HTML or SVG export. `save()` writes the
  six Office Open XML presentation formats and throws `std::invalid_argument` for every other
  `SaveFormat` value, naming the six that work.
- **No charts, SmartArt, OLE objects, animations, slide transitions, group shapes, hyperlinks, slide
  backgrounds or themes.**
- **No API for the slide size** — a new presentation is 4:3 and cannot be changed.
- **No saving to a stream, and no adding an image from a path or a stream** — the only overload takes
  a byte span.
- **No encryption, protection, digital signatures, VBA macros or mathematical text.**
- `slides().add_clone()` writes the shape but not its text, and `masters().add_clone()` does not
  reach the file.

## When you want the commercial product

This is not a drop-in replacement for
[Aspose.Slides for C++](https://products.aspose.com/slides/cpp/) and is not trying to be. If you need
PDF or image rendering, charts, animations, the other presentation formats, or a support commitment,
that is the product to use. If you need to build and read `.pptx` packages under a permissive licence,
this one is complete for that.

## Licence and support

MIT. The full text is packed alongside this file, with the third-party notices for pugixml and miniz.

Questions and bug reports are welcome on the
[issue tracker](https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp/issues) or on the
[free support forum](https://forum.aspose.com/c/slides/11). A report that names the version and
attaches the file PowerPoint would not open is one that can be acted on.
