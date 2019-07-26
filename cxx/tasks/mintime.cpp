//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

long calc(const vector<long>& machines, long goal) {
    long n = machines.size();
    long index = 0;
    long limit_index = 0;
    long limit = machines[limit_index];
    unordered_map<long, long> times;
    long time = 0;
    for (long i = 1; i <= goal; ++i) {
        cout << "i=" << i << ", index=" << index << ", limit_index=" << limit_index << ", limit=" << limit << "\n";
        while ((times[index] + machines[index]) > limit && index <= limit_index) {
            index++;
            cout << "++\n";
        }

        times[index] += machines[index];
        if (times[index] > time) time = times[index];

        cout << "times[" << index << "]=" << times[index] << "\n";
        cout << "TIME=" << time << "\n\n";

        if (index == limit_index) {
            if (limit_index + 1 < n) {
                limit_index++;
            } else {
                limit_index = 0;
            }
            limit = times[limit_index] + machines[limit_index];
            index = 0;
        }
    }

    return time;
}

// Complete the minTime function below.
long minTime(vector<long> machines, long goal) {
    sort(begin(machines), end(machines));
    return calc(machines, goal);
}

int main() {
    //vector<long> m{2, 3};
    //long g = 5;

    //vector<long> m{1, 3, 4};
    //long g = 10;

    vector<long> m{4, 5, 6};
    long g = 12;
    cout << minTime(m, g) << "\n";
}
