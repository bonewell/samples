#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

int main() {
  vector<unique_ptr<int>> v;
  v.emplace_back(new int(2));
  v.emplace_back(new int(4));
  v.emplace_back(new int(6));

  // here auto requires c++14
  for_each(begin(v), end(v), [](auto& i) { cout << *i << " "; });
  cout << endl;
}
