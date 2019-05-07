#include <iostream>
#include <string>

static int nullobj = 10;

class I {
 public:
  virtual void print() = 0;
};

class Null : public I {
 public:
  static Null& instance() {
    static Null self;
    return self;
  }
  void print() override {
    std::cout << "Null print\n";
  }
};

class Obj : public I {
 public:
  void print() override {
    std::cout << "Obj print\n";
  }
};

class P : public I {
 public:
  P(int x) : x_(x) {}
  static P& instance() {
    static P self(10);
    return self;
  }
  void print() override {
    std::cout << "P print " << x_ << "\n";
  }
  int x_;
};

class A {
 public:
  A() : ref(P::instance()) {}
  template<class T>
  void bind(T& x) {
    std::cout << "bind\n";
    ref = x;
  }
  void print() {
    ref.print();
  }
  I& ref;
};

int main()
{
    A a;
    a.print();
    P obj(5);
    a.bind(obj);
    a.print();

    P obj3(3);
    P& ref = obj3;
    ref.print();

    P obj7(7);
    ref = obj7;
    ref.print();
}
