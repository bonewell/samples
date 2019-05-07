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

void do_this(const A& a) {
  std::cout << "do_this type=" << typeid(a).name() << "\n";
}

int main() {
  B b;
  A& a = b;
  std::cout << "type=" << typeid(a).name() << std::endl;
  
  do_this(b);
  do_this(a);

  return 0;
}
