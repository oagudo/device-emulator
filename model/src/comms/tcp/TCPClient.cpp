#include "comms/tcp/TCPClient.h"
#include "data/Message.h"
#include "log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.comms.tcp.client")

TCPClient::TCPClient(const TCPClientSetup &setup) : _setup(setup) { }

bool TCPClient::Start() {
    try {

        // Start an accept operation for a new connection
        _conn.reset(new TCPConnection(_io_service));

        // Resolve the host name into an IP address
        boost::asio::ip::tcp::resolver resolver(_io_service);
        boost::asio::ip::tcp::resolver::query query(getSetup().GetHost(), getSetup().GetPort());
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Start an asynchronous connect operation
        boost::asio::async_connect(_conn->socket(), endpoint_iterator,
                                   boost::bind(&TCPClient::handleConnect, boost::static_pointer_cast<TCPClient>(shared_from_this()),
                                               boost::asio::placeholders::error));

        _thread = boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service));

    } catch (std::exception& e) {
        LOG_ERROR(logger, "Error starting connection to server (" << 
                  getSetup().GetHost() << ":" << getSetup().GetPort() << ") [ex:" << e.what() << "]");
        return false;
    }

    return true;
}


/// Handle completion of a connect operation.
void TCPClient::handleConnect(const boost::system::error_code& e) {
    if (!e) {

        LOG_INFO(logger, "Client successfully bind to server (" << 
                 getSetup().GetHost() << ":" << getSetup().GetPort() << ")" );

        _conn->async_read(_msg,
                          boost::bind(&TCPClient::handleRead, boost::static_pointer_cast<TCPClient>(shared_from_this()),
                                      boost::asio::placeholders::error));
    } else {
        LOG_ERROR(logger, "Error when connecting to server (" << 
                  getSetup().GetHost() << ":" << getSetup().GetPort() << " [error:" << e.message() << "]" );
    }
}

const TCPClientSetup& TCPClient::getSetup() {
    return _setup;
}

}
