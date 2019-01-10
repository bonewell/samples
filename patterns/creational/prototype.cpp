#include <memory>
#include <iostream>

using namespace std;

class Cell {
    public:
        Cell&& clone() {
            auto c = *this;
            return move(c);
        }
        Cell(Cell&&) = default;
        Cell& operator=(Cell&&) = default;
        Cell() = default;
        ~Cell() = default;
        int generation = 0;
    private:
        Cell(const Cell& o) {
            generation = o.generation + 1;
        }
        Cell& operator=(const Cell& o) {
            generation = o.generation + 1;
            return *this;
        }
};

int main() {
    Cell c;
    auto nc = c.clone();
    cout << nc.generation << "\n";
    auto nc2 = nc.clone();
    cout << nc2.generation << "\n";
    auto cc = c.clone();
    cout << cc.generation << "\n";
}