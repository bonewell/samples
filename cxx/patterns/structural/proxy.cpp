#include <iostream>
#include <memory>

class Kpp {
    public:
        virtual bool open(std::string id) = 0;
        virtual ~Kpp() = default;
};
using KppPtr = std::shared_ptr<Kpp>;

class Schlagbaum: public Kpp {
    bool open(std::string id) override {
        std::cout << "open schlagbaum\n";
        return true;
    }
};

class FrontierGuard: public Kpp {
    public:
        FrontierGuard(KppPtr kpp):
            kpp_{std::move(kpp)} {
        }
        bool open(std::string id) override {
            if (id == "president") {
                std::cout << "President\n";
                return kpp_->open(id);
            }
            return false;
        }
    private:
        KppPtr kpp_;
};

int main() {
    FrontierGuard guard{std::make_shared<Schlagbaum>()};
    guard.open("president");
}