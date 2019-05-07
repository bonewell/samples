#include <memory>
#include <iostream>

class Clonable;
using Clone = std::unique_ptr<Clonable>;

class Clonable {
    public:
        virtual Clone clone() = 0;
        virtual ~Clonable() = default;
};

class Cell: public Clonable {
    public:
        Clone clone() override {
            return Clone{new Cell{*this}};
        }
        Cell() = default;
        int generation = 0;
    private:
        Cell(const Cell& o) {
            generation = o.generation + 1;
        }
};
std::ostream& operator<<(std::ostream& out, const Cell& cell) {
    return out << cell.generation;
}

int main() {
    Clone c = std::make_unique<Cell>();
    std::unique_ptr<Cell> nc{static_cast<Cell*>(c->clone().release())};
    std::cout << *nc << "\n";
    std::unique_ptr<Cell> nc2{static_cast<Cell*>(nc->clone().release())};
    std::cout << *nc2 << "\n";
    std::unique_ptr<Cell> cc{static_cast<Cell*>(c->clone().release())};
    std::cout << *cc << "\n";
}