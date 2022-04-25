#include "cgui/geometry/geometry.h"
#include "cgui/graphics/color.h"
#include "SkCanvas.h"
#include "SkColor.h"

namespace cgui {
  SkColor colorToSk(const Color& color) {
    return SkColorSetARGB(
      static_cast<uint8_t>(color.alpha * 0xff),
      static_cast<uint8_t>(color.red * 0xff),
      static_cast<uint8_t>(color.green * 0xff),
      static_cast<uint8_t>(color.blue * 0xff));
  }

  SkRect rectToSk(const Rect& rect) {
    return SkRect::MakeXYWH(rect.x, rect.y, rect.width, rect.height);
  }
}
