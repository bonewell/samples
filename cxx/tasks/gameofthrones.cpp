//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Complete the gameOfThrones function below.
string gameOfThrones(string s) {
	unordered_map<char, int> cs;

	for (char c: s) {
		cs[c]++;
	}

	int nechet = 0;
	for (auto [c, v]: cs) {
		if (v % 2 != 0) nechet++;
		if (nechet > 1) return "NO";
	}

	return "YES";
}

int main()
{
	cout << gameOfThrones("aaabbbb") << "\n";
	cout << gameOfThrones("cdefghmnopqrstuvw") << "\n";
	cout << gameOfThrones("cdcdcdcdeeeef") << "\n";

	return 0;
}