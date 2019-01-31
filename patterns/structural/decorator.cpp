#include <iostream>

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
        Transformation(Canvas& canvas):
            canvas_{canvas} {}
        void draw() override {
            canvas_.draw();
        }
    protected:
        Size size() override {
            return canvas_.size();
        }
        void size(Size size) override {
            canvas_.size(size);
        }
    private:
        Canvas& canvas_;
};

class Rotation: public Transformation {
    public:
        Rotation(Canvas& canvas, int angle):
            Transformation(canvas),
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
    Image i{{25, 62}};
    i.draw();

    Rotation r{i, 90};
    Canvas& c = r;
    c.draw();
    Rotation rr{r, 90};
    rr.draw();
}