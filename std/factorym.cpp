#include <iostream>
#include <memory>

using namespace std;

class A {
    protected:
        A() = default;
        void init() {
            f();
        }
    public:
        virtual void f() = 0;

        template<class T>
        static unique_ptr<T> create() {
            auto ptr = make_unique<T>();
            ptr->init();
            return ptr;
        }
};

class B: public A {
    public:
        void f() override {
            cout << "B::f\n";
        }
};

int main() {
    auto b = B::create<B>();
    cout << typeid(b).name() << "\n";
}