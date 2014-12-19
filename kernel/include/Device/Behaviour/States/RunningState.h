#ifndef _RUNNING_STATE_H
#define _RUNNING_STATE_H

#include "DeviceBehaviourState.h"
#include "Device/Behaviour/DeviceBehaviour.h"
#include "Device/Orders/OrderList.h"
#include "StoppedState.h"
#include "FinishedState.h"

namespace device_emulator {

class RunningState : public NonErrorState {
    
    void ExecuteOrders(const DeviceBehaviourPtr &context) {
        while (!context->GetOrders()->Empty() && context->GetState()->AllowToContinue()) {
            context->GetOrders()->Next()->Execute(context);
        }

        if (context->GetState()->AllowToContinue()) {
            transitionTo(context, DeviceBehaviourStatePtr(new FinishedState()));
        }
    }

    void Stop(const DeviceBehaviourPtr &context) { 
        transitionTo(context, DeviceBehaviourStatePtr(new StoppedState()));
    }    
};

} // namespace

#endif
