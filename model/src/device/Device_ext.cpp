#include "device/Device.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

void export_Device()
{
    class_<Device>("Device", init<const std::string>())
        .def("start", &Device::Start)
        .def("stop", &Device::Stop)
        .def("wait", &Device::Wait)
        .def("add_behaviour", &Device::AddBehaviour)
        .def("get_name", &Device::GetName)
        ;
}
