#include <boost/python.hpp>

void export_IDeviceOrders();
void export_IMessage();
void export_DeviceBehaviour();
void export_CommunicationChannel();

BOOST_PYTHON_MODULE(DeviceEmulatorKernel_ext)
{
    export_IMessage();
    export_IDeviceOrders();
    export_DeviceBehaviour();
    export_CommunicationChannel();

}
