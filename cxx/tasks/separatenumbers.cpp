//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <string>

using namespace std;

long long call(const string& s, int l) {
	cout << "l=" << l << "\n";
	string xs = s.substr(0, l);
	auto x = stoull(xs);
	auto b = x;
	if (x > 0 && xs[0] == '0') return 0;
	int i = l;
	while (i < s.length()) {
		string ys = s.substr(i, l);
		auto y = stoull(ys);
		cout << "x=" << xs << ", y=" << ys << "\n";
		if (ys.length() != l || ys[0] == '0') return 0;
		if (y - x != 1) {
			if (xs.length() != ys.length()) return 0;
			l++;
		}
		else {
			x = y;
			i += l;
		}
	}
	return b;
}

// Complete the weightedUniformStrings function below.
void separateNumbers(string s) {
	int l = 1;
	while (l <= s.length() / 2) {
		auto x = call(s, l);
		if (x != 0) {
			cout << "YES " << x << "\n";
			return;
		}
		else {
			l++;
		}
	}
	cout << "NO\n";
}

int main()
{
 	separateNumbers("10331003514757101033100351475711");

// 	separateNumbers("1234");
// 	separateNumbers("91011");
// 	separateNumbers("99100");
// 	separateNumbers("101103");
// 	separateNumbers("010203");
// 	separateNumbers("13");
// 	separateNumbers("1");
// 	separateNumbers("88888888888888888888888888888888");

	return 0;
}