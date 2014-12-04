#include "Device/Orders/IDeviceOrder.h"
#include "Device/Orders/SendOrder.h"
#include "Device/Orders/ReceiveOrder.h"
#include "Device/Orders/WaitOrder.h"
#include "Device/Orders/OrderList.h"
#include "Device/Orders/InfiniteOrderList.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;


struct IDeviceOrderWrap : IDeviceOrder, wrapper<IDeviceOrder>
{
    void Execute(const DeviceBehaviourPtr &context) {
        this->get_override("Execute")();
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

    class_<SendOrder, bases<IDeviceOrder> >("SendOrder", init<const IMessagePtr&>())
        .def("execute", &SendOrder::Execute)
        ;

    class_<ReceiveOrder, bases<IDeviceOrder> >("ReceiveOrder", init<const unsigned int, const unsigned int>())
        .def("execute", &ReceiveOrder::Execute)
        ;

    class_<WaitOrder, bases<IDeviceOrder> >("WaitOrder", init<const unsigned int>())
        .def("execute", &WaitOrder::Execute)
        ;

    class_<OrderList, OrderListPtr>("OrderList")
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
