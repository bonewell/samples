#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

string isValid(string s) {
    unordered_map<char, int> cn;
    for (auto c: s)
        cn[c]++;

    unordered_map<int, int> cnn;
    for (const auto& p: cn) {
        cout << p.first << "=" << p.second << "\n";
        cnn[p.second]++;
    }

    for (const auto& p: cnn) {
        cout << p.first << "-" << p.second << "\n";
    }

    auto len = cnn.size();
    if (len == 1) return "YES";
    if (len == 2) {
        auto it = begin(cnn);
        auto c1 = it->first;
        auto v1 = it->second;
        advance(it, 1);
        auto c2 = it->first;
        auto v2 = it->second;
        if ((c1 == 1 && v1 == 1) || (c2 == 1 && v2 == 1)) return "YES";
        if (abs(c2 - c1) == 1 && (v1 == 1 || v2 == 1)) return "YES";
    }
    return "NO";
}

int main() {
    ifstream ifs{"input01.txt"};
    string str;
    ifs >> str;
    cout << isValid(str) << "\n";
}