#include <iostream>

class A {
public:
    A() {
        std::cout << "default ctr\n";
    }
    A(const A& o) {
        std::cout << "copy ctr\n";
    }
    A(const A&& o) {
        std::cout << "move ctr\n";
    }
    A&& m1() {
        std::cout << "&&m1\n";
        return std::move(*this);
    }
    A&& m2() {
        std::cout << "&&m2\n";
        return std::move(*this);
    }
    void cm() const {
        std::cout << "cm\n";
    }
};

class B {
public:
    B() {
        std::cout << "default ctr\n";
    }
    B(const B& o) {
        std::cout << "copy ctr\n";
    }
    B(const B&& o) {
        std::cout << "move ctr\n";
    }
    B& m1() {
        std::cout << "&m1\n";
        return *this;
    }
    B& m2() {
        std::cout << "&m2\n";
        return *this;
    }
    void cm() const {
        std::cout << "cm\n";
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    auto a = A().m1().m2();
    a.cm();

    auto b = std::move(B().m1().m2());
    b.cm();

    const auto& r = 5;
    std::cout << r << std::endl;
    return 0;
}
