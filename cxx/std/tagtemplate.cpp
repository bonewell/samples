#include <iostream>
#include <string>

using namespace std;

struct TagString {};
template<class T> struct Tagging {  using tag = TagString; };
template<typename T> using Tag = typename Tagging<T>::tag;
int funcImpl(string in, TagString) {
  return in.length();
}

struct TagInt {};
template<> struct Tagging<int> { using tag = TagInt; };
int funcImpl(int in, TagInt) {
  return in;
}

struct TagDouble {};
template<> struct Tagging<double>{ using tag = TagDouble; };
int funcImpl(double in, TagDouble) {
  return static_cast<int>(in);
}

template<typename T>
int func(T&& in) {
  return funcImpl(forward<T>(in), Tag<T>{});
}

int main() {
    cout << func(4) << "\n";
    cout << func(5.2) << "\n";
    cout << func("123") << "\n";
//     cout << func('a') << "\n"; compile error
}