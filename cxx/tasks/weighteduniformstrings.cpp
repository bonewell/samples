//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Complete the weightedUniformStrings function below.
vector<string> weightedUniformStrings(string s, vector<int> queries) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    unordered_map<char, int> alws;
    for (int i = 0; i < alphabet.length(); ++i)
        alws[alphabet[i]] = i + 1;

    unordered_map<char, int> crs;
    unordered_set<int> ws;
    crs[s[0]] = alws[s[0]];
    ws.insert(crs[s[0]]);
    for (int i = 1; i < s.length(); ++i) {
        if (s[i-1] == s[i]) crs[s[i]] += alws[s[i]];
        else crs[s[i]] = alws[s[i]];
        ws.insert(crs[s[i]]);
    }

    vector<string> res;
    for (int q: queries) {
        res.push_back(ws.find(q) != end(ws) ? "Yes" : "No");
    }

    return res;
}


int main()
{
	for (auto v: weightedUniformStrings("abccddde", {1})) {
		cout << v << "\n";
	}
	return 0;
}