#include "tcp_server.h"

#include <iostream>

using boost::asio::ip::tcp;

TcpServer::TcpServer(boost::asio::io_context& io_context)
  : io_context_{io_context},
    acceptor_{io_context_, tcp::endpoint{tcp::v4(), 4545}}
{
  start_accept();
}

void TcpServer::start_accept()
{
  std::cout << "Tcp: start accept\n";
  auto new_conn = TcpConnection::create(io_context_);
  acceptor_.async_accept(new_conn->socket(),
      [new_conn, this](auto error) {
        handle_accept(new_conn, error);
  });
}

void TcpServer::handle_accept(TcpConnection::pointer new_conn,
                           const boost::system::error_code& error)
{
  std::cout << "Tcp: accepted\n";
  if (!error) {
    new_conn->start();
  } else {
    std::cerr << "Tcp: accept error: " << error << "\n";
  }
  start_accept();
}
