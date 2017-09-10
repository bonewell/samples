#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<int> v = { 1, 3 };
	int first = v[0];
	auto func = [first](int a, int b) {
				if (a == b) return false;
				if ((a >= first && b >= first) || 
						(a < first && b < first)) {
					return a < b;
				}
				return a >= first && b < first;
			};
	cout << binary_search(v.begin(), v.end(), 2, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 2, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 3, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 4, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 5, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 6, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 7, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 8, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 9, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 0, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 10, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 11, func) << endl;
//	cout << binary_search(v.begin(), v.end(), 12, func) << endl;


	return 0;
}
