#include <unistd.h>
#include <cstdlib>
#include <iostream>

void before_exit() {
  std::cout << "Atexit\n";
}

int main() {
  std::cout << "Start\n";
  atexit(before_exit);
  sleep(5);
  std::cout << "Exit\n";
  return 0;
}
