//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit
#include <iostream>
#include <vector>
#include <set>

using namespace std;

long triplets(vector<int> a, vector<int> b, vector<int> c) {
    set<int> bs;
    for (int x: b) {
        bs.insert(x);
    }

    set<int> as;
    for (int x: a) {
        as.insert(x);
    }

    set<int> cs;
    for (int x: c) {
        cs.insert(x);
    }

    long res = 0;
    long ab = 0;
    long cb = 0;
    auto ai = begin(as);
    auto ci = begin(cs);
    for (int x: bs) {
        while (ai != end(as)) {
            if (*ai <= x) {
                ab++;
                ai++;
            } else {
                break;
            }
        }
        while (ci != end(cs)) {
            if (*ci <= x) {
                cb++;
                ci++;
            } else {
                break;
            }
        }
        cout << "ab=" << ab << ", cb=" << cb << "\n";
        res += ab * cb;
    }
    return res;
}

int main() {
    vector<int> a{1, 3, 5, 7};
    vector<int> b{5, 7, 9};
    vector<int> c{7, 9, 11, 13};
    cout << triplets(a, b, c) << "\n";
}
