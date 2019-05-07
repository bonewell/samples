#include <iostream>

class MVD {
    public:
        bool checkPolicy() {
            std::cout << "MVD: check policy\n";
            return true;
        }
};

class FNS {
    public:
        void provideDiscount() {
            std::cout << "FNS: provide discount\n";
        }
};

class PFR {
    public:
        void grantPensions() {
            std::cout << "PFR: grant pensions\n";
        }
};

class MFC {
    public:
        void service() {
            if (mvd_.checkPolicy()) {
                fns_.provideDiscount();
            }
            pfr_.grantPensions();
        }
    private:
        MVD mvd_;
        FNS fns_;
        PFR pfr_;
};

int main() {
    MFC mfc;
    mfc.service();
}