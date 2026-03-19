# Aspose.Slides FOSS for C++

The official open-source C++ library by Aspose.Slides for creating, reading, and editing PowerPoint (`.pptx`) presentations.

---

## Quick Start

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/export/save_format.h>

using namespace Aspose::Slides::Foss;

int main() {
    // Open an existing presentation
    Presentation pres("input.pptx");
    auto& slides = pres.slides();
    // ... work with slides ...
    pres.save("output.pptx", SaveFormat::PPTX);

    // Create a new presentation
    Presentation new_pres;
    auto& slide = new_pres.slides()[0];
    new_pres.save("new.pptx", SaveFormat::PPTX);
}
```

---

## Features

- **Presentation I/O** — Open, create, and save `.pptx` files with full round-trip fidelity
- **Slides** — Add, remove, clone, reorder, and iterate slides
- **Shapes** — AutoShapes, PictureFrames, Tables, Connectors
- **Text** — TextFrame, Paragraph, Portion with character, paragraph, and text frame formatting (including bullets)
- **Fill** — Solid, gradient, pattern, and picture fills
- **Lines** — Width, dash style, arrows, join and alignment
- **Effects** — Outer shadow, glow, soft edge, blur, reflection, inner shadow
- **3D** — Bevel, camera, light rig, material, extrusion depth
- **Document properties** — Core, app, and custom properties
- **Notes slides** — Per-slide notes with header/footer management
- **Comments** — Threaded comments with authors, timestamps, and positions
- **Images** — Embed from file, bytes, or stream

---

## Usage Examples

### Shapes

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/export/save_format.h>

using namespace Aspose::Slides::Foss;

Presentation pres;
auto& slide = pres.slides()[0];
auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 300, 100);
shape.add_text_frame("Hello, world!");
pres.save("shapes.pptx", SaveFormat::PPTX);
```

### Text Formatting

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/export/save_format.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

Presentation pres;
auto& shape = pres.slides()[0].shapes().add_auto_shape(
    ShapeType::RECTANGLE, 50, 50, 400, 150);
auto& tf = shape.add_text_frame("Formatted text");
auto& fmt = tf.paragraphs()[0].portions()[0].portion_format();
fmt.set_font_height(24.0f);
fmt.set_font_bold(NullableBool::TRUE);
fmt.fill_format().set_fill_type(FillType::SOLID);
fmt.fill_format().solid_fill_color().set_color(Color::from_argb(255, 0, 70, 127));
pres.save("text.pptx", SaveFormat::PPTX);
```

### Table

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/table.h>
#include <Aspose/Slides/Foss/export/save_format.h>

using namespace Aspose::Slides::Foss;

Presentation pres;
auto& table = pres.slides()[0].shapes().add_table(
    50, 50, {120.0, 120.0, 120.0}, {40.0, 40.0});
table.rows()[0][0].text_frame().set_text("Name");
table.rows()[0][1].text_frame().set_text("Value");
pres.save("table.pptx", SaveFormat::PPTX);
```

### Connector

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/export/save_format.h>

using namespace Aspose::Slides::Foss;

Presentation pres;
auto& slide = pres.slides()[0];
auto& box1 = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 100, 150, 60);
auto& box2 = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 350, 100, 150, 60);
auto& conn = slide.shapes().add_connector(
    ShapeType::BENT_CONNECTOR3, 0, 0, 10, 10);
conn.set_start_shape_connected_to(&box1);
conn.set_start_shape_connection_site_index(3);  // right
conn.set_end_shape_connected_to(&box2);
conn.set_end_shape_connection_site_index(1);    // left
pres.save("connector.pptx", SaveFormat::PPTX);
```

### Fill

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/export/save_format.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

Presentation pres;
auto& shape = pres.slides()[0].shapes().add_auto_shape(
    ShapeType::RECTANGLE, 50, 50, 300, 150);
shape.fill_format().set_fill_type(FillType::SOLID);
shape.fill_format().solid_fill_color().set_color(Color::from_argb(255, 30, 120, 200));
pres.save("fill.pptx", SaveFormat::PPTX);
```

### Notes

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/notes_slide_manager.h>
#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/export/save_format.h>

using namespace Aspose::Slides::Foss;

Presentation pres;
auto& notes = pres.slides()[0].notes_slide_manager().add_notes_slide();
notes.notes_text_frame().set_text("Speaker notes go here.");
pres.save("notes.pptx", SaveFormat::PPTX);
```

### Comments

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <chrono>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

Presentation pres;
auto& author = pres.comment_authors().add_author("Jane Smith", "JS");
auto& slide = pres.slides()[0];
author.comments().add_comment(
    "Review this slide", &slide, PointF{2.0, 2.0},
    std::chrono::system_clock::now());
pres.save("comments.pptx", SaveFormat::PPTX);
```

### Document Properties

```cpp
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/document_properties.h>
#include <Aspose/Slides/Foss/export/save_format.h>

using namespace Aspose::Slides::Foss;

Presentation pres;
pres.document_properties().set_title("Q1 Results");
pres.document_properties().set_author("Finance Team");
pres.document_properties().set_custom_property_value("Version", 3);
pres.save("deck.pptx", SaveFormat::PPTX);
```

---

## Building

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Dependencies (fetched automatically via CMake FetchContent):
- [pugixml](https://github.com/zeux/pugixml) v1.14 — XML parsing
- [miniz](https://github.com/richgel999/miniz) 3.0.2 — ZIP archive I/O
- [GoogleTest](https://github.com/google/googletest) v1.15.2 — Testing (build only)

**Requires:** C++20 compiler, CMake 3.20+

---

## Limitations

The following areas are not yet available:

- Charts, SmartArt, OLE objects, mathematical text
- Animations and slide transitions
- Export to non-PPTX formats (PDF, HTML, SVG, images)
- VBA macros, digital signatures
- Hyperlinks and action settings

Unknown XML parts encountered during load are preserved verbatim on save —
opening and re-saving a file will never strip content this library does not yet understand.

---

## Links

- [GitHub Repository](https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp)
- [Issue Tracker](https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp/issues)

---

## License

[MIT License](https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp/blob/main/LICENSE)
