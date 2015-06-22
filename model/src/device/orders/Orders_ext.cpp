#include "device/orders/IDeviceOrder.h"
#include "device/orders/SendOrder.h"
#include "device/orders/ReceiveOrder.h"
#include "device/orders/WaitOrder.h"
#include "device/orders/IOrderList.h"
#include "device/orders/OrderList.h"
#include "device/orders/InfiniteOrderList.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;


struct IDeviceOrderWrap : IDeviceOrder, wrapper<IDeviceOrder>
{
    bool Execute(const DeviceBehaviourPtr &context) {
        return this->get_override("execute")(context);
    }
};

struct OrderListWrap : OrderList, wrapper<OrderList>
{
    IDeviceOrderPtr Next() {
        if (override n = this->get_override("next"))
            return n();
        return OrderList::Next();
    }

    IDeviceOrderPtr default_Next() { return this->OrderList::Next(); }
};

void export_IDeviceOrders()
{
    class_<IDeviceOrderPtr>("IDeviceOrder")
        ;

    class_<IDeviceOrderWrap, boost::noncopyable>("IDeviceOrder")
        .def("execute", pure_virtual(&IDeviceOrder::Execute))
        ;

    class_<SendOrder, bases<IDeviceOrder> >("SendOrder", init<const Message&>())
        .def("execute", &SendOrder::Execute)
        ;

    class_<ReceiveOrder, bases<IDeviceOrder> >("ReceiveOrder", init<const unsigned int, const unsigned int>())
        .def("execute", &ReceiveOrder::Execute)
        ;

    class_<WaitOrder, bases<IDeviceOrder> >("WaitOrder", init<const unsigned int>())
        .def("execute", &WaitOrder::Execute)
        ;

    class_<IOrderList, boost::noncopyable>("IOrderList", no_init)
        ;

    class_<OrderList, bases<IOrderList> >("OrderList")
        ;

    class_<InfiniteOrderList, bases<OrderList> >("InfiniteOrderList")
        .def("next", &InfiniteOrderList::Next)
        .def("add", &InfiniteOrderList::Add)
        .def("empty", &InfiniteOrderList::Empty)
        .def("count", &InfiniteOrderList::Count)
        ;

    class_<OrderListWrap, boost::noncopyable>("OrderList")
        .def("next", &OrderList::Next, &OrderListWrap::default_Next)
        .def("add", &OrderList::Add)
        .def("empty", &OrderList::Empty)
        .def("count", &OrderList::Count)
        ;
}
