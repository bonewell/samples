#include <iostream>

using namespace std;

template<typename F, typename... Args>
void invoke(F f, Args&&... x) {
  f(forward<Args>(x)...);
}

void fr(int& x) {
  cout << x << "\n";
  x = 3;
}

void f(int&& x) {
  cout << x << "\n";
};

int main() {
  int x = 5;
  invoke(fr, x);
  invoke(f, move(x));
}