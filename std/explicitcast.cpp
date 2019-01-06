#include <algorithm>
#include <iostream>
#include <cstddef>
#include "gsl/gsl"  // guideline support library is required

using namespace std;
using namespace gsl;

struct A {
  int x;
};

struct B {
    short x;
    explicit operator A() {
      cout << "B::operator A()\n";
      return {x};
    }
    
    explicit operator span<byte>() {  // std::byte is c++17
        cout << "B::operator byte()\n";
        auto bs = span(reinterpret_cast<byte*>(&x), sizeof(x));
        reverse(begin(bs), end(bs));
        return bs;
    }
};

int main() {
    B b = {5};
    auto a = static_cast<A>(b);
    
    auto bs = static_cast<span<byte>>(b);
    for (auto c: bs)
        cout << to_integer<int>(c);
    cout << "\n";
}