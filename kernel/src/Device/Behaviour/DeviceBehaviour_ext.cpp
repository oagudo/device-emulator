#include "Device/Behaviour/DeviceBehaviour.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

void export_DeviceBehaviour()
{
    class_<DeviceBehaviour, DeviceBehaviourPtr, boost::noncopyable>("DeviceBehaviour", init<const std::string, const ComChannelPtr, const OrderListPtr>())
        //        .def("to_string", pure_virtual(&IMessage::ToString))
        ;
}

