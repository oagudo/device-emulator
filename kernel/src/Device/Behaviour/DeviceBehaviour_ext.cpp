#include "Device/Behaviour/DeviceBehaviour.h"
#include "Device/Behaviour/States/DeviceBehaviourState.h"
#include "Device/Orders/OrderList.h"
#include "Comms/CommunicationChannel.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

void export_DeviceBehaviour()
{
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

