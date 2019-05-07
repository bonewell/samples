#include <iostream>
#include <typeinfo>

using namespace std;

template<typename T>
class Optional {
public:
  using value_type = T;

  Optional(): value_{}, presented_{false} {}
  Optional(T v): value_{v}, presented_{true} {}
  auto& operator =(T v) {
    value_ = v;
    presented_ = true;
    return *this;
  }

  operator bool() {
    return presented_;
  }
  const T& operator *() const {
    return value_;
  }

private:
  T value_;
  bool presented_;
};

int main() {
  Optional o1{4.5}; // C++17 is required for deduction
  if (o1) {
    cout << "o1=" << *o1 << ",type=" << typeid(*o1).name() << "\n";
  } else {
    cout << "o1 is not presented\n";
  }

  Optional<int> o2;
  if (!o2) {
    cout << "o2 is not presented\n";
  }
  o2 = 7;
  if (o2)
    cout << "o1=" << *o2 << ",type=" << typeid(*o2).name() << "\n";

  Optional o3 = "abc";
  if (o3) cout << "o3=" << *o3 << ",type=" << typeid(*o3).name() << "\n";

  Optional o4 = "abc"s;
  cout << "o4=" << *o4 << ",type=" << typeid(*o4).name() << "\n";
}
