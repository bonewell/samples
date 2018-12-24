#include <algorithm>
#include <vector>
#include <random>  // c++11
#include <iostream>
#include <chrono>  // c++11
#include <execution>  // c++17 (compiller should support this feature)
#include <functional>

using namespace std;

int main() {
  default_random_engine generator;
  uniform_int_distribution<int> distribution(1,99999999);

  auto value = bind(distribution, generator);

  vector<int> v;
  for (auto i=0; i != 10000000; ++i) v.push_back(value());

  auto start = chrono::system_clock::now();
  sort(execution::seq, begin(v), end(v));
  auto end = chrono::system_clock::now();

  chrono::duration<double> elapsed_seconds = end - start;

  cout << "Time: " << elapsed_seconds.count() << "\n";
}
