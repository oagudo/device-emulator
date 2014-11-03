#include "Comms/CommunicationChannel.h"
#include "Device/Behaviour/IDeviceBehaviour.h"

namespace device_emulator {

bool CommunicationChannel::WantMessage(const unsigned int msgID, const IDeviceBehaviourPtr &who) {
    boost::lock_guard<boost::mutex> lock(_mutexMsgArrived);

    bool received = false;
    if (existsMessage(msgID)) {
        who->MessageArrived(_hashArrivedMessages[msgID].front());
        _hashArrivedMessages[msgID].pop();
        received = true;
    }
    else {
        addWaitingForMessage(msgID, who);
    }
    return received;
}

void CommunicationChannel::MsgReceived(const IMessagePtr &msg) {
    boost::lock_guard<boost::mutex> lock(_mutexMsgArrived);

    if (anyDeviceWaitingFor(msg->GetId())) {
        // Notify them!
        _hashWaitingForMessage[msg->GetId()].front()->MessageArrived(msg);
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
