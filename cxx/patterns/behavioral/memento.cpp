#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Memento {
public:
    virtual std::string name() = 0;
    virtual ~Memento() = default;
};

class Wardrobe {
public:
    using Stuff = std::vector<std::string>;
    class State : public Memento {
        public:
            State(std::string name, Stuff stuff):
                name_{std::move(name)},
                stuff_{stuff} {}
            std::string name() override {
                return name_;
            }
            void restore(Wardrobe& w) {
                w.stuff_ = stuff_;
            }
        private:
            std::string name_;
            Stuff stuff_;
    };
    State save(std::string name) {
        return State{std::move(name), stuff_};
    }
    void put(std::string name) {
        stuff_.push_back(std::move(name));
    }
    void restore(State state) {
        state.restore(*this);
    }
private:
    friend std::ostream& operator<<(std::ostream&, const Wardrobe&);
    Stuff stuff_;
};
std::ostream& operator<<(std::ostream& out, const Wardrobe& w) {
    std::copy(std::begin(w.stuff_), std::end(w.stuff_), std::ostream_iterator<std::string>(out, " "));
    return out;
}

int main() {
    Wardrobe w;
    w.put("shoes");
    w.put("hat");
    std::cout << w << "\n";

    auto state = w.save("thefirst");
    w.put("shirt");
    std::cout << w << "\n";

    std::cout << state.name() << "\n";
    w.restore(state);

    std::cout << w << "\n";
}