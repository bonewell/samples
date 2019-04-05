#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream_buffer.hpp>

#include <sstream>
#include <iostream>

namespace io = boost::iostreams;

struct ssl_device : public io::device<io::bidirectional> {
  ssl_device() {}
  ssl_device(const ssl_device& o) : dev_buf{o.dev_buf.str()} {}
  ssl_device& operator=(const ssl_device& o) { dev_buf.str(o.dev_buf.str()); }
  ssl_device(ssl_device&&) = default;
  ssl_device& operator=(ssl_device&&) = default;
  ~ssl_device() = default;
  std::stringbuf dev_buf;
  std::streamsize read(char_type* s, std::streamsize n)
  {
    return dev_buf.sgetn(s, n);
  }
  std::streamsize write(const char_type* s, std::streamsize n)
  {
    return dev_buf.sputn(s, n);
  }
};

int main() {
  ssl_device dev;
  io::stream_buffer<ssl_device> ssl_buf{dev};
  std::iostream ssl{&ssl_buf};
  std::ostream& os = ssl;
  std::istream& is = ssl;
  int x = 5;
  ssl << x << std::flush;
  int z = 0;
  ssl >> z;
  std::cout << z << "\n";
}
