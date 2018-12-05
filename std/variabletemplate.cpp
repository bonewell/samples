#include <iostream>
#include <vector>

using namespace std;

template<typename T>
constexpr T sum(T a, T b) {
  return a + b;
}

// C++14 is required
// It should be outside of function
template <class T>
  constexpr T value = sum(1, 2); // = 3;

template <class T>
  T variable(5); // = sum(2, 3);  // = 5;

int main() {
  auto v = 2 * value<int>;
  cout << v << "\n";

  auto var = 3 * variable<double>;
  cout << var << "\n";

  auto vec = variable<vector<int>>;
  cout << "size=" << vec.size() << "\n";
}
