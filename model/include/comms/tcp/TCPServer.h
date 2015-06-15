#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H

#include "comms/tcp/TCPEndPoint.h"
#include "comms/tcp/TCPServerSetup.h"

namespace device_emulator {

/*!
    \class Represents a TCP Server
 */
class TCPServer : public TCPEndPoint {

public:

    TCPServer(const TCPServerSetup &setup);
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
    const TCPServerSetup& getSetup();

    /*!
        \brief Acceptor object used for accepting new conenctions
     */
    boost::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptorPtr;

    TCPServerSetup _setup;
};

} // namespace s11n_example
#endif
