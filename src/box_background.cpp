#include <cgui/box.h>

namespace cgui {
  class BackgroundBox : public Box {
  private:
    std::unique_ptr<Box> child;
  public:
    const Color color;

    BackgroundBox(const Color& color, std::unique_ptr<Box> child)
      : color(color), child(std::move(child)) {
      //
    }

    ~BackgroundBox() override = default;

    Size getSize(const Constraints& c) override {
      if (!this->child) {
        return c.smallest();
      }
      return this->child->getSize(c);
    }

    void render(const Canvas& canvas, const Rect& rect) const override {
      canvas.fillRect(rect, this->color);
      if (this->child) {
        this->child->render(canvas, rect);
      }
    }
  };

  std::unique_ptr<Box> createBackgroundBox(Color color,
    std::unique_ptr<Box> child) {
    return std::make_unique<BackgroundBox>(color, std::move(child));
  }
}
