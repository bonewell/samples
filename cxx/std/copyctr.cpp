#include <iostream>

using namespace std;

class A {
  int* p_;
  public:
    A(int* p): p_(p) {}
    A(A& a) {
      p_ = a.p_;
      a.p_ = 0;
    }
    A(const A& a): p_(0) {}
    A(volatile A& a): p_(0) {}
    A(const volatile A& a): p_(0) {}
    void print() {
      cout << p_ << "\n";
      if (p_)
        cout << *p_ << "\n";
    }
    ~A() {
      cout << "dtr\n";
      delete p_;
    }
};

int main() {
  A a(new int(3));
  a.print();
  A b(a);
  b.print();
  a.print();
  const A c(a);
  A d(c);
  volatile A e(a);
  A f(e);
  const volatile A g(a);
  A i(g);
}
