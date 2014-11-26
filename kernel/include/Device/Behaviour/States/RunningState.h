#ifndef _RUNNING_STATE_H
#define _RUNNING_STATE_h

#include "DeviceBehaviourState.h"
#include "Device/Behaviour/IDeviceBehaviour.h"
#include "Device/Orders/OrderList.h"
#include "StoppedState.h"
#include "FinishedState.h"

namespace device_emulator {

class RunningState : public NonErrorState {
public:
    void ExecuteOrders(const IDeviceBehaviourPtr &context) {
        while (!context->GetOrders()->Empty() && context->GetState()->AllowToContinue()) {
            context->GetOrders()->Next()->Execute(context);
        }

        if (context->GetState()->AllowToContinue()) {
            context->TransitionTo(DeviceBehaviourStatePtr(new FinishedState()));
        }
    }

    void Stop(const IDeviceBehaviourPtr &context) { 
        context->TransitionTo(DeviceBehaviourStatePtr(new StoppedState()));
    }
};

} // namespace

#endif
