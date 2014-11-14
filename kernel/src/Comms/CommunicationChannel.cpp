#include "Comms/CommunicationChannel.h"
#include "Device/Behaviour/IDeviceBehaviour.h"
#include "Log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.comms")

bool CommunicationChannel::WantMessage(const unsigned int msgID, const IDeviceBehaviourPtr &who) {
    boost::lock_guard<boost::mutex> lock(_mutexMsgArrived);

    bool received = false;
    if (existsMessage(msgID)) {
        who->OnMessageArrived(_hashArrivedMessages[msgID].front());
        _hashArrivedMessages[msgID].pop();
        received = true;
    }
    else {
        LOG_INFO(logger, "No message '" << msgID << "' ready for " << who->GetName());
        addWaitingForMessage(msgID, who);
    }
    return received;
}

void CommunicationChannel::OnMsgReceived(const IMessagePtr &msg) {
    boost::lock_guard<boost::mutex> lock(_mutexMsgArrived);

    LOG_INFO(logger, "Message '" << msg->GetId() << "' received");
    if (anyDeviceWaitingFor(msg->GetId())) {
        // Notify them!
        _hashWaitingForMessage[msg->GetId()].front()->OnMessageArrived(msg);
        _hashWaitingForMessage[msg->GetId()].pop();
    } else {
        // Adds the message to the receiving queue
        _hashArrivedMessages[msg->GetId()].push(msg);
    }
}

void CommunicationChannel::addWaitingForMessage(unsigned int msgId, const IDeviceBehaviourPtr &who) {
    _hashWaitingForMessage[msgId].push(who);
}

bool CommunicationChannel::existsMessage(const unsigned int msgID) {
    return (_hashArrivedMessages.count(msgID) > 0) &&
           (!_hashArrivedMessages[msgID].empty());
}

bool CommunicationChannel::anyDeviceWaitingFor(const unsigned int msgID) {
    return (_hashWaitingForMessage.count(msgID) > 0) &&
            (!_hashWaitingForMessage[msgID].empty());
}

} // namespace
