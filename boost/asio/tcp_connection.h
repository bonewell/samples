#include <boost/asio.hpp>
#include <memory>
#include <string>

using boost::asio::ip::tcp;

class TcpConnection : private std::enable_shared_from_this<TcpConnection> {
  public:
    using pointer = std::shared_ptr<TcpConnection>;

    static pointer create(boost::asio::io_context& io_context);
    tcp::socket& socket() { return socket_; }
    void start();

  private:
    explicit TcpConnection(boost::asio::io_context& io_context);
    tcp::socket socket_;
    std::string message_;
};
