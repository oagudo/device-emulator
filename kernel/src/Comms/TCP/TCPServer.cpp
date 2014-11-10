#include <boost/lexical_cast.hpp>
#include "Comms/TCP/TCPServer.h"

namespace device_emulator {

TCPServer::TCPServer(TCPServerSetupPtr setup) : TCPEndPoint(setup) { }

bool TCPServer::Start() {
    try {

        // Gets server configuration
        TCPServerSetupPtr TCPsetup =
            boost::dynamic_pointer_cast<TCPServerSetup>(_setup);

        _acceptorPtr.reset(
                           new boost::asio::ip::tcp::acceptor(_io_service,
                                                              boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                                                             boost::lexical_cast<int>(TCPsetup->GetPort()))));
        // Starts a new connection
        TCPConnectionPtr newConn(new TCPConnection(_acceptorPtr->get_io_service()));

        _acceptorPtr->async_accept(newConn->socket(),
                                   boost::bind(&TCPServer::handleAccept, this,
                                               boost::asio::placeholders::error, newConn));
        
        // Boost asio loop in other thread
        _thread = boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service));

    } catch (std::exception& /*e*/) {
        // std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}


void TCPServer::Stop() {
    _acceptorPtr->close();
    TCPEndPoint::Stop();
}

void TCPServer::handleAccept(const boost::system::error_code& e, TCPConnectionPtr conn) {

    if (!_acceptorPtr->is_open()) {
        return;
    }

    if (!e) {
        // std::cout << "Successfully accepted a new connection" << std::endl;
        _conn = conn;

        // Starts reading data from the socket
        conn->async_read(_msg,
                         boost::bind(&TCPServer::handleRead, this,
                                     boost::asio::placeholders::error));

    } else {
        // std::cout << "Could not accept a new operation" << std::endl;
    }

    // Do not starts a new accept operation as only one client can be connected
}

}
