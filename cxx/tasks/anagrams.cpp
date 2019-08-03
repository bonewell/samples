//usr/bin/clang++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    string s1;
    string s2;

    getline(cin, s1);
    getline(cin, s2);

	multiset<string::value_type> ss1{begin(s1), end(s1)};
    multiset<string::value_type> ss2{begin(s2), end(s2)};

    cout << (ss1 == ss2);
}