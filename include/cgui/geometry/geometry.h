#pragma once

namespace cgui {
  enum class Axis {
    X, Y,
  };

  enum class Axes {
    X, Y, XY,
  };

  extern const float UNBOUNDED;

  bool isUnbounded(float);

  struct Constraints;

  struct Size {
    const float width;
    const float height;

    Size(float width, float height);

    [[nodiscard]]
    Size growBy(Size) const;

    [[nodiscard]]
    Size growBy(float width, float height) const;

    [[nodiscard]]
    Size growToSatisfy(Constraints) const;

    [[nodiscard]]
    Size shrinkBy(Size) const;

    [[nodiscard]]
    Size shrinkBy(float width, float height) const;

    [[nodiscard]]
    Size shrinkToSatisfy(Constraints) const;

    [[nodiscard]]
    Size rotate90() const;
  };

  struct Constraints {
    const Size min;
    const Size max;

    Constraints(Size min, Size max);

    explicit Constraints(Size tightSize);

    Constraints(float minWidth, float minHeight, float maxWidth,
      float maxHeight);

    [[nodiscard]]
    Constraints tightenTo(Size) const;

    [[nodiscard]]
    Constraints tightenTo(float width, float height) const;

    [[nodiscard]]
    Constraints tightenToMax() const;

    [[nodiscard]]
    Constraints tightenWidthToMin() const;

    [[nodiscard]]
    Constraints tightenHeightToMin() const;

    [[nodiscard]]
    Constraints tightenWidthToMax() const;

    [[nodiscard]]
    Constraints tightenHeightToMax() const;

    [[nodiscard]]
    Constraints tightenMainToMin(Axis) const;

    [[nodiscard]]
    Constraints tightenCrossToMin(Axis) const;

    [[nodiscard]]
    Constraints tightenMainToMax(Axis) const;

    [[nodiscard]]
    Constraints tightenCrossToMax(Axis) const;

    [[nodiscard]]
    Constraints shrinkTo(Size) const;

    [[nodiscard]]
    Constraints shrinkTo(float width, float height) const;

    [[nodiscard]]
    Constraints shrinkUnbounded(Size) const;

    [[nodiscard]]
    Constraints shrinkUnbounded(float width, float height) const;

    [[nodiscard]]
    Constraints shrinkUnboundedToZero() const;

    [[nodiscard]]
    Constraints unboundedWidth() const;

    [[nodiscard]]
    Constraints unboundedHeight() const;

    [[nodiscard]]
    Constraints noMin() const;

    [[nodiscard]]
    Constraints rotate90() const;

    [[nodiscard]]
    Size prefer(Size) const;

    [[nodiscard]]
    Size prefer(float width, float height) const;

    [[nodiscard]]
    Size smallest() const;

    [[nodiscard]]
    Size biggest() const;

    [[nodiscard]]
    bool contains(Size) const;

    [[nodiscard]]
    bool contains(float width, float height) const;

    Constraints operator&&(const Constraints&) const;
  };

  struct Rect {
    const float x;
    const float y;
    const float width;
    const float height;

    Rect(float x, float y, Size size);

    Rect(float x, float y, float width, float height);
  };
}
