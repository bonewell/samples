#include <functional>
#include <string>
#include <iostream>
#include <future>
#include <cstring>

auto asyncall(std::function<int()> callback) {
  return std::async(callback);
}

auto invoker(const std::string& text) {
  return asyncall([=]() {  // & - crash
    return strlen(text.c_str());
  });
}

int main() {
  auto t = new std::string("abc");
  auto f = invoker(*t);
  delete t;
  std::cout << "len: " << f.get() << std::endl;
  return 0;
}
