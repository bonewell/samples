#include <memory>
#include <string>
#include <iostream>

class Item {
    public:
        Item(const std::string& name): name_{name}
        {
        }

        virtual void poweron()
        {
            std::cout << "poweron\n";
        }

        virtual void shutdown()
        {
            std::cout << "shutdown\n";
        }
    private:
        std::string name_;
};
using Product = std::unique_ptr<Item>;

class Factory {
    public:
        Product produce(const std::string& name) const
        {
            std::cout << "produce\n";
            auto p = create(name);
            p->poweron();
            return p;
        }
    protected:
        virtual Product create(const std::string& name) const = 0;
};

class Laptop: public Item {
    public:
        Laptop(const std::string& name): Item{name}
        {
        }
};

class LaptopFactory: public Factory {
    protected:
        Product create(const std::string& name) const override
        {
            std::cout << "Create laptor " << name << "\n";
            return std::make_unique<Laptop>(name);
        }
};

class Vehicle: public Item {
    public:
        Vehicle(const std::string& name): Item{name}
        {
        }
};

class VehicleFactory: public Factory {
    protected:
        Product create(const std::string& name) const override
        {
            std::cout << "Create vehicle " << name << "\n";
            return std::make_unique<Vehicle>(name);
        }
};

int main() {
    const Factory& factory = LaptopFactory{};
    auto laptop = factory.produce("ASUS");
    laptop->shutdown();
}