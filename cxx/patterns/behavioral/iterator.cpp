#include <iostream>
#include <memory>

struct Level {
    int number;
};

class LevelIterator {
public:
    virtual Level up() = 0;
    virtual Level down() = 0;
    virtual bool hasUp() const = 0;
    virtual bool hasDown() const = 0;
    virtual ~LevelIterator() = default;
};

class IterableBuilding {
public:
    using Iterator = std::unique_ptr<LevelIterator>;
    virtual Iterator iterator() = 0;
    virtual ~IterableBuilding() = default;
};

class Skyscraper;

class Elevator : public LevelIterator {
public:
    Elevator(Skyscraper& building) : building_{building} {}
    Level up() override;
    bool hasUp() const override;
    Level down() override;
    bool hasDown() const override;
private:
    Skyscraper& building_;
    int current_{0};
};

class Skyscraper : public IterableBuilding {
public:
    Skyscraper(int levels): levels_{levels} {}
    int levels() const { return levels_; };
    Iterator iterator() override {
        return std::make_unique<Elevator>(*this);
    }
private:
    int levels_;
};

Level Elevator::up() {
    return Level{++current_};
}
bool Elevator::hasUp() const {
    return current_ < building_.levels();
}
Level Elevator::down() {
    return Level{--current_};
}
bool Elevator::hasDown() const {
    return current_ > 0;
}

int main() {
    Skyscraper b{5};
    auto it = b.iterator();
    while (it->hasUp()) {
        std::cout << it->up().number << "\n";
    }
    while (it->hasDown()) {
        std::cout << it->down().number << "\n";
    }
}