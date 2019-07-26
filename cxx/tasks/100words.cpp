#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> top100(const vector<string>& words) {
    unordered_map<string, int> indexes;
    vector<pair<string, int>> counters(words.size());
    for (auto i = 0; i < words.size(); ++i) {
        const auto& w = words[i];
        if (indexes.find(w) == end(indexes)) {
            indexes[w] = i;
        }
        auto& p = counters[indexes[w]];
        p.first = w;
        p.second++;
    }

    constexpr int kTop = 100;
    int size = indexes.size();
    auto top = begin(counters) + min(kTop, size);
    partial_sort(begin(counters), top, end(counters),
    [](const auto& v1, const auto& v2){
        return v1.second > v2.second;
    });

    vector<string> res;
    for (auto it = begin(counters); it != top; ++it) {
        res.push_back(it->first);
    }

    return res;
}

int main() {
    vector<string> in{"word", "word", "ura", "word", "da", "da"};
    auto out = top100(in);
    for (const auto& w: out) {
        cout << w << "\n";
    }
    unordered_map<int, int> m;
    for (auto [k, v]: m) {}
}
