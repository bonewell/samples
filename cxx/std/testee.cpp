#include <iostream>

using namespace std;

class A {
    int x {5};
protected:
    void run() {
        cout << x << " A::run\n";
    }
};

class ATestee: public A {
public:
    using A::run;  // for private doesn't work
};

int main() {
    ATestee at;
    at.run();
}