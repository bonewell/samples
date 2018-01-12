#include <map>
#include <vector>
#include <iostream>

using RawData = std::vector<unsigned char>;

struct Data {
  Data(int u, int s, const RawData&& d)
      : unix_time(u),
	time_stamp(s),
	data(std::move(d)) {}
  int unix_time;
  int time_stamp;
  RawData data;
};

using Frames = std::vector<Data>;

struct Network {
  unsigned char type;
  unsigned char id;
};
bool operator<(const Network& a, const Network& b) {
  return (a.type < b.type) || (a.type == b.type && a.id < b.id);
}

using Buffer = std::map<Network, Frames>;

int main() {
  Buffer buf;
  Network n1 = {1, 1};
  Network n2 = {1, 2};
  Network n3 = {2, 1};
  buf[n1] = Frames();
  buf[n2] = Frames();
  buf[n3] = Frames();
  std::cout << "Size, Capacity: " << buf[n1].size() << ", " << buf[n1].capacity() << std::endl;
  std::cout << "Size, Capacity: " << buf[n2].size() << ", " << buf[n2].capacity() << std::endl;
  std::cout << "Size, Capacity: " << buf[n3].size() << ", " << buf[n3].capacity() << std::endl;
  for (auto i = 0; i < 500000; ++i) {
    buf[n1].emplace_back(i + 1, i + 0, RawData(20, 'A'));
  } 
  for (auto i = 0; i < 1000000; ++i) {
    buf[n2].emplace_back(i + 3, i + 2, RawData(20, 'B'));
  } 
  for (auto i = 0; i < 1000000; ++i) {
    buf[n3].emplace_back(i + 5, i + 4, RawData(76, 'C'));
  } 
  std::cout << "Size, Capacity: " << buf[n1].size() << ", " << buf[n1].capacity() << std::endl;
  std::cout << "Size, Capacity: " << buf[n2].size() << ", " << buf[n2].capacity() << std::endl;
  std::cout << "Size, Capacity: " << buf[n3].size() << ", " << buf[n3].capacity() << std::endl;

  int size = sizeof(buf);
  int sizem = sizeof(buf);
  for (const auto& n: buf) {
    size += sizeof(n);
    sizem += sizeof(n);
    for (const auto& f: n.second) {
      size += sizeof(f);
      sizem += sizeof(f);
      sizem += f.data.size();
    }
  }
  std::cout << "Total size: " << size << ", " << sizem << std::endl;

  return 0;
}
