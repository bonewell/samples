#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

void print(int x) {
  cout << x << " ";
}

int main() {
  vector<unique_ptr<int>> v;
  v.emplace_back(new int(2));
  v.emplace_back(new int(4));
  v.emplace_back(new int(6));

  // here auto requires c++14
  for_each(begin(v), end(v), [](auto& i) { print(*i); });
  cout << endl;
  
  vector<int> vi{1, 2, 3};
  for_each(begin(vi), end(vi), [](auto&& i) { print(forward<decltype(i)>(i)); });
  cout << endl;
}
