#include "data/Message.h"

namespace device_emulator {

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

bool Message::IsValid() const {
  // TODO: Implement
  return true;
}

} // namespace
