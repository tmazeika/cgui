#include "geometry_utils.h"

namespace cgui {
  SkRect rectToSk(const Rect& rect) {
    return SkRect::MakeXYWH(rect.x, rect.y, rect.width, rect.height);
  }
}
