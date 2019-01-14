#include <string>
#include <iostream>

using namespace std;

// imagine it is not possible to change
class DeltaApi {
    public:
        int find(const string& name) {
            return 2;
        }
        int balance(int id) {
            return 500;
        }
};

struct Account {
    string name;
    int money;
};

class Bank {
    public:
        virtual Account account(string name) = 0;
        ~Bank() = default;
};

class DeltaBank: public Bank {
    public:
        Account account(string name) override {
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
    cout << a.name << ": " << a.money << "\n";
}
