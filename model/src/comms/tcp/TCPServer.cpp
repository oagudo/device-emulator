#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include "comms/tcp/TCPServer.h"
#include "log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.comms.tcp.server")

TCPServer::TCPServer(const TCPServerSetup &setup) : _setup(setup) { }

bool TCPServer::Start() {
    try {
        _acceptorPtr = boost::make_shared<boost::asio::ip::tcp::acceptor>(
                                              _io_service,
                                              boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                              boost::lexical_cast<int>(getSetup().GetPort())));
        // Starts a new connection
        auto newConn = boost::make_shared<TCPConnection>(_acceptorPtr->get_io_service());

        _acceptorPtr->async_accept(newConn->socket(),
                                   boost::bind(&TCPServer::handleAccept, this,
                                               boost::asio::placeholders::error, newConn));
        
        // Boost asio loop in other thread
        _thread = boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service));

    } catch (std::exception &e) {
        LOG_ERROR(logger, "Error starting listening on port (" << 
                  getSetup().GetPort() << ") [ex:" << e.what() << "]" );
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
        LOG_INFO(logger, "Successfully accepted new connection to port (" << 
                 getSetup().GetPort() << ")" );

        _conn = conn;

        // Starts reading data from the socket
        conn->async_read(_msg,
                         boost::bind(&TCPServer::handleRead, this,
                                     boost::asio::placeholders::error));

    } else {
        LOG_ERROR(logger, "Error when accepting a new connection to port (" << 
                  getSetup().GetPort() << ") [error:" << e.message() << "]" );
    }

    // Do not starts a new accept operation as only one client can be connected
}

const TCPServerSetup& TCPServer::getSetup() {
    return _setup;
}

}
