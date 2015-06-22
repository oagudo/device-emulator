#include "device/orders/InfiniteOrderList.h"
#include "device/orders/IDeviceOrder.h"

namespace device_emulator {

IDeviceOrderPtr InfiniteOrderList::Next() {
    IDeviceOrderPtr order = OrderList::Next();
    Add(order);
    return order;
}

IOrderListPtr InfiniteOrderList::Clone() const {
    auto cloned = new InfiniteOrderList();
    for (auto const& orderPtr : this->_orders)
        cloned->_orders.push_back(orderPtr->Clone());
    return cloned;
}

} // namespace

