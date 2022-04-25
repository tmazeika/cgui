#include "cgui/graphics/canvas.h"
#include "cgui/graphics/color.h"
#include "colorutils.cpp"
#include <SkCanvas.h>

namespace cgui {
  class SkiaCanvas : public Canvas {
    SkCanvas* canvas;
  public:
    explicit SkiaCanvas(SkCanvas* canvas) : canvas(canvas) {
      //
    }

    void fillRect(const Rect& rect, const Color& color) const override {
      SkPaint paint;
      paint.setColor(colorToSk(color));
      this->canvas->drawRect(rectToSk(rect), paint);
    }

    void fillRoundedRect(const Rect& rect, float rx, float ry,
      const Color& color) const override {
      SkPaint paint;
      paint.setColor(colorToSk(color));
      this->canvas->drawRoundRect(rectToSk(rect), rx, ry, paint);
    }
  };
}
