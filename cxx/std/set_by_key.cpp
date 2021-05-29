#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>

using namespace std;

struct V {
    int value;
};

struct Cmp {
    bool operator() (V const* a, V const* b) const {
        return a->value < b->value;
    }
};

ostream& operator<<(ostream& out, V const* a) {
    return out << a->value;
}

int main() {
    V v1{10};
    V v2{2};
    V v3{30};
    V v4{40};
    set<V*, Cmp> s;

    s.insert(&v1);
    s.insert(&v2);
    s.insert(&v3);
    s.insert(&v4);

    copy(begin(s), end(s), ostream_iterator<V*>(cout, " "));
    cout << '\n';

    v4.value = 4;
    s.erase(begin(s));

    copy(begin(s), end(s), ostream_iterator<V*>(cout, " "));
    cout << '\n';

    return 0;
}
