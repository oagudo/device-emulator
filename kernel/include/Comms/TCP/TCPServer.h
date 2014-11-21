#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "Comms/TCP/TCPEndPoint.h"
#include "Comms/TCP/TCPServerSetup.h"

namespace device_emulator {

class TCPServer;
typedef boost::shared_ptr<TCPServer> TCPServerPtr;

/*!
    \class Represents a TCP Server
 */
class TCPServer : public TCPEndPoint {

public:

    TCPServer(TCPServerSetupPtr setup);
    virtual ~TCPServer() { }
    bool Start();
    void Stop();

private:

    /*!
        \brief handle used for accepting a new connection
     */
    void handleAccept(const boost::system::error_code& e, TCPConnectionPtr conn);

    /*!
        \brief Retrieves the server setup
     */
    TCPServerSetupPtr getSetup();

    /*!
        \brief Acceptor object used for accepting new conenctions
     */
    boost::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptorPtr;
};

} // namespace s11n_example
#endif
