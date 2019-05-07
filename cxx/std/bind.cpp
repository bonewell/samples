#include <memory>
#include <iostream>

void callback(std::unique_ptr<int> x) {
  std::cout << *x << std::endl;
}

int main() {
  std::unique_ptr<int> ptr(new int(5)); 
  auto l = [ptr=std::move(ptr)]() { // c++14 is required
    std::cout << *ptr << std::endl;
  };
  l();
  return 0;
}
