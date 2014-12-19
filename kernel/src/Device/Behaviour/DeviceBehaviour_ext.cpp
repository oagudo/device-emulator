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
