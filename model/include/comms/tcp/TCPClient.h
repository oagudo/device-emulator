#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "comms/tcp/TCPEndPoint.h"
#include "comms/tcp/TCPClientSetup.h"

namespace device_emulator {

class TCPClient;
typedef boost::shared_ptr<TCPClient> TCPClientPtr;

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
