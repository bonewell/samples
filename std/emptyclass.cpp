#include <utility>
#include <iostream>

using namespace std;

class A {
public:
  A(int x) {}
//  A() = default; //{ cout << "A()\n"; } //= default;
//  A(const A&) = delete; //{ cout << "A(constA&)\n"; } // << = default;
//  A(A&&) = default; //{ cout << "A(A&&)\n"; }
//  A& operator=(const A&) = default; //{ cout << "A& operator=(const A&)\n"; return *this; }
//  A& operator=(A&&) = default; //{ cout << "A& operator=(A&&)\n"; return *this; }
//  ~A() = default; //{ cout << "~A()\n"; }
};

int main() {
  A a(4);
  A aa(a);
  A aaa(move(a));
  A a4 = aa;
  A a5 = move(aa);
  a4 = a;
  a5 = move(a);
}

