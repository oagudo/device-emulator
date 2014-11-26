#ifndef _ERROR_STATE_H
#define _ERROR_STATE_h

#include "DeviceBehaviourState.h"

namespace device_emulator {

class ErrorState : public DeviceBehaviourState {

public:
    ErrorState(const std::string &errorMsg) : _errorMsg(errorMsg) { }
    bool IsErrorState() { return true; }
    bool AllowToContinue() { return false; }
    std::string GetErrorMsg() { return _errorMsg; }
private:
    std::string _errorMsg;
};

} // namespace

#endif
