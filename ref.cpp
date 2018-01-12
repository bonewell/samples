#include <iostream>

int main() {
  int obj = 5;
  int& ref = obj;
  int nobj = 10;
  std::cout << "ptr to obj = " << &obj << std::endl;
  std::cout << "ptr to nobj = " << &nobj << std::endl;
  std::cout << "ptr to ref = " << &ref << std::endl;
  std::cout << "value of obj = " << obj << std::endl;
  std::cout << "value of nobj = " << nobj << std::endl;
  std::cout << "value of ref = " << ref << std::endl;
  ref = nobj;
  std::cout << "ptr to obj = " << &obj << std::endl;
  std::cout << "ptr to nobj = " << &nobj << std::endl;
  std::cout << "ptr to ref = " << &ref << std::endl;
  std::cout << "value of obj = " << obj << std::endl;
  std::cout << "value of nobj = " << nobj << std::endl;
  std::cout << "value of ref = " << ref << std::endl;
}
