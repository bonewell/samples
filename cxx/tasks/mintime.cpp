//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

long total(const vector<long>& machines, long goal, long day) {
    long ttl = 0;
    for (long p: machines) {
        ttl += day / p;
    }
    return ttl;
}

long calc(const vector<long>& machines, long goal) {
    auto [mini, maxi] = minmax_element(begin(machines), end(machines));
//    cout << "mini=" << *mini << ", maxi=" << *maxi << "\n";
    long mindays = (goal / machines.size()) * (*mini);
    long maxdays = (goal / machines.size() + 1) * (*maxi);

    while (mindays < maxdays) {
//        cout << "mindays=" << mindays << ", maxdays=" << maxdays << "\n";
        long days = (mindays + maxdays) / 2;
//        cout << "days=" << days << "\n";
        long ttl = total(machines, goal, days);
//        cout << "ttl=" << ttl << "\n";
        if (ttl >= goal) {
            maxdays = days;
        } else {
            mindays = days + 1;
        }
    }

    return mindays;
}

// Complete the minTime function below.
long minTime(vector<long> machines, long goal) {
    return calc(machines, goal);
}

int main() {
    // vector<long> m{2, 3};
    // long g = 5;
    cout << minTime({2, 3}, 5) << "\n";

    // vector<long> m{1, 3, 4};
    // long g = 10;
    cout << minTime({1, 3, 4}, 10) << "\n";

    // vector<long> m{4, 5, 6};
    // long g = 12;
    cout << minTime({4, 5, 6}, 12) << "\n";
    
    // vector<long> m{63, 2, 26, 59, 16, 55, 99, 21, 98, 65};
    // long g = 56;
    cout << minTime({63, 2, 26, 59, 16, 55, 99, 21, 98, 65}, 56) << "\n";
    

    // vector<long> m{1386, 95, 2944, 4740, 3903, 4224, 2078, 3145, 4079, 329, 2735, 510, 335, 138, 1452, 4439, 4280, 1886, 416, 778, 2240, 4381, 3002, 963, 975, 528, 2001, 4620, 2575, 3013, 2578, 312, 3107, 521, 1403, 3361, 4744, 3480, 1505, 174, 3808, 591, 683, 494, 2080, 3487, 4932, 1359, 372, 1699, 3488, 2612, 2432, 1489, 4926, 3406, 3369, 3278, 4377, 2295, 1290, 1954, 2606, 748, 3827, 4009, 4108, 4922, 3840, 1964, 1448, 2648, 2555, 3482, 3141, 4634, 1968, 4425, 2345, 2340, 2475, 832, 1303, 4906, 3673, 2580, 3311, 2041, 858, 2687, 4335, 2147, 993, 3292, 4247, 1171, 3652, 3354, 1092, 2492, 1670, 3891, 1491, 576, 2373, 983, 1561, 4340, 1759, 3905, 3031, 586, 4737, 685, 491, 4761, 3265, 154, 1801, 4122, 4192, 2487, 2620, 184, 2130, 1866, 2706, 782, 1572, 150, 4625, 3241, 4040, 2467, 3816, 2764, 4801, 376, 3456, 1560, 633, 1486, 2145, 369, 3523, 3987, 129, 1787, 4140, 3281, 908, 3332, 767, 4879, 4867, 2896, 1745, 3925, 29, 3316, 4074, 1005, 1556, 4465, 3471, 1723, 2229, 3272, 3450, 684, 1183, 4082, 3521, 4679, 802, 2043, 3665, 2282, 181, 4157, 1914, 2440, 3840, 4032, 2319, 58, 3280, 4063, 3982, 3308, 3730, 4407, 665, 1637, 3872, 487, 3359, 2452, 3758, 3160, 4487, 1292, 3594, 3007, 2322, 4395, 1402, 987, 3029, 2934, 1495};
    // long g = 844676607;

    //cout << minTime(m, g) << "\n";
}
