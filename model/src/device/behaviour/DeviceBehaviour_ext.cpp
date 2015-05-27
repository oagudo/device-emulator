#include "device/behaviour/DeviceBehaviour.h"
#include "device/behaviour/states/DeviceBehaviourState.h"
#include "device/orders/IOrderList.h"
#include "comms/CommunicationChannel.h"
#include "device/behaviour/states/ErrorState.h"
#include "device/behaviour/states/FinishedState.h"
#include "device/behaviour/states/NotStartedState.h"
#include "device/behaviour/states/RunningState.h"
#include "device/behaviour/states/StoppedState.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

void export_DeviceBehaviour()
{
    class_<DeviceBehaviourState, DeviceBehaviourStatePtr, boost::noncopyable>("DeviceBehaviourState", no_init)
        ;

    class_<ErrorState, bases<DeviceBehaviourState> >("ErrorState", no_init)
        .def("instance", &ErrorState::Instance).staticmethod("instance")
        .def("to_string", &ErrorState::ToString)
        ;

    class_<FinishedState, bases<DeviceBehaviourState> >("FinishedState", no_init)
        .def("instance", &FinishedState::Instance).staticmethod("instance")
        .def("to_string", &FinishedState::ToString)
        ;

    class_<NotStartedState, bases<DeviceBehaviourState> >("NotStartedState", no_init)
        .def("instance", &NotStartedState::Instance).staticmethod("instance")
        .def("to_string", &NotStartedState::ToString)
        ;

    class_<RunningState, bases<DeviceBehaviourState> >("RunningState", no_init)
        .def("instance", &RunningState::Instance).staticmethod("instance")
        .def("to_string", &RunningState::ToString)
        ;

    class_<StoppedState, bases<DeviceBehaviourState> >("StoppedState", no_init)
        .def("instance", &StoppedState::Instance).staticmethod("instance")
        .def("to_string", &StoppedState::ToString)
        ;

    //    implicitly_convertible<boost::shared_ptr<ErrorState>, DeviceBehaviourStatePtr >();
    //    implicitly_convertible<boost::shared_ptr<FinishedState>, DeviceBehaviourStatePtr >();

    class_<DeviceBehaviour, DeviceBehaviourPtr, boost::noncopyable>("DeviceBehaviour", init<const std::string, const ComChannelPtr, const IOrderList&>())
        .add_property("state", &DeviceBehaviour::GetState)
        .add_property("name", &DeviceBehaviour::GetName)
        .add_property("orders", make_function(&DeviceBehaviour::GetOrders, return_value_policy<reference_existing_object>()) )
        .add_property("channel", &DeviceBehaviour::GetCommChannel)
        .def("start", &DeviceBehaviour::Start)
        .def("stop", &DeviceBehaviour::Stop)
        .def("wait", &DeviceBehaviour::Wait)
        ;
}
