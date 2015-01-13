#ifndef _COMMUNICATION_CHANNEL_MOCK_H
#define _COMMUNICATION_CHANNEL_MOCK_H

#include "Comms/CommunicationChannel.h"

using namespace device_emulator;

/*!
    \brief CommunicationChannel Mock
*/
class CommsMock : public CommunicationChannel {
public:
    CommsMock() { };

    bool Start() { return true; }

    void Stop() { }

    void Send(const IMessagePtr &/*msg*/) { }

    void OnMsgReceived(const IMessagePtr &msg) { CommunicationChannel::OnMsgReceived(msg); };
};

#endif
