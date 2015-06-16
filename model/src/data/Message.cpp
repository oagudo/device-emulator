#include "data/Message.h"

namespace device_emulator {

Message::Message(const unsigned int msgID, const std::string &msgName, const std::string &msgContent) :
                         _msgId(msgID), _msgName(msgName), _msgContent(msgContent) { };

Message::Message() : _msgId(0), _msgName(""), _msgContent("") { };

Message::~Message() { };

std::string Message::ToString() const {
    return _msgContent;
}

std::vector<unsigned char> Message::ToVector() const {
    std::vector<unsigned char> vector;
    for (auto &character : _msgContent) {
        vector.push_back((unsigned char)character);
    }
    return vector;
}

unsigned int Message::GetId() const { 
    return _msgId; 
}

} // namespace
