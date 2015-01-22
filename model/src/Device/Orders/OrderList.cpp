#include <boost/assert.hpp>
#include "Device/Orders/OrderList.h"
#include "Device/Orders/IDeviceOrder.h"

namespace device_emulator {

void OrderList::Add(const IDeviceOrderPtr &order) {
    _queue.push(order);
}

IDeviceOrderPtr OrderList::Next() {
    BOOST_ASSERT(Count() > 0);
    IDeviceOrderPtr order = _queue.front();
    _queue.pop();
    return order;
}

bool OrderList::Empty() const {
    return _queue.empty();
}

unsigned int OrderList::Count() const {
    return _queue.size();
}

} // namespace

