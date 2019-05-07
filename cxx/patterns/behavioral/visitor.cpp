#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class PFRF;
class MVD;

class Visitor {
public:
    virtual void visitPFRF(PFRF* pfrf) = 0;
    virtual void visitMVD(MVD* mvd) = 0;
    virtual ~Visitor() = default;
};

class Organization {
public:
    virtual void accept(Visitor& v) = 0;
    virtual ~Organization() = default;
};

class PFRF : public Organization {
public:
    void accept(Visitor& v) override {
        v.visitPFRF(this);
    }
    int money() {
        return 1'000'000;
    }
};

class MVD : public Organization {
public:
    void accept(Visitor& v) override {
        v.visitMVD(this);
    }
    int count() {
        return 5;
    }
};

class President : public Visitor {
public:
    void visitPFRF(PFRF* pfrf) override {
        std::cout << "PFRF's money " << pfrf->money() << "\n";
    }
    void visitMVD(MVD* mvd) override {
        std::cout << "MVD's count " << mvd->count() << "\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Organization>> orgs;
    orgs.push_back(std::make_unique<PFRF>());
    orgs.push_back(std::make_unique<MVD>());

    President v;
    std::for_each(std::begin(orgs), std::end(orgs), [&v](auto& o) {
        o->accept(v);
    });
}
