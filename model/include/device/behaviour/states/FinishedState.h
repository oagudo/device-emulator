#ifndef _FINISHED_STATE_H
#define _FINISHED_STATE_H

#include "DeviceBehaviourState.h"

namespace device_emulator {

class FinishedState : public DeviceBehaviourState {
public:
    static DeviceBehaviourStatePtr Instance();
    std::string ToString() const;
private:
    FinishedState();
};

} // namespace

#endif
