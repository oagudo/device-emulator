#ifndef _TCP_CLIENT_SETUP_H
#define _TCP_CLIENT_SETUP_H

#include <string>

namespace device_emulator {

/*! 
    This class represents a setup for a TCP Client
*/
class TCPClientSetup {
 public:
    TCPClientSetup(const std::string &host, const std::string &port) : _host(host), _port(port) { };
    virtual ~TCPClientSetup() { }

    std::string GetPort() const { return _port; }
    std::string GetHost() const { return _host; }

private:

  std::string _host;
  std::string _port;
};

} // namespace

#endif
