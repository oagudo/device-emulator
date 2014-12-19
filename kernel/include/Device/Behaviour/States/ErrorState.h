#ifndef _ERROR_STATE_H
#define _ERROR_STATE_H

#include "DeviceBehaviourState.h"

namespace device_emulator {

class ErrorState : public DeviceBehaviourState {

public:
    ErrorState(const std::string &errorMsg) : _errorMsg(errorMsg) { }
    std::string GetErrorMsg() const { return _errorMsg; }
    std::string ToString() const { return "Error"; }
private:
    std::string _errorMsg;
};

} // namespace

#endif
