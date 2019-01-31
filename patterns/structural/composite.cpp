#include <iostream>
#include <string>
#include <vector>

class Address {
    public:
        virtual std::string get() const = 0;
        virtual ~Address() = default;
};

class CompositeAddress: public Address {
    public:
        CompositeAddress& add(const Address& item) {
            items_.push_back(&item);
            return *this;
        }
        std::string get() const {
            std::string res;
            for (const auto i: items_) {
                res += i->get() + " ";
            }
            return res;
        }
    private:
        std::vector<const Address*> items_;
};

std::ostream& operator<<(std::ostream& out, const Address& address) {
    return out << address.get();
}

class Flat: public Address {
    public:
        Flat(std::string number):
            number_{std::move(number)} {}
        std::string get() const override {
            return number_;
        }
    private:
        std::string number_;
};

class Block: public CompositeAddress {
    public:
        Block(std::string number):
            number_{std::move(number)} {}
        std::string get() const override {
            return number_ + ": " + CompositeAddress::get();
        }
    private:
        std::string number_;
};


int main() {
    Block b{"539"};
    Flat f1{"1"};
    Flat f2{"2"};
    Flat f3{"3"};
    b.add(f1).add(f2).add(f3);

    std::cout << b << "\n";
}