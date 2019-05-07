#include <iostream>
#include <bitset>

using namespace std;

constexpr auto length = sizeof(char) * 8;
using bs = bitset<length>;

int main() {
  unsigned char v = 3;
  unsigned char iv = ~v;
  cout << int(v) << ": " << bs(v) << ", " << int(iv) << ": " << bs(iv) << "\n";

  char nv = -3;
  char niv = ~nv;
  cout << int(nv) << ": " << bs(nv) << ", " << int(niv) << ": " << bs(niv) << "\n";
}
