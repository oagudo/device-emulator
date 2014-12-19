#ifndef _ERROR_STATE_H
#define _ERROR_STATE_H

#include "DeviceBehaviourState.h"

namespace device_emulator {

class ErrorState : public DeviceBehaviourState {

public:
    static DeviceBehaviourStatePtr Instance();
    std::string ToString() const;
private:
    ErrorState();
};

} // namespace

#endif
