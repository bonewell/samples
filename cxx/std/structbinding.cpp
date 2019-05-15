#include <string>
#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

struct S {
    int i;
    std::string t;
    double* d;
};

int main() {
    S s;
    const auto [i, t, d] = s;
    std::cout << type_id_with_cvr<decltype(i)>().pretty_name() << "\n";
    std::cout << type_id_with_cvr<decltype(t)>().pretty_name() << "\n";
    std::cout << type_id_with_cvr<decltype(d)>().pretty_name() << "\n";
}
