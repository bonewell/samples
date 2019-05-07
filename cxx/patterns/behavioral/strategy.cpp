#include <iostream>
#include <memory>

class Cooking {
public:
    virtual std::string cook(const std::string& food) = 0;
    virtual ~Cooking() = default;
};
using CookingPtr = std::unique_ptr<Cooking>;

class Boil : public Cooking {
public:
    std::string cook(const std::string& food) override {
        return "boil " + food;
    }
};

class Fry : public Cooking {
public:
    std::string cook(const std::string& food) override {
        return "fry " + food;
    }
};

class Bake : public Cooking {
public:
    std::string cook(const std::string& food) override {
        return "bake " + food;
    }
};

class Cook {
public:
    std::string doit(const std::string& food) {
        return strategy_->cook(food);
    }
    void setStrategy(CookingPtr strategy) {
        strategy_ = std::move(strategy);
    }
private:
    CookingPtr strategy_;
};

int main() {
    Cook c;
    c.setStrategy(std::make_unique<Boil>());
    std::cout << c.doit("eggs") << "\n";

    c.setStrategy(std::make_unique<Fry>());
    std::cout << c.doit("potatoes") << "\n";
}

