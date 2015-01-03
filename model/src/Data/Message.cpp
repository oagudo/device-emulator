#include <iostream>

#include "Data/Message.h"

namespace device_emulator {

std::string Message::ToString() const {
    return _msgContent;
}

std::vector<unsigned char> Message::ToVector() const {
    std::vector<unsigned char> vector;
    for(unsigned int charIndex = 0; charIndex < _msgContent.length(); charIndex++) {
            vector.push_back((unsigned char)_msgContent[charIndex]);
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
