#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

constexpr long long factorial(int n) {
  assert(n > 0);
  auto res = 1;
  for (auto i = 1; i <= n; ++i) {
    res *= i;
  }
  return res;
}

template<typename T, typename U = int>
constexpr vector<T> fibonacci(U n) {
    vector<T> res(n);
    pair<T, T> p{0, 1};
    for (auto i = 0; i != n; ++i) {
      p = {p.second, p.first + p.second};
      res[i] = p.first;
    }
    return res;
}

template<typename T>
constexpr vector<T> fibonacci_less(T n) {
  vector<T> res;
  for (pair<T, T> p{0,1}; p.second < n; p = { p.second, p.first + p.second}) {
    res.push_back(p.second);
  }
  return res;
}

int main() {
    cout << "11! = " << factorial(11) << "\n";
    
    using FibonacciNumber = unsigned long long;
    auto fibs = fibonacci<FibonacciNumber>(10);
    copy(begin(fibs), end(fibs), ostream_iterator<FibonacciNumber>(cout, " "));
    cout << "\n";
    
    auto fibles = fibonacci_less(400'000'000'000ull);
    copy(begin(fibles), end(fibles), ostream_iterator<decltype(fibles)::value_type>(cout, " "));
    cout << sizeof(decltype(fibles)::value_type) << "\n";
}
