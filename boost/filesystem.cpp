#include <boost/filesystem.hpp>
#include <iostream>

int main() {
  std::string path = boost::filesystem::current_path().string();
  std::cout << path << std::endl;
  return 0;
}
