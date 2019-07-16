#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

long long count(std::vector<long> arr, long r) {
    int n = arr.size();

    // long max = arr[0];
    unordered_map<long, vector<int>> vs;
    for (int i = 0; i < n; ++i) {
        vs[arr[i]].push_back(i);
        // if (arr[i] > max) max = arr[i];
    }

    long long res = 0;
    for (const auto& p: vs) {
        long t1 = p.first;
        long t2 = t1 * r;
        long t3 = t2 * r;
        auto i1 = vs.find(t1);
        if (i1 == end(vs)) continue;
        const auto& t1s = i1->second;
        auto i2 = vs.find(t2);
        if (i2 == end(vs)) continue;
        const auto& t2s = i2->second;
        auto i3 = vs.find(t3);
        if (i3 == end(vs)) continue;
        const auto& t3s = i3->second;

        if (t1s.empty() || t2s.empty() || t3s.empty()) continue;
        for (int i: t1s) {
            if (i > n - 3) break;
            for (int j: t2s) {
                if (j <= i) break;
                for (int k: t3s) {
                    if (k <= j) break;
                    if (i < j && j < k) {
                        ++res;
                    }
                }
            }
        }
    }

    return res;
}

int main() {
    vector<long> v{1, 2, 2, 4};
//     cout << count(v, 2) << "\n";

    for (auto i : v) {
        if (i == 4) break;
        cout << i << " ";
    }
    cout << "\n";
    return 0;
}
