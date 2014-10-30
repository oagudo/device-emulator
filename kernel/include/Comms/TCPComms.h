#ifndef _TCP_COMMS_CHANNEL_H
#define _TCP_COMMS_CHANNEL_H

#include "CommunicationChannel.h"

namespace device_emulator {

class TCPComms;
typedef boost::shared_ptr<TCPComms> TCPCommsPtr;

/*!
    This class is responsible for communicating two Devices
    TODO: Implement TCP Send / Receive methods. See Boost Asio
*/
class TCPComms : public CommunicationChannel {
public:
    TCPComms(const ComChannelSetupPtr &setup) : CommunicationChannel(setup) { };

    bool Start();

    void Close();

    void Send(const IMessagePtr &msg);

    void MsgReceived(const IMessagePtr &msg);
};

} // namespace
#endif
