#include <iostream>

int main() try {
  try {
    try {
       throw "1";
    } catch (const char* e) {
       std::cout << e << "\n";
       throw "2";
    }
  } catch (const char* e) {
    std::cout << e << "\n";
    throw "3";
  }
}
catch (const char* e) {
  std::cout << e << "\n";
}
