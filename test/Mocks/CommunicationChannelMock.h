#ifndef _COMMUNICATION_CHANNEL_MOCK_H
#define _COMMUNICATION_CHANNEL_MOCK_H

#include "Comms/CommunicationChannel.h"
#include "Comms/CommunicationChannelSetup.h"

using namespace device_emulator;

/*!
    \brief CommunicationChannelSetup Mock
*/
class CommsSetupMock : public CommunicationChannelSetup {
 public:
    CommsSetupMock() { };
};

/*!
    \brief CommunicationChannel Mock
*/
class CommsMock : public CommunicationChannel {
public:
    CommsMock() : CommunicationChannel(ComChannelSetupPtr(new CommsSetupMock())) { };

    bool Start() { return true; }

    void Close() { }

    void Send(const IMessagePtr &/*msg*/) { }

    void MsgReceived(const IMessagePtr &msg) { CommunicationChannel::MsgReceived(msg); };
};

#endif
