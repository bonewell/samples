//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//Define the structs Workshops and Available_Workshops.
struct Workshops {
    Workshops() : start_time{0}, duration{0}, end_time{0} {}
    Workshops(int s, int d, int e) : start_time{s}, duration{d}, end_time{e} {}
    int start_time;
    int duration;
    int end_time;
};

struct Available_Workshops {
    int n;
    vector<Workshops> list;
};

//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops* initialize(int start_time[], int duration[], int n)
{
    Available_Workshops* ptr = new Available_Workshops();
    ptr->n = n;
    for (int i = 0; i < n; ++i) {
        ptr->list.emplace_back(start_time[i], duration[i], start_time[i] + duration[i]);
    }
    return ptr;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    sort(begin(ptr->list), end(ptr->list), [](const auto& w1, const auto& w2) {
        return w1.end_time < w2.end_time;
    });
    int maxi = 0;
    int curend = 0;
    for (const auto& w: ptr->list) {
        if (w.start_time >= curend) {
            maxi++;
            curend = w.end_time;
        }
    }
    return maxi;
}

int main(int argc, char *argv[]) {
    constexpr int n = 6; // number of workshops
    // create arrays of unknown size n
    int start_time[n] = {1, 3, 0, 5, 5, 8};
    int duration[n] = {1, 1, 6, 2, 4, 1};

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
