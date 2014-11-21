#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "Comms/TCP/TCPEndPoint.h"
#include "Comms/TCP/TCPClientSetup.h"

namespace device_emulator {

class TCPClient;
typedef boost::shared_ptr<TCPClient> TCPClientPtr;

/*!
    \class Represents a TCP client
*/
class TCPClient  : public TCPEndPoint {

public:

    TCPClient(TCPClientSetupPtr setup);
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
    TCPClientSetupPtr getSetup();
};
} // namespace

#endif
