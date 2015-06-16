#include "comms/tcp/TCPEndPoint.h"
#include "data/Message.h"
#include "log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.comms.tcp")

TCPEndPoint::TCPEndPoint() { }

void TCPEndPoint::Send(const Message &msg) {
    _io_service.post(boost::bind(&TCPEndPoint::doWrite, this, msg));
}

void TCPEndPoint::handleRead(const boost::system::error_code& e) {
    if (!e) {
        CommunicationChannel::OnMsgReceived(_msg);
        _conn->async_read(_msg,
                          boost::bind(&TCPEndPoint::handleRead, this,
                                      boost::asio::placeholders::error));
    } else {
        LOG_ERROR(logger, "Error when reading [error:" << e.message() << "]");
    }
}

void TCPEndPoint::handleWrite(const boost::system::error_code& e, TCPConnectionPtr conn) {
    if (!e) {
    } else {
        LOG_ERROR(logger, "Error when writting [error:" << e.message() << "]");
    }
}

void TCPEndPoint::doWrite(const Message &msg) {
    _conn->async_write(msg,
                       boost::bind(&TCPEndPoint::handleWrite, this,
                                   boost::asio::placeholders::error, _conn));
}

void TCPEndPoint::Stop() {
    LOG_INFO(logger, "TCP end point stop requested!");
    _io_service.post(boost::bind(&TCPEndPoint::doClose, this));
    _io_service.stop();
    _thread.join();
}

void TCPEndPoint::doClose() {
    if (_conn->socket().is_open()) {
          _conn->socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);
          _conn->socket().close();
    }
}
}
