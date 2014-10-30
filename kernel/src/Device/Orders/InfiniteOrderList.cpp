#include "Device/Orders/InfiniteOrderList.h"

namespace device_emulator {

IDeviceOrderPtr InfiniteOrderList::Next() {
    IDeviceOrderPtr order = OrderList::Next();
    Add(order);
    return order;
}

} // namespace

