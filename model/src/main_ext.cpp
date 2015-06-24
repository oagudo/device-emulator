#include "log/Logger.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

void export_IDeviceOrders();
void export_IMessage();
void export_DeviceBehaviour();
void export_Device();
void export_CommunicationChannel();

BOOST_PYTHON_MODULE(DeviceEmulatorModel_ext)
{
    class_<Logger, boost::noncopyable>("Logger", no_init)
        .def("init", &Logger::Init).staticmethod("init")
        .def("configure", &Logger::Configure).staticmethod("configure")
        ;


    export_IMessage();
    export_IDeviceOrders();
    export_DeviceBehaviour();
    export_Device();
    export_CommunicationChannel();
}
