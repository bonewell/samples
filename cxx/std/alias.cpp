#include <vector>
#include <list>
#include <iostream>
#include <string>

using namespace std;

template<typename F, typename S>
struct Pair {
  using first_type = F;
  using second_type = S;
  
  F first;
  S second;
};

template<typename P>
using Key_type = typename P::first_type; // C++11 is required

template<typename P>
auto get_key(const P& p) { // C++14 is required or tail -> Key_type<P> for C++11
  Key_type<P> y = p.first;
  return y;
}

template<typename Value>
using Int_pair = Pair<int, Value>;

int main() {
  Pair<int, double> x;
  x.first = 1; x.second = 2;
  auto y = get_key(x);
  cout << typeid(y).name() << "\n";

  Int_pair<string> s;
}
