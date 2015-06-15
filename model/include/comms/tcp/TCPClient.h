#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

#include "comms/tcp/TCPEndPoint.h"
#include "comms/tcp/TCPClientSetup.h"

namespace device_emulator {

/*!
    \class Represents a TCP client
*/
class TCPClient  : public TCPEndPoint {

public:

    TCPClient(const TCPClientSetup &setup);
    virtual ~TCPClient() { }
    bool Start();

private:
    
    /*!
        \brief Handles a new client connection
     */
    void handleConnect(const boost::system::error_code& e);
    
    /*!
        \brief Retrieves the current client setup
     */
    const TCPClientSetup& getSetup();

    TCPClientSetup _setup;
};
} // namespace

#endif
