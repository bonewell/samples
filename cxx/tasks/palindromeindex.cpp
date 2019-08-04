//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <string>

using namespace std;

// Complete the palindromeIndex function below.
int palindromeIndex(string s) {
    int i = 0;
    int j = s.length() - 1;
    while (i < j) {
        if (s[i] != s[j]) {
            if (s[i + 1] == s[j] && s[i + 2] == s[j - 1]) return i;
            if (s[i] == s[j - 1]) return j;
        }
        i++;
        j--;
    }
    return -1;
}

int main()
{
	cout << palindromeIndex("hgygsvlfwcwnswtuhmyaljkqlqjjqlqkjlaymhutwsnwcflvsgygh") << "\n";
	return 0;
}
