#ifndef _TCP_SERVER_SETUP_H
#define _TCP_SERVER_SETUP_H

#include <string>

namespace device_emulator {

/*! 
    This class represents a setup for a TCP Server
*/
class TCPServerSetup {
public:
    TCPServerSetup(const std::string &port) : _port(port) { };
    virtual ~TCPServerSetup() { }

    std::string GetPort() const { return _port; }
        
private:
    std::string _port;
};

} // namespace

#endif
