#include "Device/Orders/IDeviceOrder.h"
#include "Device/Orders/SendOrder.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;


struct IDeviceOrderWrap : IDeviceOrder, wrapper<IDeviceOrder>
{
    void Execute(const DeviceBehaviourPtr &context) {
        this->get_override("Execute")();
    }
};

void export_IDeviceOrders()
{
    class_<IDeviceOrderWrap, boost::noncopyable>("IDeviceOrder")
        .def("execute", pure_virtual(&IDeviceOrder::Execute))
        ;

    class_<SendOrder, bases<IDeviceOrderWrap> >("SendOrder", init<const IMessagePtr&>())
        ;
}
