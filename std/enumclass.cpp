#include <iostream>

using namespace std;

enum class A;

struct B {
    int x{0};
    void set(const A& a);
};

enum class A {
    one=1, two, three, four, five
};

A& operator ++(A& a) {
  return a = (a == A::five) ? A::one : static_cast<A>(static_cast<int>(a) + 1);
}

ostream& operator <<(ostream& out, A a) {
  return out << static_cast<int>(a);
}

void B::set(const A& a) {
  x = static_cast<int>(a);
}

int main() {
  auto a = A::three;
  ++a;
  cout << "a=" << a << "\n";
  
  B x;
  x.set(A::two);
  cout << "x.x=" << x.x << "\n";
}