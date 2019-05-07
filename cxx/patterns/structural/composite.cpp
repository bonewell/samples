#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Address {
    public:
        virtual std::string get() const = 0;
        virtual ~Address() = default;
};
using AddressPtr = std::unique_ptr<Address>;

class CompositeAddress: public Address {
    public:
        CompositeAddress& add(AddressPtr item) {
            items_.push_back(std::move(item));
            return *this;
        }
        std::string get() const {
            std::string res;
            for (const auto& i: items_) {
                res += i->get() + " ";
            }
            return res;
        }
    private:
        std::vector<AddressPtr> items_;
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
    b.add(std::make_unique<Flat>("1"))
      .add(std::make_unique<Flat>("2"))
      .add(std::make_unique<Flat>("3"));

    std::cout << b << "\n";
}