#include "server.h"

#include <iostream>

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context)
  : io_context_{io_context},
    acceptor_{io_context_, tcp::endpoint{tcp::v4(), 4545}}
{
  start_accept();
}

void Server::start_accept()
{
  std::cout << "Start accept\n";
  using namespace std::placeholders;
  auto new_conn = TcpConnection::create(io_context_);
  acceptor_.async_accept(new_conn->socket(),
      [conn=new_conn, this](auto error) {
          handle_accept(conn, error);
  });
}

void Server::handle_accept(TcpConnection::pointer new_conn,
                           const boost::system::error_code& error)
{
  std::cout << "accepted\n";
  if (!error) {
    new_conn->start();
  }
  start_accept();
}
