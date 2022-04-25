#pragma once

#include "cgui/box/box.h"
#include "cgui/graphics/color.h"
#include <memory>

namespace cgui {
  std::unique_ptr<Box> createBackgroundBox(Color,
    std::unique_ptr<Box> child = nullptr);
}
