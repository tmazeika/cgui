#pragma once

#include <cstdint>

namespace cgui {
  struct Color {
    const float red;
    const float green;
    const float blue;
    const float alpha;

    Color(float red, float green, float blue, float alpha = 1.0f);

    explicit Color(float gray, float alpha = 1.0f);
  };
}
