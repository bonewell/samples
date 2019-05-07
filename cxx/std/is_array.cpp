#include <type_traits>
#include <iostream>

int main() {
  std::cout << std::boolalpha;
  std::cout << "is_array:\n";
  std::cout << "const char*: " << std::is_array<const char*>::value << std::endl;
  std::cout << "const char[]: " << std::is_array<const char[]>::value << std::endl;
  return 0;
}
