#include "tcp_connection.h"

#include <iostream>
#include <string>

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& io_context)
{
  return pointer{new TcpConnection{io_context}};
}

TcpConnection::TcpConnection(boost::asio::io_context& io_context)
    : socket_{io_context} {}

TcpConnection::~TcpConnection() noexcept
{
  std::cout << "Tcp: close conn\n";
}

void TcpConnection::start()
{
  std::cout << "Tcp: start conn\n";
  socket_.async_read_some(boost::asio::buffer(inbuf_, inbuf_.size()),
      [self=shared_from_this()](auto error, auto size) {
        self->handle_read(error, size);
  });
}

void TcpConnection::handle_read(boost::system::error_code error, size_t size)
{
  std::cout << "Tcp: read\n";
  if (!error) {
    outbuf_ = inbuf_;
    async_write(socket_, boost::asio::buffer(outbuf_, size),
        [self=shared_from_this()](auto error, auto size) {
          self->handle_write(error, size);
      });
  } else {
    std::cerr << "Tcp: read error=" << error << "\n";
  }
}

void TcpConnection::handle_write(boost::system::error_code error, size_t size)
{
  std::cout << "Tcp: write\n";
  if (!error) {
    std::string message{std::begin(inbuf_), std::begin(inbuf_) + size};
    std::cout << "Tcp: echo=" << message << "\n";
  } else {
    std::cerr << "Tcp: write error=" << error << "\n";
  }
}
