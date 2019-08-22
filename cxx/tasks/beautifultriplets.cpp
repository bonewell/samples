//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Complete the beautifulTriplets function below.
int beautifulTriplets(int d, vector<int> arr) {
    unordered_map<int, int> cts;

    for (int x: arr) cts[x]++;

    int res = 0;
    for (const auto& p: cts) {
        res += p.second * cts[p.first + d] * cts[p.first + (2*d)];
    }
    return res;
}

int main() {
    cout << beautifulTriplets(3, {1, 6, 7, 7, 8, 10, 12, 13, 14, 19}) << "\n";
}
