#include "cgui/box/box.h"
#include "cgui/geometry/geometry.h"
#include <memory>
#include <string>

namespace cgui {
  class TextBox : public Box {
  public:
    const std::string text;

    explicit TextBox(std::string text) : text(std::move(text)) {
      //
    }

    Size getSize(const Constraints& c) override {
      // TODO
      return {0, 0};
    }

    void render(const Canvas& canvas, const Rect& rect) const override {
      // TODO
    }
  };

  std::unique_ptr<Box> createTextBox(std::string text) {
    return std::make_unique<TextBox>(std::move(text));
  }
}
