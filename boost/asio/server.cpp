#include "server.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context)
  : io_context_{io_context},
    acceptor_{io_context_, tcp::endpoint{tcp::v6(), 4545}}
{
  start_accept();
}

void Server::start_accept()
{
  using namespace std::placeholders;
  auto new_conn = TcpConnection::create(io_context_);
  acceptor_.async_accept(new_conn->socket(),
      std::bind(&Server::handle_accept, this, new_conn, _1));
}

void Server::handle_accept(TcpConnection::pointer new_conn,
                           const boost::system::error_code& error)
{
  if (!error) {
    new_conn->start();
  }
  start_accept();
}
