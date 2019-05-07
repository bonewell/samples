#include "pimpl.h"

#include <iostream>

struct Pimpl::Impl {
  int a;
};

struct SharedPimpl::Impl {
  double x;
};

Pimpl::Pimpl() noexcept:
  ptr_(std::make_unique<Impl>())
{
}

Pimpl::~Pimpl() noexcept = default;

Pimpl::Pimpl(Pimpl&& o) noexcept = default;
Pimpl& Pimpl::operator =(Pimpl&& o) noexcept = default;

Pimpl::Pimpl(const Pimpl& o): ptr_(std::make_unique<Impl>(*o.ptr_))
{
}

Pimpl& Pimpl::operator =(const Pimpl& o) {
  *ptr_ = *o.ptr_;
  return *this;
}

void Pimpl::print() {
    std::cout << ptr_->a << "\n";
}

SharedPimpl::SharedPimpl() noexcept:
  ptr_(std::make_shared<Impl>())
{
}

void SharedPimpl::print() {
    std::cout << ptr_->x << "\n";
}