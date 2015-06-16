#include "comms/CommunicationChannel.h"
#include "data/Message.h"
#include "device/behaviour/DeviceBehaviour.h"
#include "log/Logger.h"

namespace device_emulator {

DEFINE_LOGGER(logger, "emulator.comms")

CommunicationChannel::CommunicationChannel() { }

CommunicationChannel::~CommunicationChannel() { }

bool CommunicationChannel::WantMessage(const unsigned int msgID,
                                       const ComChannelReceiveCallback &callback) {

    boost::lock_guard<boost::mutex> lock(_mutexMsgArrived);

    bool received = false;
    if (existsMessage(msgID)) {
        auto msg = _hashArrivedMessages[msgID].front();
        callback(msg);
        _hashArrivedMessages[msgID].pop();
        received = true;
    }
    else {
        LOG_INFO(logger, "There is no message with id = '" << msgID);
        addWaitingForMessage(msgID, callback);
    }
    return received;
}

void CommunicationChannel::OnMsgReceived(const Message &msg) {
    boost::lock_guard<boost::mutex> lock(_mutexMsgArrived);

    LOG_INFO(logger, "Message '" << msg.GetId() << "' received");
    if (anyWaitingForMessage(msg.GetId())) {
        // Notify them!
        auto callback = _hashWaitingForMessage[msg.GetId()].front();
        callback(msg);
        _hashWaitingForMessage[msg.GetId()].pop();
    } else {
        // Adds the message to the receiving queue
        _hashArrivedMessages[msg.GetId()].push(msg);
    }
}

void CommunicationChannel::addWaitingForMessage(unsigned int msgId,
                                                const ComChannelReceiveCallback &callback) {
    _hashWaitingForMessage[msgId].push(callback);
}

bool CommunicationChannel::existsMessage(const unsigned int msgID) {
    return (_hashArrivedMessages.count(msgID) > 0) &&
           (!_hashArrivedMessages[msgID].empty());
}

bool CommunicationChannel::anyWaitingForMessage(const unsigned int msgID) {
    return (_hashWaitingForMessage.count(msgID) > 0) &&
            (!_hashWaitingForMessage[msgID].empty());
}

} // namespace
