#include <iostream>
#include <typeinfo>
#include <string>

template<typename Task>
void get(Task) {
    decltype(std::declval<Task>()()) x;
    std::cout << typeid(x).name() << "\n";
}

int main() {
    get([]{
        return std::string{};
    });
}
