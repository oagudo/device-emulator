#include "device/orders/InfiniteOrderList.h"

namespace device_emulator {

IDeviceOrderPtr InfiniteOrderList::Next() {
    IDeviceOrderPtr order = OrderList::Next();
    Add(order);
    return order;
}

IOrderList* InfiniteOrderList::Clone() const {
    return new InfiniteOrderList(*this);
}

} // namespace

