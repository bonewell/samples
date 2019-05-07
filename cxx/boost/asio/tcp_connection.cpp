#include "tcp_connection.h"

#include <iostream>

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& io_context)
{
  return pointer{new TcpConnection(io_context)};
}

TcpConnection::TcpConnection(boost::asio::io_context& io_context)
    : socket_{io_context} {}

void TcpConnection::start()
{
  std::cout << "Start conn\n";
  using namespace std::placeholders;
  message_ = "da";
  auto self = shared_from_this();
  std::cout << std::boolalpha << bool{self} << "\n";
  async_write(socket_, boost::asio::buffer(message_),
      [self=self](auto error, auto size) {
          self->handle_write(error, size);
  });
}

void TcpConnection::handle_write(boost::system::error_code error, size_t size)
{
  std::cout << "Sent mesaage\n";
}
