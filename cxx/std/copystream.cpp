#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ios>
#include <sstream>

int main() {
  std::ifstream ifs{"copystream.cpp"};  // text file
  // std::ifstream ifs{"copystream"};  // binary file
  std::stringstream ss;
  ifs >> std::noskipws;
  std::copy(std::istream_iterator<char>{ifs},
    std::istream_iterator<char>{},
    std::ostream_iterator<char>{ss});
  std::cout << ss.str();
  return 0;
}
