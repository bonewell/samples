#include <iostream>

class WashingMachine {
private:
    virtual void wash() = 0;
    virtual void rinse() = 0;
    virtual void spin() {
        std::cout << "do spin\n";
    }
public:
    void washit() {
        wash();
        rinse();
        spin();
    }
};

class Indesite : public WashingMachine {
private:
    void wash() override {
        std::cout << "Indesite wash\n";
    }
    void rinse() override {
        std::cout << "Indesite rinse\n";
    }
};

int main() {
    Indesite machine;
    machine.washit();
}
