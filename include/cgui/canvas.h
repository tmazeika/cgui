#pragma once

#include <cgui/color.h>
#include <cgui/geometry.h>

namespace cgui {
  class Canvas {
  public:
    virtual ~Canvas() = default;

    virtual void fillRect(const Rect&, const Color&) const = 0;

    virtual void fillRoundedRect(const Rect&, float rx, float ry,
      const Color&) const = 0;
  };
}
