//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit
#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
struct Workshops {
    int start_time;
    int duration;
    int end_time;
};

struct Available_Workshops {
    int n;
    Workshops* list;
};

//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops* initialize(int start_time[], int duration[], int n)
{
    Available_Workshops* ptr = new Available_Workshops();
    ptr->n = n;
    ptr->list = new Workshops[n];
    for (int i = 0; i < n; ++i) {
        ptr->list[i].start_time = start_time[i];
        ptr->list[i].duration = duration[i];
        ptr->list[i].end_time = start_time[i] + duration[i];
    }
    return ptr;
}

bool is_overlay(const Workshops* p1, const Workshops* p2) {
    return !((p1->end_time <= p2->start_time) ||
        (p2->end_time <= p1->start_time));
}

int calc(vector<const Workshops*>& vec)
{
    unordered_map<int, int> count;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec.size(); ++j) {
            if (i != j) {
                if (is_overlay(vec[i], vec[j])) count[i]++;
            }
        }
    }
    int res = 0;
    auto maxi = max_element(begin(count), end(count),
        [](const auto& p1, const auto& p2) {
            return p1.second < p2.second;
    });
    if (maxi->second == 0) return vec.size();
    vec.erase(begin(vec) + maxi->first);
    return calc(vec);
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    vector<const Workshops*> vec;
    for (int i = 0; i < ptr->n; ++i) {
        vec.push_back(&ptr->list[i]);
    }
    return calc(vec);
}

int main(int argc, char *argv[]) {
