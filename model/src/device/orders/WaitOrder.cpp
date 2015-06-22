#include <boost/thread/thread.hpp>
#include <boost/make_shared.hpp>
#include "device/orders/WaitOrder.h"

namespace device_emulator {

WaitOrder::WaitOrder(const unsigned int milliseconds) : _milliseconds(milliseconds) {
}

bool WaitOrder::Execute(const DeviceBehaviourPtr &/*context*/) {
    boost::this_thread::sleep( boost::posix_time::milliseconds(_milliseconds) );
    return true;
}

IDeviceOrderPtr WaitOrder::Clone() const {
    return boost::make_shared<WaitOrder>(*this);
}

} // namespace
