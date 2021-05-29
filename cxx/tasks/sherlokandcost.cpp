#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

using Values = unordered_map<int, int>;
using Matrix = vector<Values>;

ostream& operator<<(ostream& out, Values::value_type const& v) {
    return out << '(' << v.first << ',' << v.second << ')';
}

Matrix m;

void printM() {
    for (auto const& v: m) {
        for (auto const& p: v) {
            cout << p << ' ';
        }
        cout << endl;
    }
}

int getMax(int v, int i) {
    int maxi = 0;
    for (auto const& p: m[i])
        maxi = max(maxi, abs(v - p.first) + p.second);
    return maxi;
}

void init(vector<int> const& B) {
    m.clear();
    m.resize(B.size());
    for (int i = 1; i <= B[0]; ++i) m[0][i] = 0;
}

int maximum(Values const& mv) {
    int maxi = 0;
    for (auto const& p: mv) maxi = max(maxi, p.second);
    return maxi;
}

int cost(vector<int> const& B) {
    init(B);
    for (int i = 1; i < B.size(); ++i)
        for (int v = 1; v <= B[i]; ++v) m[i][v] = getMax(v, i - 1);
    return maximum(m.back());
}

int main() {

    // vector<int> B{1, 2, 3};
    //vector<int> B{10, 1, 10, 1, 10};
    //vector<int> B{100, 2, 100, 2, 100};
    //vector<int> B{4, 7, 9};
    vector<int> B{3, 15, 4, 12, 10};

    cout << cost(B) << '\n';

    printM();

    return 0;
}