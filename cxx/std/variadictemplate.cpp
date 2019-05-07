#include <iostream>
#include <vector>

using namespace std;

/*
 * until c++17
 *
void print() {
  cout << endl;
}
*/

template<typename T, typename ... Tail>  // c++11
void print(T head, Tail... tail) {
  cout << head << ' ';
  if constexpr(sizeof...(tail) > 0)  // c++17
    print(tail...);
  else
    cout << endl;
}

template<typename ... P>
void print_short(P... pack) {
  (cout << ... << pack) << endl; // c++17
}

int main() {
  print(1, 2.3, "string");
  print_short('a', 4, 5.6);
}
