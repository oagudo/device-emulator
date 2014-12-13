#include <boost/make_shared.hpp>
#include "Comms/TCP/TCPEndPoint.h"
#include "Data/Message.h"
#include "Log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.comms.tcp")

TCPEndPoint::TCPEndPoint(const ComChannelSetupPtr &setup) : CommunicationChannel(setup) { }

void TCPEndPoint::Send(const IMessagePtr &msg) {
    MessagePtr msgPtr = boost::dynamic_pointer_cast<Message>(msg);
    _io_service.post(boost::bind(&TCPEndPoint::doWrite, boost::static_pointer_cast<TCPEndPoint>(shared_from_this()), *(msgPtr.get())));
}

void TCPEndPoint::handleRead(const boost::system::error_code& e) {
    if (!e) {
        MessagePtr msgPtr(new Message(_msg));
        CommunicationChannel::OnMsgReceived(boost::dynamic_pointer_cast<IMessage>(msgPtr));
        _conn->async_read(_msg,
                          boost::bind(&TCPEndPoint::handleRead, boost::static_pointer_cast<TCPEndPoint>(shared_from_this()),
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
                       boost::bind(&TCPEndPoint::handleWrite, boost::static_pointer_cast<TCPEndPoint>(shared_from_this()) ,
                                   boost::asio::placeholders::error, _conn));
}

void TCPEndPoint::Stop() {
    LOG_INFO(logger, "TCP end point stop requested!");
    _io_service.post(boost::bind(&TCPEndPoint::doClose, boost::static_pointer_cast<TCPEndPoint>(shared_from_this()) ));
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
