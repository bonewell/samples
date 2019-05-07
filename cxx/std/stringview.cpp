#include <iostream>
#include <string>
#include <string_view> // c++17 is required

using namespace std;

bool match(string_view a, string_view b) {
  return a == b;
}

int main() {
  auto res = match("Bone", "BoneWell"s);
  cout << boolalpha << res << endl;
  res = match("Bone"sv, "BoneWell"s);
  cout << boolalpha << res << endl;
  string b = "BoneWell";
  res = match({&b[4], 4}, "Well");
  cout << boolalpha << res << endl;
}
