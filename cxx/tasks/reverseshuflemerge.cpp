#include <iostream>
#include <list>
#include <unordered_map>
// #include <iterator>
#include <set>
#include <utility>
#include <string>

using namespace std;

// list<string> shuffle(string const& A) {
//     if (A.length() == 1) return {A};
//     list<string> res;
//     for (auto i = 0; i < A.length(); ++i) {
//         auto a = A; a.erase(i, 1);
//         for (auto const& s: shuffle(a)) res.push_back(A[i] + s);
//     }
//     return res;
// }

// bool find(string const& s, string const& a) {
//     auto si = crbegin(s);
//     auto ai = crbegin(a);
//     while (ai != crend(a) && si != crend(s)) {
//         if (*ai == *si) ++ai;
//         ++si;
//     }
//     return ai == crend(a);
// }

// Complete the reverseShuffleMerge function below.
// string reverseShuffleMerge(string s) {
//     reverse(begin(s), end(s));
//     unordered_map<char, int> counters;
//     string A;
//     for (char c: s) {
//         if (counters[c] % 2 == 0) {
//             A += c;
//         }
//         ++counters[c];
//     }
//     sort(begin(A), end(A));

//     for (string const& a: shuffle(A)) {
//         cout << a << '\n';
//         if (find(s, a)) return a;
//     }

//     return "not found";
// }

ostream& operator<<(ostream& o, multiset<char> a) {
    copy(a.begin(), a.end(), ostream_iterator<char>(o, ","));
    return o;
}

pair<string, int> calc(string s, multiset<char> a) {
    cout << "s=" << s << ", a=" << a << '\n';
    if (a.empty() || s.empty()) return make_pair("", 0);
    list<pair<string, int>> lp;
    auto len = s.length() - a.size();
    for (int i = 0; i <= len; ++i) { // do we need it?
        cout << "ib=" << i << '\n';
        multiset<char> ca{a.begin(), a.end()};
        auto it = ca.find(s[i]);
        if (it != ca.end()) {
            ca.erase(it);
            auto p = calc(s.substr(i+1), ca);
            p.first += s[i];
            p.second += int(s[i]) * int(pow(10, a.size()));
            lp.push_back(p);
        }
        cout << "ie=" << i << '\n';
    }
    auto it = min_element(lp.begin(), lp.end());
    return (it != lp.end()) ? (*it) : make_pair("", 0);
}

string reverseShuffleMerge(string s) {
    unordered_map<char, int> counters;
    string as;
    for (char c: s) {
        if (counters[c] % 2 == 0) as += c;
        ++counters[c];
    }
    multiset<char> a{as.begin(), as.end()};
    return calc(s, a).first;
}

int main()
{
    // string s = "eggegg"; // egg
    // string s = "abcdefgabcdefg"; // agfedcb
    string s = "bdabaceadaedaaaeaecdeadababdbeaeeacacaba"; // aaaaaabaaceededecbdb

    string result = reverseShuffleMerge(s);

    cout << '\n' << result << "\n";

    return 0;
}
