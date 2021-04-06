#include <iostream>
#include <memory>

using namespace std;

// A.h
class A {
    protected:
        A() = default;
        void init() {
            f();
        }
    public:
        virtual void f() = 0;
        virtual ~A() = default;

        template<class T>
        static unique_ptr<T> create() {
            auto ptr = make_unique<T>();
            ptr->init();
            return ptr;
        }
};

// B.h and B.cpp
class B: public A {
    public:
        void f() override {
            cout << "B::f\n";
        }
};

int main() {
    auto b = A::create<B>();
    cout << typeid(b).name() << "\n";
}
