#include <memory>
#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

class Base{
    public:
        virtual ~Base() {
            cout << "~Base\n";
        }
};

class Derived: public Base{
    public:
        ~Derived() {
            cout << "~Derived\n";
        }
};

class NoDerived {
    public:
        ~NoDerived() {
            cout << "~NoDerived\n";
        }
};

int main() {
    unique_ptr<Base> bp;

    auto dp = make_unique<Derived>();

    vector<unique_ptr<Base>> v;// = {move(make_unique<Derived>())};
    v.push_back(make_unique<Derived>());

    for (const auto& p: v) {
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << "\n";
    }

    for (auto it = begin(v); it != end(v); ++it) {
        cout << type_id_with_cvr<decltype(it)>().pretty_name() << "\n";
        cout << type_id_with_cvr<decltype(*it)>().pretty_name() << "\n";
    }

    auto ndp = make_unique<NoDerived>();

//     bp = ndp;
}