#include <boost/asio.hpp>
#include <iostream>

#include "server.h"

using namespace std::literals;

int main(int argc, char* argv[])
/*try*/ {
  boost::asio::io_context io_context;
  Server server{io_context};
  std::cout << "Run\n";
  io_context.run();
  return 0;
}
/*catch(const std::exception& error) {
  std::cerr << "Error: " << error.what() << "\n";
  return 1;
}
catch(...) {
  std::cerr << "Unknown error\n";
  return 1;
}*/
