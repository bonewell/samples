#include <iostream>
#include <functional>

using namespace std;

template<class... Bs>
struct A: Bs... {
  using Bs::operator()...;
};

struct F1 {
    void operator()() {
        cout << "F1::operator()\n";
    }
};

struct F2 {
    void operator()() {
        cout << "F2::operator()\n";
    }
};

int main() {
  A<F1, F2> a;
  invoke(static_cast<F2>(a));
}