#ifndef _RUNNING_STATE_H
#define _RUNNING_STATE_H

#include "DeviceBehaviourState.h"
#include "Device/Behaviour/DeviceBehaviour.h"
#include "Device/Orders/OrderList.h"
#include "StoppedState.h"
#include "FinishedState.h"

namespace device_emulator {

class RunningState : public DeviceBehaviourState {
public:    
    std::string ToString() const { return "Running"; }
protected:
    void ExecuteOrders(const DeviceBehaviourPtr &context) const {
        while (!context->GetOrders()->Empty() && 
               (context->GetState()->ToString() == "Running")) {
            context->GetOrders()->Next()->Execute(context);
        }

        if (context->GetState()->ToString() == "Running") {
            transitionTo(context, DeviceBehaviourStatePtr(new FinishedState()));
        }
    }

    void Stop(const DeviceBehaviourPtr &context) const { 
        transitionTo(context, DeviceBehaviourStatePtr(new StoppedState()));
    }    
};

} // namespace

#endif
