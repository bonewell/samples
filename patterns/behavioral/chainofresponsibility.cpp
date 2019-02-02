#include <iostream>
#include <vector>
#include <exception>

using Cash = std::vector<int>;

class NoMoney: public std::exception {
};

class CashCatridge {
    public:
        CashCatridge(int count): count_{count} {}
        CashCatridge& add(CashCatridge* catridge) {
            if (next_) {
                next_->add(catridge);
            } else {
                next_ = catridge;
            }
            return *this;
        }
        virtual Cash withdraw(int amount) {
            if (next_) {
                return next_->withdraw(amount);
            }
            return {};
        }
        virtual ~CashCatridge() = default;
    protected:
        int count() { return count_; };
        Cash withdraw(int amount, int banknote) {
            int c = amount / banknote;
            if (c > count()) {
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
        CashCatridge* next_;
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
    Cash1000 c1000(100);
    Cash500 c500(1000);
    Cash100 c100(5000);
    c1000.add(&c500).add(&c100);

    auto cash = c1000.withdraw(2900);
    for (const auto& c: cash) {
        std::cout << c << " ";
    }
    std::cout << "\n";
}