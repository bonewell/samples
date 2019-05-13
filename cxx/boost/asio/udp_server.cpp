#include "udp_server.h"

#include <iostream>
#include <string>

using boost::asio::ip::udp;

UdpServer::UdpServer(boost::asio::io_context& io_context, unsigned short port)
  : socket_{io_context, udp::endpoint{udp::v4(), port}}
{
  start_receive();
}

void UdpServer::start_receive()
{
  std::cout << "Udp: start receive\n";
  socket_.async_receive_from(
      boost::asio::buffer(inbuf_, inbuf_.size()), remote_,
      [this](auto error, auto size) {
        handle_receive(error, size);
  });
}

void UdpServer::handle_receive(const boost::system::error_code& error, size_t size)
{
  std::cout << "Udp: received\n";
  if (!error) {
    outbuf_ = inbuf_;
    socket_.async_send_to(boost::asio::buffer(outbuf_, size), remote_,
        [this](auto error, auto size) {
          handle_send(error, size);
    });
  } else {
    std::cerr << "Udp: received error=" << error << "\n";
  }
  start_receive();
}

void UdpServer::handle_send(const boost::system::error_code& error, size_t size)
{
  std::cout << "Udp: sent\n";
  if (!error) {
    std::string message{std::begin(outbuf_), std::begin(outbuf_) + size};
    std::cout << "Upd: echo=" << message << "\n";
  } else {
    std::cerr << "Udp: sent error=" << error << "\n";
  }
}
