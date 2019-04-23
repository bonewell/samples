#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

int main() {
  std::ifstream ifs{"copystream.cpp"};
  std::stringstream ss;
  std::copy(std::istream_iterator<uint8_t>{ifs},
    std::istream_iterator<uint8_t>{},
    std::ostream_iterator<uint8_t>{ss});
  std::cout << ss.str() << "\n";
  return 0;
}
