#include <iostream>

using namespace std;

int str_len(char* str) {
    char* p = str;
    while (p != 0 && *p++ != '\0') { }
    return p - str - 1;
}

int main() {
  cout << str_len("abc") << '\n';
  cout << str_len("") << '\n';
  cout << str_len(nullptr) << '\n';
}
