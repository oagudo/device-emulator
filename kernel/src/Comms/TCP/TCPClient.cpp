#include "Comms/TCP/TCPClient.h"
#include "Data/Message.h"

namespace device_emulator {

TCPClient::TCPClient(TCPClientSetupPtr setup) : TCPEndPoint(setup) { }

bool TCPClient::Start() {
    try {

        TCPClientSetupPtr TCPsetup =
            boost::dynamic_pointer_cast<TCPClientSetup>(_setup);

        // Start an accept operation for a new connection
        _conn.reset(new TCPConnection(_io_service));

        // Resolve the host name into an IP address
        boost::asio::ip::tcp::resolver resolver(_io_service);
        boost::asio::ip::tcp::resolver::query query(TCPsetup->GetHost(), TCPsetup->GetPort());
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Start an asynchronous connect operation
        boost::asio::async_connect(_conn->socket(), endpoint_iterator,
                                   boost::bind(&TCPClient::handleConnect, this,
                                               boost::asio::placeholders::error));

        _thread = boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service));

    } catch (std::exception& /*e*/) {
        //std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}


/// Handle completion of a connect operation.
void TCPClient::handleConnect(const boost::system::error_code& e) {
    if (!e) {
        //std::cout << "Successfully bind to server!" << std::endl;
        _conn->async_read(_msg,
                          boost::bind(&TCPClient::handleRead, this,
                                      boost::asio::placeholders::error));
    } else {
        //std::cerr << e.message() << std::endl;
    }
}

}
