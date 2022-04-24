#ifndef CGUI_GEOMETRY_H
#define CGUI_GEOMETRY_H

enum class Axis {
    X, Y,
};

enum class Axes {
    X, Y, XY,
};

typedef float Length;

extern const Length UNBOUNDED_LENGTH;

bool isLengthUnbounded(Length length);

struct Constraints;

struct Size {
    Length width;
    Length height;

    Size(Length width, Length height);

    [[nodiscard]]
    Size growBy(Size size) const;

    [[nodiscard]]
    Size growBy(Length width, Length height) const;

    [[nodiscard]]
    Size growToSatisfy(Constraints constraints) const;

    [[nodiscard]]
    Size shrinkBy(Size size) const;

    [[nodiscard]]
    Size shrinkBy(Length width, Length height) const;

    [[nodiscard]]
    Size shrinkToSatisfy(Constraints constraints) const;

    [[nodiscard]]
    Size rotate90() const;
};

struct Constraints {
    Size min;
    Size max;

    Constraints(Size min, Size max);

    explicit Constraints(Size tightSize);

    Constraints(Length minWidth, Length minHeight, Length maxWidth,
        Length maxHeight);

    [[nodiscard]]
    Constraints tightenTo(Size size) const;

    [[nodiscard]]
    Constraints tightenTo(Length width, Length height) const;

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
    Constraints tightenMainToMin(Axis axis) const;

    [[nodiscard]]
    Constraints tightenCrossToMin(Axis axis) const;

    [[nodiscard]]
    Constraints tightenMainToMax(Axis axis) const;

    [[nodiscard]]
    Constraints tightenCrossToMax(Axis axis) const;

    [[nodiscard]]
    Constraints shrinkTo(Size size) const;

    [[nodiscard]]
    Constraints shrinkTo(Length width, Length height) const;

    [[nodiscard]]
    Constraints shrinkUnbounded(Size size) const;

    [[nodiscard]]
    Constraints shrinkUnbounded(Length width, Length height) const;

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
    Size prefer(Size size) const;

    [[nodiscard]]
    Size prefer(Length width, Length height) const;

    [[nodiscard]]
    Size smallest() const;

    [[nodiscard]]
    Size biggest() const;

    [[nodiscard]]
    bool contains(Size size) const;

    [[nodiscard]]
    bool contains(Length width, Length height) const;

    Constraints operator&&(const Constraints&) const;
};

#endif
