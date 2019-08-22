//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Complete the stringConstruction function below.
int stringConstruction(string s) {
	unordered_map<char, bool> cs;
	int res = 0;
	for (char c: s) {
		if (!cs[c]) {
			cs[c] = true;
			res++;
		}
	}

	return res;
}

int main()
{
	cout << stringConstruction("abcd") << "\n";

	return 0;
}