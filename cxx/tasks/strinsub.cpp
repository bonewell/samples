//usr/bin/clang++ "$0" && ./a.out; exit
#include <iostream>
#include <string>

using namespace std;

long substrCount(int n, string s) {
    long l = 1;
    long pl = 0;
    long ppl = 0;
    long res = 1;
    char p = 0;
    char pp = 0;
    for (int i  = 1; i < s.length(); ++i) {
        if (s[i-1] == s[i]) {
            l++;
        } else {
            ppl = pl;
            pl = l;
            l = 1;
            pp = p;
            p = s[i-1];
        }
        res += l;
        cout << "pp=" << pp << ", p=" << p << ", s[" << i << "]=" << s[i] << "\n";
        cout << "l=" << l << ", pl=" << pl << ", ppl=" << ppl << "\n\n";
        if ((pl == 1) && (s[i] == pp) && (l <= ppl)) {
            cout << i << "->" << s[i] << "\n";
            res++;
        }
    }

    return res;
}

int main() {
    string s = "aaaa";
    //string s = "baabaaa";
    //string s = "aaasaa";
    cout << s << "\n";
    cout << substrCount(s.length(), s) << "\n";
    return 0;
}