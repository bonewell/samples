#include <iostream>
#include "gsl/gsl"  // guideline support library is required

using namespace std;
using namespace gsl;

void put(owner<int*> i) {
  cout << *i << "\n";
  delete i;
}

owner<int*> get() {
  return new int(3);
}

template<class T>
class smartptr {
    owner<T*> p_;
public:
    smartptr(T* p): p_{p} {}
    smartptr() = default;
    smartptr(const smartptr&) = default;
    smartptr(smartptr&&) = default;
    smartptr& operator=(const smartptr&) = default;
    smartptr& operator=(smartptr&&) = default;
    ~smartptr() { delete p_; }
};

void func(smartptr<int> ptr) {
    auto p = ptr;
}

int main() {
  put(new int(8));
  
  int* x = new int(7);
  put(x);
  
  int* y = get();
  put(y);
  
  put(get());
  
  func(smartptr<int>{new int(5)});
}