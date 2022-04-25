#pragma once

#include "cgui/geometry/geometry.h"
#include "cgui/graphics/color.h"
#include <cstdint>

namespace cgui {
  class Canvas {
  public:
    virtual ~Canvas() = default;

    virtual void fillRect(const Rect&, const Color&) const = 0;

    virtual void fillRoundedRect(const Rect&, float rx, float ry,
      const Color&) const = 0;
  };
}
