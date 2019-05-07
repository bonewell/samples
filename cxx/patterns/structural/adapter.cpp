#include <string>
#include <iostream>

// imagine it is not possible to change
class DeltaApi {
    public:
        int find(const std::string& name) {
            return 2;
        }
        int balance(int id) {
            return 500;
        }
};

struct Account {
    std::string name;
    int money;
};

class Bank {
    public:
        virtual Account account(std::string name) = 0;
        ~Bank() = default;
};

class DeltaBank: public Bank {
    public:
        Account account(std::string name) override {
            Account acc;
            auto id = api_.find(name);
            if (id > 0) {
                acc.name = name;
                acc.money = api_.balance(id);
            }
            return acc;
        }
    private:
        DeltaApi api_;
};

int main() {
    DeltaBank delta;
    Bank& b = delta;
    auto a = b.account("My Name");
    std::cout << a.name << ": " << a.money << "\n";
}
