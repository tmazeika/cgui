#include "cgui/graphics/color.h"
#include <cassert>

namespace cgui {
  Color::Color(float red, float green, float blue, float alpha)
    : red(red), green(green), blue(blue), alpha(alpha) {
    assert(0.0f <= red && red <= 1.0f);
    assert(0.0f <= green && green <= 1.0f);
    assert(0.0f <= blue && blue <= 1.0f);
    assert(0.0f <= alpha && alpha <= 1.0f);
  }

  Color::Color(float gray, float alpha) : Color(gray, gray, gray, alpha) {
    //
  }
}
