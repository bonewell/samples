#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class A {
public:
    A() = default;
    ~A() = default;
    A(initializer_list<int> init) { cout << "init_list ctr\n"; assert(init.size() > 0); i = *init.begin(); }
    explicit A(int i): i{i} { cout << "ctr\n"; }
    A(A&& a) { cout << "move ctr\n"; swap(i, a.i); }
    A(A const& a): i{a.i} { cout << "copy ctr\n"; }
    A& operator=(A&& a) { cout << "move\n"; swap(i, a.i); return *this; }
    A& operator=(A const& a) { cout << "move\n"; i = a.i; return *this; }
    int i{0};
};

ostream& operator<<(ostream& out, A const& a) {
    return out << "{" << a.i << "}";
}

int main() {
    //vector<string> v{"one", "two", "three", "four"};
    vector<A> v{{1}, {2}, {3}, {4}};
    auto& r = v;
    //vector<string> c;
    vector<A> c;

    cout << "do copy using move iterator\n";
    copy_if(make_move_iterator(begin(r)),
            make_move_iterator(end(r)),
            back_inserter(c),
            [](auto const& i) { return i.i == 4; });

    copy(begin(r), end(r), ostream_iterator<A>{cout, " "});
    cout << '\n';

    copy(begin(c), end(c), ostream_iterator<A>{cout, " "});
    cout << '\n';

    return 0;
}
