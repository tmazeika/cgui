#pragma once

#include <cgui/canvas.h>
#include <cgui/geometry.h>
#include <any>
#include <memory>

namespace cgui {
  struct Box {
    std::any parentData;

    virtual ~Box() = default;

    virtual Size getSize(const Constraints&) = 0;

    virtual void render(const Canvas&, const Rect&) const = 0;
  };

  std::unique_ptr<Box> createBackgroundBox(Color,
    std::unique_ptr<Box> child = nullptr);
}
