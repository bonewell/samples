#include <iostream>

using namespace std;

int& print(int a) {
  cout << "a=" << a << "\n";
  return move(a);
}

int main() {
  //int x = 0, y = 2;
  int x = print(2) = print(5);
  cout << "x=" << x << "\n";// << ", y=" << y << "\n";
}
