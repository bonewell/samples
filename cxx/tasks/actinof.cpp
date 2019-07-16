#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

using History = vector<int>;

void replace(History& history, int old, int v) {
    if (old <= v) {
        auto r = std::lower_bound(begin(history), end(history), old);
        auto i = std::lower_bound(r, end(history), v);
        auto it = r;
        for (; it != i; ++it) {
            auto nit = it + 1;
            if (nit == i || nit == end(history)) {
                *it = v;
            } else {
                *it = *nit;
            }
        }
    } else {
        auto r = std::lower_bound(begin(history), end(history), old);
        auto i = std::lower_bound(begin(history), r, v);
        auto it = r;
        if (r == i) *r = v;
        for (; it != i; --it) {
            if (it == begin(history)) {
                *it = v;
            } else {
                *it = *(it - 1);
            }
        }
    }
}

int median(const History& history, int d) {
    copy(begin(history), end(history), ostream_iterator<int>{cerr, " "});
    cerr << "\n";
    int i = d / 2;
    if (d % 2 == 0) {
        cout << history[i-1] << "+" << history[i] << "=" << history[i-1] + history[i] << " ";
        return history[i-1] + history[i];
    } else {
        return history[i] * 2;
    }
}

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {
    int n = expenditure.size();

    History history{begin(expenditure), next(begin(expenditure), d)};
    sort(begin(history), end(history));

    int res = 0;
    for (int i = d; i < n; ++i) {
        auto m = median(history, d);
        if (expenditure[i] >= m) ++res;
        replace(history, expenditure[i - d], expenditure[i]);
    }
    return res;
}

int main() {
    int d = 10;
    ifstream ifs{"input01.txt"};
    vector<int> vec;

    copy(istream_iterator<int>{ifs}, istream_iterator<int>{}, back_inserter(vec));

    std::cout << activityNotifications(vec, d) << "\n";
}