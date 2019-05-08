#include <boost/asio.hpp>

#include <array>
#include <memory>

using boost::asio::ip::tcp;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
  public:
    using pointer = std::shared_ptr<TcpConnection>;

    static pointer create(boost::asio::io_context& io_context);
    tcp::socket& socket() { return socket_; }
    void start();

    ~TcpConnection() noexcept;

  private:
    explicit TcpConnection(boost::asio::io_context& io_context);
    void handle_read(boost::system::error_code error, size_t size);
    void handle_write(boost::system::error_code error, size_t size);
    tcp::socket socket_;
    std::array<unsigned char, 1024> inbuf_;
    std::array<unsigned char, 1024> outbuf_;
};
