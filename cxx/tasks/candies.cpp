//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <vector>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) {
    long sum = n;
    long s = 0;
    vector<int> v(n, 1);
    while (sum != s) {
        s = sum;
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] < arr[i+1] && v[i] >= v[i+1]) {
                int d = v[i] - v[i+1] + 1;
                v[i+1] = v[i] + 1;
                s += d;
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            if (arr[i-1] > arr[i] && v[i-1] <= v[i]) {
                int d = v[i] - v[i-1] + 1;
                v[i-1] = v[i] + 1;
                s += d;
            }
        }
        swap(sum, s);
    }
    return sum;
}

int main()
{
// b = b+1 (1, 1, 1) = n + 1
// b > b+1 (2, 1, 1) = n + 2
// b > b+2 (3, 2, 1) = n + 1
// b < b+1 && b+1 < b+2 (1, 2, 3) = n + 3
// b < b+1 && b+1 == b+2 (1, 2, 2) = n + 2
// b < b+1 (1, 2, 1) = n + 1

// 	cout << candies(0, {}) << "\n";  // 0
// 	cout << candies(1, {2}) << "\n";  // 1
// 	cout << candies(2, {1, 1}) << "\n";  // 2
// 	cout << candies(2, {1, 2}) << "\n";  // 3
// 	cout << candies(2, {2, 1}) << "\n";  // 3
// 	cout << candies(3, {1, 1, 1}) << "\n"; // 3
// 	cout << candies(3, {1, 1, 2}) << "\n"; // 4
// 	cout << candies(3, {1, 2, 1}) << "\n"; // 4
// 	cout << candies(3, {2, 1, 1}) << "\n"; // 4
// 	cout << candies(3, {1, 2, 2}) << "\n"; // 4
// 	cout << candies(3, {2, 2, 1}) << "\n"; // 4
// 	cout << candies(3, {2, 1, 2}) << "\n"; // 5
// 	cout << candies(3, {2, 2, 2}) << "\n"; // 3
// 	cout << candies(3, {1, 2, 3}) << "\n"; // 6
// 	cout << candies(3, {3, 2, 1}) << "\n"; // 6
// 	cout << candies(3, {1, 3, 2}) << "\n"; // 4
// 	cout << candies(4, {1, 1, 1, 1}) << "\n"; // 4
// 	cout << candies(4, {1, 2, 2, 2}) << "\n"; // 5
// 	cout << candies(4, {1, 2, 2, 1}) << "\n"; // 6
// 	cout << candies(4, {1, 2, 2, 2}) << "\n"; // 5
// 	cout << candies(4, {1, 2, 2, 2}) << "\n"; // 5

// 	cout << candies(3, {1, 2, 2}) << "\n";
	cout << candies(10, {2, 4, 2, 6, 1, 7, 8, 9, 2, 1}) << "\n";

	return 0;
}