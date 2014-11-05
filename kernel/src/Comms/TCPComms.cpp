#include <iostream>

#include "Comms/TCPComms.h"
#include "Device/Behaviour/IDeviceBehaviour.h"

namespace device_emulator {

bool TCPComms::Start() {
    // TODO: Implement
    return true;
}

void TCPComms::Close() {
    // TODO: Implement
}

void TCPComms::Send(const IMessagePtr &msg) {
    // TODO: Implement
}


void TCPComms::OnMsgReceived(const IMessagePtr &msg) {
    // TODO: Implement
    CommunicationChannel::OnMsgReceived(msg);
}

} // namespace
