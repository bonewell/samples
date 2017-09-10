#include <iostream>
#include <sstream>

// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// open

// close
#include <unistd.h>
// close

// ioctl
#include <sys/ioctl.h>
// ioctl

// ifreq
#include <net/if.h>
// ifreq

// TUNSETIFF
#ifdef __QNXNTO__
#  include <net/if_tun.h>
#else
#  include <linux/if_tun.h>
#endif
// TUNSETIFF

// strerror
#include <string.h>
// strerror

// errno
#include <errno.h>
// errno

// sockaddr_in
#include <netinet/in.h>
// sockaddr_in

// inet_pton
#include <sys/socket.h>
#include <arpa/inet.h>
// inet_pton

// pthread
#include <pthread.h>
// pthread

// pcap
#include <pcap.h>
// pcap

// tcphdr
#include <netinet/tcp.h>
// tcphdr

// ip
#include <netinet/ip.h>
// ip

const char* kNetToSniff = "en0";

struct pcap_fds {
  pcap_t *fd_in;
  pcap_t *fd_out;
};

int open_sock() {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not create socket with error: " << error << std::endl;
  }
  return fd;
}
bool create_tun_interface(int sock, ifreq *ifr) {
  int ret = ioctl(sock, SIOCIFCREATE, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not create tun with error: " << error << std::endl;
  }
  return ret != -1;
}
void destroy_tun_interface(int sock, ifreq *ifr) {
  int ret = ioctl(sock, SIOCIFDESTROY, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not destroy tun with error: " << error << std::endl;
  }
}
void fill_addr(const char *ip, sockaddr *addr) {
  std::cout << "Fill addr\n";
  sockaddr_in *tmp = (sockaddr_in*) addr;
  tmp->sin_len = sizeof(*tmp);
  tmp->sin_family = AF_INET;
  inet_aton(ip, &tmp->sin_addr);
  std::cout << "Ip " << ip << " was parsed successful: 0x" << std::hex << (uint32_t) tmp->sin_addr.s_addr << std::dec << std::endl;
}
void set_ip(int sock, ifreq *ifr) {
  std::cout << "Set ip\n";
  int ret = ioctl(sock, SIOCSIFADDR, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not set ip with error: " << error << std::endl;
  }
}
void get_ip(int sock, ifreq *ifr) {
  int ret = ioctl(sock, SIOCGIFADDR, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not get ip with error: " << error << std::endl;
  }
  sockaddr_in *sin = (sockaddr_in *) &ifr->ifr_addr;
  const char *ip = inet_ntoa(sin->sin_addr);
  std::cout << "Ip: " << ip << std::endl;
}
void set_netmask(int sock, ifreq *ifr) {
  std::cout << "Set netmask\n";
  int ret = ioctl(sock, SIOCSIFNETMASK, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not set mask with error: " << error << std::endl;
  }
}
void get_netmask(int sock, ifreq *ifr) {
  int ret = ioctl(sock, SIOCGIFNETMASK, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not set mask with error: " << error << std::endl;
  }
  sockaddr_in *sin = (sockaddr_in *) &ifr->ifr_addr;
  const char *ip = inet_ntoa(sin->sin_addr);
  std::cout << "Netmask: " << ip << std::endl;
}
void set_dest_ip(int sock, ifreq *ifr) {
  std::cout << "Set dest ip\n";
  int ret = ioctl(sock, SIOCSIFDSTADDR, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not set dest ip with error: " << error << std::endl;
  }
}
void get_dest_ip(int sock, ifreq *ifr) {
  int ret = ioctl(sock, SIOCGIFDSTADDR, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not get dest ip with error: " << error << std::endl;
  }
  sockaddr_in *sin = (sockaddr_in *) &ifr->ifr_dstaddr;
  const char *ip = inet_ntoa(sin->sin_addr);
  std::cout << "Dest ip: " << ip << std::endl;
}
void get_mtu(int sock, ifreq *ifr) {
  int ret = ioctl(sock, SIOCGIFMTU, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not set dest ip with error: " << error << std::endl;
  }
  std::cout << "Mtu: " << ifr->ifr_mtu << std::endl;
}
void set_flags(int sock, ifreq *ifr) {
  std::cout << "Set flags\n";
  int ret = ioctl(sock, SIOCSIFFLAGS, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not set flags with error: " << error << std::endl;
  }
}
void fill_name(const std::string& name, ifreq *ifr) {
  strlcpy(ifr->ifr_name, name.c_str(), sizeof(ifr->ifr_name));
  std::cout << "Name: " << ifr->ifr_name << std::endl;
}
short int get_flags(int sock, const std::string& name) {
  ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));
  fill_name(name, &ifr);
  int ret = ioctl(sock, SIOCGIFFLAGS, ifr);
  if (ret == -1) {
    std::string error(strerror(errno));
    std::cout << "Could not get flags with error: " << error << std::endl;
    return 0;
  }
  return ifr.ifr_flags;
}
void do_injection(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer) {
    pcap_t *fd = reinterpret_cast<pcap_t*>(args);
    std::cout << "To inject (len, caplen): " << header->len << ", " << header->caplen << std::endl;
    int size = pcap_inject(fd, buffer, header->caplen);
    if (size == -1) {
      std::cout << "Error of inject: " << pcap_geterr(fd) << std::endl;
    } else {
      std::cout << "Success written: " << size << std::endl;
    }
}
void display_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer) {
  std::cout << "Smell (len, caplen): " << header->len << ", " << header->caplen << std::endl;
}
void* inject_thread(void* param) {
    std::cout << "Start inject\n";
    pcap_fds *fds = (pcap_fds*) param;
    int ret = pcap_loop(fds->fd_in, -1, &do_injection, reinterpret_cast<u_char*>(fds->fd_out));
    if (ret == -1) {
      std::cout << "Error loop: " << pcap_geterr(fds->fd_in) << std::endl;
    }
    pcap_close(fds->fd_out);
    pcap_close(fds->fd_in);
    std::cout << "Stop inject\n";
    return 0;
}
void* sniff_thread(void* param) {
    std::cout << "Start sniff\n";
    pcap_t *fd = (pcap_t*) param;
    int ret = pcap_loop(fd, -1, &display_packet, NULL);
    if (ret == -1) {
      std::cout << "Error loop: " << pcap_geterr(fd) << std::endl;
    }
    pcap_close(fd);
    std::cout << "Stop sniff\n";
    return 0;
}
void create_tun(const std::string& name) {
  ifreq ifr;
  memset(&ifr, 1, sizeof(ifr));
  fill_name(name, &ifr);
  int sock = open_sock();
  bool created = create_tun_interface(sock, &ifr);
  if (created) {
    fill_addr("10.8.0.1", &ifr.ifr_addr);
    set_ip(sock, &ifr);
    fill_addr("10.8.0.2", &ifr.ifr_dstaddr);
    set_dest_ip(sock, &ifr);
    fill_addr("255.255.255.0", &ifr.ifr_addr);
    set_netmask(sock, &ifr);
    ifr.ifr_flags = IFF_UP | IFF_NOARP;
    set_flags(sock, &ifr);
  }
  close(sock);
}
void destroy_tun(const std::string& name) {
  ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));
  int sock = open_sock();
  fill_name(name, &ifr);
  destroy_tun_interface(sock, &ifr);
  close(sock);
}
void info_tun(const std::string& name) {
  ifreq ifr;
  int sock = open_sock();
  memset(&ifr, 0, sizeof(ifr));
  fill_name(name, &ifr);
  get_ip(sock, &ifr);
  memset(&ifr, 0, sizeof(ifr));
  fill_name(name, &ifr);
  get_dest_ip(sock, &ifr);
  memset(&ifr, 0, sizeof(ifr));
  fill_name(name, &ifr);
  get_netmask(sock, &ifr);
  memset(&ifr, 0, sizeof(ifr));
  fill_name(name, &ifr);
  get_mtu(sock, &ifr);
  close(sock);
}
void sniff(const std::string& name, const std::string& time) {
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *fd = pcap_open_live(name.c_str(), 65535, 0, 10, errbuf);
  if (fd) {
    pthread_t t;
    pthread_create(&t, NULL, &sniff_thread, (void*) fd);
    std::stringstream stream(time);
    uint value = 0;
    stream >> value;
    std::cout << "Waiting " << value << " secs\n";
    sleep(value);
    pcap_breakloop(fd);
    pthread_join(t,0);
  } else {
    std::cout << "Couldn't open " << name << " handle: " << errbuf << std::endl;
  }
}
void inject(const std::string& name, const std::string& time) {
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *fd = pcap_open_live(kNetToSniff, 65535, 0, 10, errbuf);
  pcap_t *fd2 = pcap_open_live(name.c_str(), 65535, 0, 10, errbuf);
  if (fd && fd2) {
    pcap_fds fds = { fd, fd2 };
    pthread_t t;
    pthread_create(&t, NULL, &inject_thread, (void*) &fds);
    std::stringstream stream(time);
    uint value = 0;
    stream >> value;
    std::cout << "Waiting " << value << " secs\n";
    sleep(value);
    pcap_breakloop(fd);
    pthread_join(t,0);
  } else {
    std::cout << "Couldn't open en0, " << name << " handle: (" <<
        (bool) fd << ", "<< (bool) fd2 << ") " << errbuf << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::string time;
  std::string command;
  std::string name;
  switch (argc) {
    case 4: time = std::string(argv[3]);
    case 3: command = std::string(argv[2]);
    case 2: name = std::string(argv[1]); break;
    default: std::cout << "Usage: ";
      std::cout << argv[0] << " <name> [create|destroy|info]\n";
      std::cout << argv[0] << " <name> [sniff|inject] <time>\n";
      return 0;
  }

  if (command == "create") {
    create_tun(name);
  } else if (command == "destroy") {
    destroy_tun(name);
  } else if (command == "info") {
    info_tun(name);
  } else if (command == "sniff") {
    sniff(name, time);
  } else if (command == "inject") {
    inject(name, time);
  }

  return 0;
}
