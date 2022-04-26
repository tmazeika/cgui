#include "color_utils.h"

namespace cgui {
  SkColor colorToSk(const Color& color) {
    return SkColorSetARGB(
      static_cast<uint8_t>(color.alpha * 0xff),
      static_cast<uint8_t>(color.red * 0xff),
      static_cast<uint8_t>(color.green * 0xff),
      static_cast<uint8_t>(color.blue * 0xff));
  }
}
