#include "cgui/geometry/geometry.h"
#include <cassert>
#include <cmath>

namespace cgui {
  namespace ord {
    template<typename T>
    T min(T a, T b) {
      return a < b ? a : b;
    }

    template<typename T>
    T max(T a, T b) {
      return a > b ? a : b;
    }
  }

  const float UNBOUNDED = INFINITY;

  bool isUnbounded(float length) {
    return std::isinf(length) == 1;
  }

  Size::Size(float width, float height) : width(width), height(height) {
    assert(!isUnbounded(width) && !isUnbounded(height));
    assert(width >= 0.0f && height >= 0.0f);
  }

  Size Size::growBy(Size size) const {
    return this->growBy(size.width, size.height);
  }

  Size Size::growBy(float width, float height) const {
    return {this->width + width, this->height + height};
  }

  Size Size::growToSatisfy(Constraints c) const {
    assert(this->width <= c.max.width && this->height <= c.max.height);
    return {
      ord::max(c.min.width, this->width),
      ord::max(c.min.height, this->height),
    };
  }

  Size Size::shrinkBy(Size size) const {
    return this->shrinkBy(size.width, size.height);
  }

  Size Size::shrinkBy(float width, float height) const {
    return {this->width - width, this->height - height};
  }

  Size Size::shrinkToSatisfy(Constraints c) const {
    assert(this->width >= c.min.width && this->height >= c.min.height);
    return {
      ord::min(c.max.width, this->width),
      ord::min(c.max.height, this->height),
    };
  }

  Size Size::rotate90() const {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
    return {this->height, this->width};
#pragma clang diagnostic pop
  }

  Constraints::Constraints(Size min, Size max) : min(min), max(max) {
    assert(min.width <= max.width && min.height <= max.height);
  }

  Constraints::Constraints(Size tightSize) : Constraints(tightSize,
    tightSize) {
    //
  }

  Constraints::Constraints(
    float minWidth,
    float minHeight,
    float maxWidth,
    float maxHeight)
    : Constraints(Size(minWidth, minHeight), Size(maxWidth, maxHeight)) {
    //
  }

  Constraints Constraints::tightenTo(Size size) const {
    return this->tightenTo(size.width, size.height);
  }

  Constraints Constraints::tightenTo(float width, float height) const {
    return Constraints(this->prefer(width, height));
  }

  Constraints Constraints::tightenToMax() const {
    return Constraints(this->max);
  }

  Constraints Constraints::tightenWidthToMin() const {
    return {this->min, {this->min.width, this->max.height}};
  }

  Constraints Constraints::tightenHeightToMin() const {
    return {this->min, {this->max.width, this->min.height}};
  }

  Constraints Constraints::tightenWidthToMax() const {
    return {{this->max.width, this->min.height}, this->max};
  }

  Constraints Constraints::tightenHeightToMax() const {
    return {{this->min.width, this->max.height}, this->max};
  }

  Constraints Constraints::tightenMainToMin(Axis axis) const {
    if (axis == Axis::X) {
      return {this->min, {this->min.width, this->max.height}};
    } else {
      return {this->min, {this->max.width, this->min.height}};
    }
  }

  Constraints Constraints::tightenMainToMax(Axis axis) const {
    if (axis == Axis::X) {
      return this->tightenWidthToMax();
    } else {
      return this->tightenHeightToMax();
    }
  }

  Constraints Constraints::tightenCrossToMin(Axis axis) const {
    if (axis == Axis::X) {
      return this->tightenHeightToMin();
    } else {
      return this->tightenWidthToMin();
    }
  }

  Constraints Constraints::tightenCrossToMax(Axis axis) const {
    if (axis == Axis::X) {
      return this->tightenHeightToMax();
    } else {
      return this->tightenWidthToMax();
    }
  }

  Constraints Constraints::shrinkTo(Size size) const {
    return this->shrinkTo(size.width, size.height);
  }

  Constraints Constraints::shrinkTo(float width, float height) const {
    return {
      this->max.width - width,
      this->max.height - height,
      ord::max(0.0f, this->min.width - width),
      ord::max(0.0f, this->min.height - height),
    };
  }

  Constraints Constraints::shrinkUnbounded(Size size) const {
    return this->shrinkUnbounded(size.width, size.height);
  }

  Constraints Constraints::shrinkUnbounded(float width,
    float height) const {
    float maxWidth = this->max.width;
    if (isUnbounded(maxWidth)) {
      maxWidth = ord::max(this->min.width, width);
    }
    float maxHeight = this->max.height;
    if (isUnbounded(maxHeight)) {
      maxHeight = ord::max(this->min.height, height);
    }
    return {this->min, {maxWidth, maxHeight}};
  }

  Constraints Constraints::shrinkUnboundedToZero() const {
    return this->shrinkUnbounded(0, 0);
  }

  Constraints Constraints::unboundedWidth() const {
    return {this->min, {UNBOUNDED, this->max.height}};
  }

  Constraints Constraints::unboundedHeight() const {
    return {this->min, {this->max.width, UNBOUNDED}};
  }

  Constraints Constraints::noMin() const {
    return {{0, 0}, this->max};
  }

  Constraints Constraints::rotate90() const {
    return {this->min.rotate90(), this->max.rotate90()};
  }

  Size Constraints::prefer(Size size) const {
    return this->prefer(size.width, size.height);
  }

  Size Constraints::prefer(float width, float height) const {
    return {
      ord::max(this->min.width, ord::min(this->max.width, width)),
      ord::max(this->min.height, ord::min(this->max.height, height)),
    };
  }

  Size Constraints::smallest() const {
    return {this->min};
  }

  Size Constraints::biggest() const {
    return {this->max};
  }

  bool Constraints::contains(Size size) const {
    return this->contains(size.width, size.height);
  }

  bool Constraints::contains(float width, float height) const {
    return width >= this->min.width && height >= this->min.height
           && width <= this->max.width && height <= this->max.height;
  }

  Constraints Constraints::operator&&(const Constraints& that) const {
    return {
      ord::max(this->min.width, that.min.width),
      ord::max(this->min.height, that.min.height),
      ord::min(this->max.width, that.max.width),
      ord::min(this->max.height, that.max.height),
    };
  }

  Rect::Rect(float x, float y, Size size)
    : Rect(x, y, size.width, size.height) {
    //
  }

  Rect::Rect(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {
    assert(width >= 0.0f && height >= 0.0f);
  }
}
