#ifndef TCP_ENDPOINT_H
#define TCP_ENDPOINT_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "Comms/CommunicationChannel.h"
#include "Comms/TCP/TCPConnection.h"
#include "Data/Message.h"

namespace device_emulator {

/*!
  \class Represents a TCP end point
*/
class TCPEndPoint  : public CommunicationChannel {

public:

    virtual ~TCPEndPoint() { }
    bool Start() = 0;
    virtual void Stop();
    void Send(const IMessagePtr &msg);

protected:

    // This class cannot be instancied
    TCPEndPoint(const ComChannelSetupPtr &setup);

    /*!
      \brief Handles a new read of a message from the socket
    */
    void handleRead(const boost::system::error_code& e);


    /*!
      \brief Handles a write completion
    */
    void handleWrite(const boost::system::error_code& e, TCPConnectionPtr conn);

    /*!
      \brief Writes a message to the socket
    */
    void doWrite(const Message &msg);

    /*!
      \brief Closes the socket communication
    */
    void doClose();

    /*!
      \brief Thread used for executing the io_service run method
    */
    boost::thread _thread;

    /*!
      \brief TCP connection object
    */
    TCPConnectionPtr _conn;

    /*!
      \brief Boost asio service object
    */
    boost::asio::io_service _io_service;

    /*!
      \brief Message received from the server
    */
    Message _msg;
};
} // namespace

#endif
