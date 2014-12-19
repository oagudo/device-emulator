#include "Device/Behaviour/DeviceBehaviour.h"
#include "Device/Behaviour/States/DeviceBehaviourState.h"
#include "Device/Orders/OrderList.h"
#include "Comms/CommunicationChannel.h"
#include "Device/Behaviour/States/ErrorState.h"
#include "Device/Behaviour/States/FinishedState.h"
#include "Device/Behaviour/States/NotStartedState.h"
#include "Device/Behaviour/States/RunningState.h"
#include "Device/Behaviour/States/StoppedState.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

/*struct DeviceBehaviourStateWrap : DeviceBehaviourState, wrapper<DeviceBehaviourState>
{
    bool AllowToContinue() {
        return this->get_override("allow_to_continue")();
    }
    void Start(const DeviceBehaviourPtr &context) {
        if (override n = this->get_override("start"))
            n(context);
        DeviceBehaviourState::Start(context);
    }
    void default_Start(const DeviceBehaviourPtr &context) { this->DeviceBehaviourState::Start(context); }

    void ExecuteOrders(const DeviceBehaviourPtr &context) {
        if (override n = this->get_override("execute_orders"))
            n(context);
        DeviceBehaviourState::ExecuteOrders(context);
    }
    void default_ExecuteOrders(const DeviceBehaviourPtr &context) { this->DeviceBehaviourState::ExecuteOrders(context); }

    void Stop(const DeviceBehaviourPtr &context) {
        if (override n = this->get_override("stop"))
            n(context);
        DeviceBehaviourState::Stop(context);
    }
    void default_Stop(const DeviceBehaviourPtr &context) { this->DeviceBehaviourState::Stop(context); }
};
*/

void export_DeviceBehaviour()
{
    class_<DeviceBehaviourState, DeviceBehaviourStatePtr, boost::noncopyable>("DeviceBehaviourState", no_init)
        //        .def("is_error_state", pure_virtual(&DeviceBehaviourState::IsErrorState))
        //        .def("allow_to_continue", pure_virtual(&DeviceBehaviourState::AllowToContinue))
        ;

    // class_<DeviceBehaviourStateWrap, boost::noncopyable>("DeviceBehaviourState")
    //     .def("allow_to_continue", pure_virtual(&DeviceBehaviourState::AllowToContinue))
    //     .def("start", &DeviceBehaviourStateWrap::Start, &DeviceBehaviourStateWrap::default_Start)
    //     .def("execute_orders", &DeviceBehaviourStateWrap::ExecuteOrders, &DeviceBehaviourStateWrap::default_ExecuteOrders)
    //     .def("stop", &DeviceBehaviourStateWrap::Stop, &DeviceBehaviourStateWrap::default_Stop)
    //     ;

    class_<ErrorState, bases<DeviceBehaviourState> >("ErrorState", init<const std::string>())
        .def("to_string", &ErrorState::ToString)
        .def("allow_to_continue", &ErrorState::AllowToContinue)
        ;

    class_<FinishedState, bases<DeviceBehaviourState> >("FinishedState")
        .def("to_string", &FinishedState::ToString)
        .def("allow_to_continue", &FinishedState::AllowToContinue)
        ;

    class_<NotStartedState, bases<DeviceBehaviourState> >("NotStartedState")
        .def("to_string", &NotStartedState::ToString)
        .def("allow_to_continue", &NotStartedState::AllowToContinue)
        ;

    class_<RunningState, bases<DeviceBehaviourState> >("RunningState")
        .def("to_string", &RunningState::ToString)
        .def("allow_to_continue", &RunningState::AllowToContinue)
        ;

    class_<StoppedState, bases<DeviceBehaviourState> >("StoppedState")
        .def("to_string", &StoppedState::ToString)
        .def("allow_to_continue", &StoppedState::AllowToContinue)
        ;

    //    implicitly_convertible<boost::shared_ptr<ErrorState>, DeviceBehaviourStatePtr >();
    //    implicitly_convertible<boost::shared_ptr<FinishedState>, DeviceBehaviourStatePtr >();

    class_<DeviceBehaviour, DeviceBehaviourPtr, boost::noncopyable>("DeviceBehaviour", init<const std::string, const ComChannelPtr, const OrderListPtr>())
        .add_property("state", &DeviceBehaviour::GetState)
        .add_property("name", &DeviceBehaviour::GetName)
        .add_property("orders", &DeviceBehaviour::GetOrders)
        .add_property("channel", &DeviceBehaviour::GetCommChannel)
        .def("start", &DeviceBehaviour::Start)
        .def("stop", &DeviceBehaviour::Stop)
        .def("wait", &DeviceBehaviour::Wait)
        ;
}
