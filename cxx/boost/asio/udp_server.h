#include <boost/asio.hpp>

#include <array>

using boost::asio::ip::udp;

class UdpConnection;

class UdpServer {
  public:
    UdpServer(boost::asio::io_context& io_context, unsigned short port);

  private:
    void start_receive();
    void handle_receive(const boost::system::error_code& error, size_t size);
    void handle_send(const boost::system::error_code& error, size_t size);
    udp::socket socket_;
    udp::endpoint remote_;
    std::array<unsigned char, 1024> inbuf_;
    std::array<unsigned char, 1024> outbuf_;
};
