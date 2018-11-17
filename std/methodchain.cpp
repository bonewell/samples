#include <iostream>

class A {
private:
    std::string text;
public:
    A() : text{"My Text"} {
        std::cout << "A default ctr\n";
    }
    A(const A& o) {
        text = o.text;
        std::cout << "A copy ctr\n";
    }
    A(A&& o) {
        text = std::move(o.text);
        std::cout << "A move ctr\n";
    }
    A& m1() & {
        std::cout << "A.&m1\n";
        return *this;
    }
    A&& m1() && {
        std::cout << "A.&&m1\n";
        return std::move(*this);
    }
    A&& m2() {
        std::cout << "A.&&m2\n";
        return std::move(*this);
    }
    void cm() const {
        std::cout << "A.cm:" << text << std::endl;
    }
};

class B {
public:
    B() {
        std::cout << "B default ctr\n";
    }
    B(const B& o) {
        std::cout << "B copy ctr\n";
    }
    B(B&& o) {
        std::cout << "B move ctr\n";
    }
    B& m1() {
        std::cout << "B.&m1\n";
        return *this;
    }
    B& m2() {
        std::cout << "B.&m2\n";
        return *this;
    }
    void cm() const {
        std::cout << "B.cm\n";
    }
};

class C {
public:
    C() {
        std::cout << "C default ctr\n";
    }
    C(const C& o) {
        std::cout << "C copy ctr\n";
    }
    C(C&& o) {
        std::cout << "C move ctr\n";
    }
    C m1() {
        std::cout << "C.m1\n";
        return std::move(*this);
    }
    void cm() const {
        std::cout << "C.cm\n";
    }
};

int main() {
    auto a = A().m1().m2();
    a.cm();

    auto a1 = A();
    auto a2 = a1.m1();
    a1.cm();
    auto a3 = std::move(a2);
    a2.cm();
    a3.cm();

    auto b = std::move(B().m1().m2());
    b.cm();

    auto c = C().m1();
    c.cm();

    auto c1 = C();
    auto c2 = c1.m1().m1();
    c1.cm();

    return 0;
}
