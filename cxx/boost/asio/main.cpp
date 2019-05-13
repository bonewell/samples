#include <boost/asio.hpp>
#include <iostream>

#include "tcp_server.h"
#include "udp_server.h"

using namespace std::literals;

int main(int argc, char* argv[])
try {
  boost::asio::io_context io_context;
  TcpServer tcp_server{io_context, 4545};
  UdpServer udp_server{io_context, 4545};
  std::cout << "Run\n";
  io_context.run();
  return 0;
}
catch(const std::exception& error) {
  std::cerr << "Error: " << error.what() << "\n";
  return 1;
}
catch(...) {
  std::cerr << "Unknown error\n";
  return 1;
}
