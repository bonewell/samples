#include <memory>
#include <iostream>

using namespace std;

[[nodiscard]]  // c++11
int func() {
  cout << "a\n";
  return 4;
}

int main() {
   auto x = func();
   func();  // warning
}