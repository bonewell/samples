#include <boost/asio.hpp>

#include "tcp_connection.h"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

class TcpConnection;

class Server {
  public:
    explicit Server(boost::asio::io_context& io_context);

  private:
    void start_accept();
    void handle_accept(TcpConnection::pointer new_conn,
                       const boost::system::error_code& error);
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};