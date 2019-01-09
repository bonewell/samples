#include <cstddef>
#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept
{
    return N;
}

template<typename T> class TD;

int func() {return 0;}

int main() {
    int a[] = {1, 2, 3, 4};
    
    std::cout << arraySize(a) << "\n";
    
    auto x = 27;
    std::cout << type_id_with_cvr<decltype(x)>().pretty_name() << "\n";    
    auto y(27);
    std::cout << type_id_with_cvr<decltype(y)>().pretty_name() << "\n"; 
    auto z = {27};
    std::cout << type_id_with_cvr<decltype(z)>().pretty_name() << "\n"; 
    auto w{27};
    std::cout << type_id_with_cvr<decltype(w)>().pretty_name() << "\n"; 
    
    decltype((x)) u = x;
    std::cout << type_id_with_cvr<decltype(u)>().pretty_name() << "\n";

    std::cout << type_id_with_cvr<decltype(func)>().pretty_name() << "\n";
    std::cout << type_id_with_cvr<decltype((func))>().pretty_name() << "\n";

    // TD<decltype(ff)> td; to get compile error with type
}