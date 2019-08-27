#include <iostream>

using namespace std;

struct A {
    int x;
    int* p;
    double d{3.4};
};

ostream& operator<<(ostream& out, const A& a) {
    cout << a.x << ", " << a.p << ", " << a.d;
}

int main() {
    A a;
    cout << a << '\n';
    A b{};
    cout << b << '\n';

    return 0;
}
