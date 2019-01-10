#include <unordered_map>
#include <string>
#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

template<typename T>
auto func(T f) { // -> decltype(f()) { // comment for c++11
    static_assert(is_invocable_v<T>);
    return f();
}

template<> auto func(int) = delete;

void types() {
    unordered_map<string, int> x = {{"a", 1}};
    for (const auto& i: x)
      cout << type_id_with_cvr<decltype(i)>().pretty_name() << "\n";
      
    auto r = func([&x](){ return &x["a"]; });
    cout << r << "\n";
    cout << type_id_with_cvr<decltype(r)>().pretty_name() << "\n";
    
    using MF = void (*)(int);
    MF mf = [](int x) { x = 0; };
    cout << type_id_with_cvr<decltype((mf))>().pretty_name() << "\n";
}

void forwardtest() {
    int in = 4;
    auto&& i = forward<int>(in);
    cout << type_id_with_cvr<decltype(i)>().pretty_name() << "\n";  
    auto&& ii = forward<int&>(in);
    cout << type_id_with_cvr<decltype(ii)>().pretty_name() << "\n";  
    auto&& iii = forward<int>(5);
    cout << type_id_with_cvr<decltype(iii)>().pretty_name() << "\n";
//     auto&& iv = forward<int&>(5); compile error
}

struct Bits {
    uint8_t version: 2,
                code: 3,
                value: 3;
};
ostream& operator << (ostream& os, const Bits& b) {
    return os << "version=" << int(b.version)
                   << " code=" << int(b.code)
                   << " value=" << int(b.value);
}

void structure() {
  Bits b{2, 4, 7};
  cout << b << "\n";
} 

int main() {
    types();
    // auto fi = func(5); error: deleted template specialization
    forwardtest();
    structure();
}