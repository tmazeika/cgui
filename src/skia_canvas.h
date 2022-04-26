#pragma once

#include <cgui/canvas.h>
#include <SkCanvas.h>

namespace cgui {
  class SkiaCanvas : public Canvas {
  private:
    SkCanvas* canvas;
  public:
    explicit SkiaCanvas(SkCanvas* canvas);

    void fillRect(const Rect& rect, const Color& color) const override;

    void fillRoundedRect(const Rect& rect, float rx, float ry,
      const Color& color) const override;
  };
}
