#include <iostream>
#include <unordered_map>

using namespace std;

int max_substr_length(const string& str) {
    int m = 0;
    int best = 0;
    unordered_map<char, int> table;
    for (auto i = 0; i != str.length(); ++i) {
        auto c = str[i];
        auto j = table.find(c);
        if (j == end(table)) {
            table[c] = -1;
        }
        m = min(m + 1, i - table[c]);
        best = max(best, m);
        table[c] = i;
    }

    return best;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Use: substring <string>\n";
        return 0;
    }
    string s{argv[1]};
    auto max = max_substr_length(s);
    cout << max << "\n";
}