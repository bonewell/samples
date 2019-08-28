#include <iostream>

using namespace std;

template<typename T> struct Animal;

struct Zoo {
    explicit Zoo(Animal<int>* it) : creature{it} {}
    Animal<int>* creature{nullptr};
};

template<typename T>
struct Animal {
    T feature{};
};

int main() {
    Zoo z{new Animal<int>{}};
    z.creature->feature = 5;
    cout << z.creature->feature << '\n';

    return 0;
}
