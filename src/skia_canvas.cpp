#include <cassert>

#include "skia_canvas.h"
#include "color_utils.h"
#include "geometry_utils.h"

namespace cgui {
  SkiaCanvas::SkiaCanvas(SkCanvas* canvas) : canvas(canvas) {
    assert(canvas);
  }

  void SkiaCanvas::fillRect(const Rect& rect, const Color& color) const {
    SkPaint paint;
    paint.setColor(colorToSk(color));
    this->canvas->drawRect(rectToSk(rect), paint);
  }

  void SkiaCanvas::fillRoundedRect(const Rect& rect, float rx, float ry,
    const Color& color) const {
    SkPaint paint;
    paint.setColor(colorToSk(color));
    this->canvas->drawRoundRect(rectToSk(rect), rx, ry, paint);
  }
}
