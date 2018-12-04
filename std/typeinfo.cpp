#include <iostream>
#include <typeinfo>

class A {
public:
  virtual ~A() {}
  virtual void m() = 0;
};

class B: public A {
public:
  void m() override {
    std::cout << "B.m\n";
  }
};

int main() {
  auto b = B();
  A& a = b;
  std::cout << "type=" << typeid(a).name() << std::endl;
  return 0;
}
