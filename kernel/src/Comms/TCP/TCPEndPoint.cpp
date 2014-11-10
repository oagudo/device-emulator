#include "Comms/TCP/TCPEndPoint.h"
#include "Data/Message.h"

namespace device_emulator {

TCPEndPoint::TCPEndPoint(const ComChannelSetupPtr &setup) : CommunicationChannel(setup) { }

void TCPEndPoint::Send(const IMessagePtr &msg) {
    MessagePtr msgPtr = boost::dynamic_pointer_cast<Message>(msg);
    _io_service.post(boost::bind(&TCPEndPoint::doWrite, this, *(msgPtr.get())));
}

void TCPEndPoint::handleRead(const boost::system::error_code& e) {
    if (!e) {
        _conn->async_read(_msg,
                          boost::bind(&TCPEndPoint::handleRead, this,
                                      boost::asio::placeholders::error));
    } else {
        //std::cerr << e.message() << std::endl;
    }
}

void TCPEndPoint::handleWrite(const boost::system::error_code& e, TCPConnectionPtr conn) {
    if (!e) {
    } else {
        //std::cerr << e.message() << std::endl;
    }
}

void TCPEndPoint::doWrite(const Message &msg) {
    _conn->async_write(msg,
                       boost::bind(&TCPEndPoint::handleWrite, this,
                                   boost::asio::placeholders::error, _conn));
}

void TCPEndPoint::Stop() {
    _io_service.post(boost::bind(&TCPEndPoint::doClose, this));
    _io_service.stop();
    _thread.join();
}

void TCPEndPoint::doClose() {
    if (_conn) {
        _conn->socket().close();
    }
}
}
