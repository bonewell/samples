#include <boost/asio.hpp>

#include "tcp_connection.h"

using boost::asio::ip::tcp;

class TcpConnection;

class TcpServer {
  public:
    TcpServer(boost::asio::io_context& io_context, unsigned short port);

  private:
    void start_accept();
    void handle_accept(TcpConnection::pointer new_conn,
                       const boost::system::error_code& error);
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};
