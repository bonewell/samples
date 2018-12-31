#include <iostream>

using namespace std;

int operator+(int a, int b) {  // error: not possible overload operators for standard types
    return a - b;
}

int main() {
    int x = 5;
    int y = 4;
    int z = x - y;
    cout << z << "\n";
}