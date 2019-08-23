#include <iostream>

using namespace std;

struct A {
    int x;
    int* p;
};

int main() {
    A a;
    cout << a.x << ", " << a.p << '\n';
    A b{};
    cout << b.x << ", " << b.p << '\n';

    return 0;
}
