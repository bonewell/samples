#include <memory>

class Pimpl {
public:
    Pimpl() noexcept;
    ~Pimpl() noexcept;
    Pimpl(Pimpl&& o) noexcept;
    Pimpl& operator =(Pimpl&& o) noexcept;
    Pimpl(const Pimpl& o);
    Pimpl& operator =(const Pimpl& o);
    
    void print();
private:
    struct Impl;
    std::unique_ptr<Impl> ptr_;
};

class SharedPimpl {
public:
    SharedPimpl() noexcept;  // to initialize structure
    
// For the rule of six we can add next
//     ~SharedPimpl() noexcept = default;
//     SharedPimpl(SharedPimpl&& o) noexcept = default;
//     SharedPimpl& operator =(SharedPimpl&& o) noexcept = default;
//     SharedPimpl(const SharedPimpl& o) = default;
//     SharedPimpl& operator =(const SharedPimpl& o) = default;

    void print();
private:
    struct Impl;
    std::shared_ptr<Impl> ptr_;
};