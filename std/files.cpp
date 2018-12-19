#include <iostream>
#include <filesystem>  // c++17

// In order to build -lstdc++fs has to go after .cpp file in the command-line
// g++ -std=c++17 files.cpp -lstdc++fs

using namespace std;
using namespace std::filesystem;

int main() {
  path p{"."};

  for(const auto& i: directory_iterator{p}) {
    if (i.is_directory()) {
      cout << "DIR: ";
    }
    cout << i.path().string() << "\n";
  }
}
