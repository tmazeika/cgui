#pragma once

#include <cgui/box.h>
#include <memory>

namespace cgui {
  std::unique_ptr<Box> createSizedBox(Size,
    std::unique_ptr<Box> child = nullptr);

  std::unique_ptr<Box> createSizedBox(float width, float height,
    std::unique_ptr<Box> child = nullptr);
}
