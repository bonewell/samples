#include <iostream>
#include <vector>
#include <exception>

using Cash = std::vector<int>;

class NoMoney: public std::exception {};

class CashCatridge;
using CashCatridgePtr = std::unique_ptr<CashCatridge>;

class ATM {
    public:
        virtual void add(CashCatridgePtr catridge) = 0;
        virtual Cash withdraw(int amount) = 0;
        virtual ~ATM() = default;
};

class CashCatridge: public ATM {
    public:
        CashCatridge(int count): count_{count} {}
        void add(CashCatridgePtr catridge) override {
            if (next_) {
                next_->add(std::move(catridge));
            } else {
                next_ = std::move(catridge);
            }
        }
        Cash withdraw(int amount) override {
            if (next_) {
                return next_->withdraw(amount);
            }
            return {};
        }
    protected:
        Cash withdraw(int amount, int banknote) {
            int c = amount / banknote;
            if (c > count_) {
                throw NoMoney{};
            }
            Cash res;
            if (amount % banknote != 0) {
                res = CashCatridge::withdraw(amount % banknote);
            }
            res.insert(end(res), c, banknote);
            count_ -= c;
            return res;
        }
    private:
        int count_;
        CashCatridgePtr next_;
};

class Cash1000: public CashCatridge {
    public:
        Cash1000(int count): CashCatridge(count) {}
        Cash withdraw(int amount) override {
            return CashCatridge::withdraw(amount, 1000);
        }
};

class Cash500: public CashCatridge {
    public:
        Cash500(int count): CashCatridge(count) {}
        Cash withdraw(int amount) override {
            return CashCatridge::withdraw(amount, 500);
        }
};

class Cash100: public CashCatridge {
    public:
        Cash100(int count): CashCatridge(count) {}
        Cash withdraw(int amount) override {
            return CashCatridge::withdraw(amount, 100);
        }
};

int main() {
    std::unique_ptr<ATM> atm = std::make_unique<Cash1000>(100);
    atm->add(std::make_unique<Cash500>(1000));
    atm->add(std::make_unique<Cash100>(5000));

    auto cash = atm->withdraw(2900);
    for (const auto& c: cash) {
        std::cout << c << " ";
    }
    std::cout << "\n";
}