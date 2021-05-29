#include <iostream>
#include <unordered_set>

using namespace std;

int SQ(int x) {
    int s = 0;
    int m = 1;
    int d = 10;
    while (x > 0) {
        int p = x % d;
        x -= p;
        s += p / m;
        d *= 10;
        m *= 10;
    }
    int ss = s*s;
    return ss;
}

int findValue() {
    int n = 1000000;
    unordered_set<int> sv;
    for (int i = 1; i < n; ++i) {
        int m = (3 * i) / SQ(i);
        sv.insert(m);
    }
    for (int i = 1; i < n; ++i) {
        if (sv.find(i) == sv.end()) return i;
    }
    return n;
}

int main() {
    cout << findValue() << '\n';
    return 0;
}
