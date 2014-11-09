#ifndef _TCP_CLIENT_SETUP_H
#define _TCP_CLIENT_SETUP_H

#include <string>
#include "Comms/CommunicationChannelSetup.h"

namespace device_emulator {

class TCPClientSetup;
typedef boost::shared_ptr<TCPClientSetup> TCPClientSetupPtr;

/*! 
    This class represents a setup for a TCP Client
*/
class TCPClientSetup : public CommunicationChannelSetup {
 public:
    TCPClientSetup(const std::string &host, const std::string &port) : _host(host), _port(port) { };

    std::string GetPort() const { return _port; }
    std::string GetHost() const { return _host; }

private:

  std::string _host;
  std::string _port;
};

} // namespace

#endif
