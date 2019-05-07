#include <iostream>
#include <regex>  // c++11

using namespace std;

int main() {
  string str;
  getline(cin, str);

  regex patm {R"(\+7 \(\d{3}\) \d{3} \d{2} \d{2})"};
  cout << boolalpha << regex_match(str, patm) << "\n";

  regex pats {R"(^\+7 \(\d{3}\) \d{3} \d{2} \d{2}$)"};
  cout << boolalpha << regex_search(str, patm) << "\n";
  cout << boolalpha << regex_search(str, pats) << "\n";

  regex patr {R"(\+7)"};
  cout << regex_replace(str, patr, "8") << "\n";
}
