#include <type_traits>
#include <iostream>

using namespace std;

template<typename T>
class SmartPointer {
  T* v_;
 public:
  SmartPointer(T* v): v_(v) {}
  T& operator*() {
    return *v_;
  }
  enable_if_t<is_class_v<T>,T*> operator->() {
    return v_;
  }
};

struct A {
  void log() {
    cout << "log\n";
  }
};

int main() {
  SmartPointer a{new A()};
  a->log();
  
  cout << sizeof(a) << "\n";
  auto p = new A();
  cout << sizeof(p) << "\n";
  delete p;
  cout << sizeof(nullptr) << "\n";

  // SmartPointer i{new int(3)};  // not build
}
