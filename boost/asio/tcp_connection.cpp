#include "tcp_connection.h"

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& io_context)
{
  return pointer{new TcpConnection(io_context)};
}

TcpConnection::TcpConnection(boost::asio::io_context& io_context)
    : socket_{io_context} {}

void TcpConnection::start()
{
/*  message_ = "";
  async_write(socket_, buffer(message_),
      std::bind(&handle_write, std::shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
                */
}
