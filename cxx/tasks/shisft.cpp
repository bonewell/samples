#include <iostream>
#include <vector>

using namespace std;

int main () {

    char x = '1';

    int xx = (int) x;
    cout << xx << "\n";

    vector<int> a{1, 2, 3, 4, 5};

    int n = 2;

    int l = a.size();
    int tmp = a[0];
    int i = 0;
    int c = l;
    while (c > 0) {
        int k = (i + n) % l;
        cout << k << "\n";
        if (k == 0) {
            a[i] = tmp;
        } else {
            a[i] = tmp;
            tmp = a[k];
        }
        i = k;
        c--;
    }

    for (auto i: a) {
        cout << i << " ";
    }
    cout << "\n";
}