#pragma once

#include "cgui/geometry/geometry.h"
#include "cgui/graphics/canvas.h"
#include <any>

namespace cgui {
  class Box {
  public:
    std::any parentData;

    virtual ~Box() = default;

    virtual Size getSize(const Constraints&) = 0;

    virtual void render(const Canvas&, const Rect&) const = 0;
  };
}
