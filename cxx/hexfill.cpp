#include <array>
#include <iomanip>
#include <iostream>
#include <sstream>

using Digest = std::array<unsigned char, 16>;
namespace {
  std::string DigestToString(const Digest& digest)
  {
    std::stringstream ss;
    ss << std::hex;
    for (auto x: digest) {
      ss << std::setw(2) << std::setfill('0') << short{x};
    }
    return ss.str();
  }
}  // namespace

int main(int argc, char* argv[]) {
  std::cout << "bin: " << argv[0] << "\n";

  Digest d{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  std::cout << DigestToString(d) << "\n";
}
