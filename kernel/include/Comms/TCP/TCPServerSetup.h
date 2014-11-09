#ifndef _TCP_SERVER_SETUP_H
#define _TCP_SERVER_SETUP_H

#include <string>
#include "Comms/CommunicationChannelSetup.h"

namespace device_emulator {

class TCPServerSetup;
typedef boost::shared_ptr<TCPServerSetup> TCPServerSetupPtr;

/*! 
    This class represents a setup for a TCP Server
*/
class TCPServerSetup : public CommunicationChannelSetup {
public:
    TCPServerSetup(const std::string &port) : _port(port) { };

    std::string GetPort() const { return _port; }
        
private:
    std::string _port;
};

} // namespace

#endif
