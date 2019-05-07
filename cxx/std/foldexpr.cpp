#include <iostream>

using namespace std;

template<class... Args>
auto sum(Args... args) {
    return (... + args);  // C++17 "fold expression"
}

int main() {
    cout << sum(3, 2) << "\n";
    cout << sum(3.14159, 2.71828) << "\n";
}