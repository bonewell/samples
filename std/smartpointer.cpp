#include <type_traits>
#include <iostream>

template<typename T>
class SmartPointer {
  T* v_;
 public:
  SmartPointer(T* v): v_(v) {}
  T& operator*() {
    return *v_;
  }
  std::enable_if_t<std::is_class_v<T>,T*> operator->() {
    return v_;
  }
};

struct A {
  void log() {
    std::cout << "log\n";
  }
};

int main() {
  SmartPointer a{new A()};
  a->log();

  // SmartPointer i{new int(3)}; not build
}
