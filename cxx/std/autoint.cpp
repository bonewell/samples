#include <typeinfo>
#include <iostream>

int main() {
  auto i{7};
  std::cout << typeid(i).name() << "\n";
}

