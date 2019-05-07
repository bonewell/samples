#include <iostream>
#include "requested_categories.h"

class BaseClass {
 public:
  virtual void Callback(Category c) {};

  void Invoke() {
    categories_.Add(Category::kDefault);
    categories_.Add(Category::kNavigation);
    categories_.Add(Category::kPhoneCall);
    categories_.Add(Category::kVoice);
    categories_.DoForEach([this](Category c) {
        if (c != Category::kPhoneCall) {
          Callback(c);
        }
    });
  }

 private:
  RequestedCategories categories_;
};

class MyClass : public BaseClass {
 public:
  void Callback(Category c) override {
    std::cout << static_cast<int>(c) << std::endl;
  }
};

class SecondClass : public BaseClass {
 public:
  void Callback(Category c) override {
    std::cout << "item:" << static_cast<int>(c) << std::endl;
  }
};



int main() {
  SecondClass m;
  m.Invoke();
  return 0;
}
