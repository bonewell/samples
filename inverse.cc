#include <iostream>

int main() {
  unsigned char v = 2;
  unsigned char nv = 1;
  unsigned char iv = ~v;
  unsigned char niv = ~nv;
//  bool b = iv == (~v);
  bool b = iv == niv;
  std::cout << std::boolalpha << b << std::endl;
  std::cout << std::hex << v << " " << iv << " " << niv << std::endl;
  return 0;
}
