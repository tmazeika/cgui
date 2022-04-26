#pragma once

#include <cgui/box.h>
#include <memory>

namespace cgui {
  std::unique_ptr<Box> createTextBox(std::string);
}
