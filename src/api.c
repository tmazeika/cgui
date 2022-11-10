#include <assert.h>

typedef struct {
  char* title;
} Window;

Window create_window(char* title) {
  Window w;
  w.title = title;
  return w;
}

void open_window(Window* w) {

}

void close_window(Window* w) {

}

typedef struct {
  float minWidth;
  float minHeight;
  float maxWidth;
  float maxHeight;
} Constraints;

typedef struct {
  float width;
  float height;
} Size;

Size minSize(Constraints* c) {
  Size s;
  s.width = c->minWidth;
  s.height = c->minHeight;
  return s;
}

Constraints grow(Constraints* c, float x, float y) {
  assert(c->maxWidth + x >= c->minWidth);
  assert(c->maxHeight + y >= c->minHeight);
  Constraints cpy = *c;
  cpy.maxWidth += x;
  cpy.maxHeight += y;
  return cpy;
}

typedef struct Widget {
  struct Widget* child;

  Size (* getSize)(struct Widget*, Constraints*);
} Widget;

Size getSizeOfChild(Widget* w, Constraints* c) {
  Widget* child = w->child;
  if (child) {
    return child->getSize(child, c);
  } else {
    return minSize(c);
  }
}

typedef struct {
  Widget widget;
  float topPad;
  float rightPad;
  float bottomPad;
  float leftPad;
} PaddedBox;

Size getPaddedBoxSize(Widget* w, Constraints* c0) {
  PaddedBox* pb = (PaddedBox*) w;
  Constraints c1 = grow(c0, -pb->leftPad - pb->rightPad,
    -pb->topPad - pb->bottomPad);
  return getSizeOfChild(&pb->widget, &c1);
}
