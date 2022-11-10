#include <cgui/sized.h>
#include <memory>

namespace cgui {
  class SizedBox : public Box {
  private:
    std::unique_ptr<Box> child;
  public:
    const float width;
    const float height;

    SizedBox(float width, float height, std::unique_ptr<Box> child)
      : width(width), height(height), child(std::move(child)) {
    }

    ~SizedBox() override = default;

    Size getSize(const Constraints& c) override {
      if (!this->child) {
        return c.prefer(this->width, this->height);
      }
      return this->child->getSize(c.tightenTo(this->width, this->height));
    }

    void render(const Canvas& canvas, const Rect& rect) const override {
      if (this->child) {
        this->child->render(canvas, rect);
      }
    }
  };

  std::unique_ptr<Box> createSizedBox(float width, float height,
    std::unique_ptr<Box> child) {
    return std::make_unique<SizedBox>(width, height, std::move(child));
  }

  std::unique_ptr<Box> createSizedBox(Size size, std::unique_ptr<Box> child) {
    return createSizedBox(size.width, size.height, std::move(child));
  }
}
