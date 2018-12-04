#include <set>
#include <iostream>

int main() {
  std::set<int> s{1, 2, 3, 4, 5};
  for (const auto& i: s) {
    std::cout << i << std::endl;
//    s.erase(i);
    s.clear();
  }
  return 0;
}
