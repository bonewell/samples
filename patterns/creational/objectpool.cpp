#include <string>
#include <iostream>
#include <list>

struct Car {
    std::string manufacture;
    std::string model;
};

class Rent {
    public:
    Rent(std::initializer_list<Car> cars) {
        for (auto c: cars)
            cars_.push_back(c);
    }
    Car get() {
        auto c = cars_.front();
        cars_.pop_front();
        return c;
    }
    void getback(Car&& car) {
        cars_.push_back(std::move(car));
    }
    void show() {
        for (const auto& c: cars_)
            std::cout << c.manufacture << " " << c.model << "\n";
    }
    private:
        std::list<Car> cars_;
};

int main() {
    Rent recar{{Car{"Ford", "Fiesta"}, Car{"Nissan", "X-trail"}}};
    auto car = recar.get();
    recar.show();
    std::cout << car.model << "\n";
    recar.getback(std::move(car));
    recar.show();
}