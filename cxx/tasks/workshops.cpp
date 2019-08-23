//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <vector>

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

bool find_overlay(const Workshops* w, const vector<const Workshops*>& ws) {
    for (auto p: ws) {
      if (is_overlay(w, p)) return true;
    }
    return false;
}

int calc_max(const Available_Workshops* ptr, vector<const Workshops*>& ws) {
  for (int i = 0; i < ptr->n; ++i) {
      if (!find_overlay(&ptr->list[i], ws)) {
          ws.push_back(&ptr->list[i]);
      }
  }
  return ws.size();
}

void print(const unordered_map<int, unordered_set<int>>& ctrs) {
    for (const auto& p: ctrs) {
        cout << p.first << " -> ";
        for (auto x: p.second) {
            cout << x << ", ";
        }
        cout << '\n';
    }
}

int calc(unordered_map<int, unordered_set<int>>& ctrs)
{
    int res = 0;
    while (ctrs.size() > 0) {
//         print(ctrs);
        auto maxi = max_element(begin(ctrs), end(ctrs),
            [](const auto& p1, const auto& p2) {
                return p1.second.size() < p2.second.size();
            });
        for (auto it = begin(ctrs); it != end(ctrs);) {
            it->second.erase(maxi->first);
            if (it->second.empty()) {
                it = ctrs.erase(it);
            }
            else it++;
        }
        ctrs.erase(maxi);
        res++;
//         cout << "---\n";
    }
    return res;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
/*    unordered_map<int, unordered_set<int>> count;
    for (int i = 0; i < ptr->n; ++i) {
        for (int j = 0; j < ptr->n; ++j) {
            if (i != j) {
                if (is_overlay(&ptr->list[i], &ptr->list[j])) {
                    count[i].insert(j);
                }
            }
        }
    }
    return ptr->n - calc(count);
*/
    vector<const Workshops*> ws;
    return calc_max(ptr, ws);
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
