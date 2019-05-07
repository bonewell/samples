#include <iostream>
#include <memory>

struct Size {
    int width;
    int height;
};
std::ostream& operator<<(std::ostream& out, const Size& size) {
    return out << size.width << "x" << size.height;
}

class Canvas {
    public:
        virtual void draw() = 0;
        virtual Size size() = 0;
        virtual void size(Size size) = 0;
        virtual ~Canvas() = default;
};
using CanvasPtr = std::unique_ptr<Canvas>;

class Image: public Canvas {
    public:
        Image(Size size): size_{size} {}
        void draw() override {
            std::cout << "draw image " << size_ << "\n";
        }
        Size size() override {
            return size_;
        }
        void size(Size size) override {
            size_ = size;
        }
    private:
        Size size_;
};

class Transformation: public Canvas {
    public:
        Transformation(CanvasPtr canvas):
            canvas_{std::move(canvas)} {}
        void draw() override {
            canvas_->draw();
        }
    protected:
        Size size() override {
            return canvas_->size();
        }
        void size(Size size) override {
            canvas_->size(size);
        }
    private:
        CanvasPtr canvas_;
};

class Rotation: public Transformation {
    public:
        Rotation(CanvasPtr canvas, int angle):
            Transformation{std::move(canvas)},
            angle_{angle} {}
        void draw() override {
            std::cout << "rotate image " << angle_ << "\n";
            auto s = size();
            size({s.height, s.width});
            Transformation::draw();
        }
    private:
        int angle_{0};
};

int main() {
    CanvasPtr c = std::make_unique<Image>(Size{25, 62});
    c->draw();

    c = std::make_unique<Rotation>(std::move(c), 90);
    c->draw();

    c = std::make_unique<Rotation>(std::move(c), 90);
    c->draw();
}