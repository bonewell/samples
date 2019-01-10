#include <string>
#include <iostream>
#include <list>

using namespace std;

struct Car {
    string manufacture;
    string model;
};

class Rent {
    public:
    Rent(initializer_list<Car> cars) {
        for (auto c: cars)
            cars_.push_back(c);
    }
    Car get() {
        auto c = cars_.front();
        cars_.pop_front();
        return c;
    }
    void getback(Car&& car) {
        cars_.push_back(move(car));
    }
    void show() {
        for (const auto& c: cars_)
            cout << c.manufacture << " " << c.model << "\n";
    }
    private:
        list<Car> cars_;
};

int main() {
    Rent recar{{Car{"Ford", "Fiesta"}, Car{"Nissan", "X-trail"}}};
    auto car = recar.get();
    recar.show();
    cout << car.model << "\n";
    recar.getback(move(car));
    recar.show();
}