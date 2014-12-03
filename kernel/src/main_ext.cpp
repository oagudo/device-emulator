#include <boost/python.hpp>

void export_IMessage();
void export_DeviceBehaviour();

BOOST_PYTHON_MODULE(DeviceEmulatorKernel_ext)
{
    export_IMessage();
    export_DeviceBehaviour();
}
