#include <boost/assert.hpp>
#include "device/orders/OrderList.h"
#include "device/orders/IDeviceOrder.h"

namespace device_emulator {

OrderList::OrderList() { }

OrderList::~OrderList() { }

void OrderList::Add(const IDeviceOrderPtr &order) {
    _orders.push_back(order);
}

IDeviceOrderPtr OrderList::Next() {
    BOOST_ASSERT(Count() > 0);
    IDeviceOrderPtr order = _orders.front();
    _orders.erase(_orders.begin());
    return order;
}

bool OrderList::Empty() const {
    return _orders.empty();
}

unsigned int OrderList::Count() const {
    return _orders.size();
}

IOrderListPtr OrderList::Clone() const {
    auto cloned = new OrderList();
    for (auto const& orderPtr : this->_orders)
        cloned->_orders.push_back(orderPtr->Clone());
    return cloned;
}

} // namespace

