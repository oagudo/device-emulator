#include <boost/thread/thread.hpp>
#include "Device/Orders/WaitOrder.h"

namespace device_emulator {

WaitOrder::WaitOrder(const unsigned int milliseconds) : _milliseconds(milliseconds) {
}

void WaitOrder::Execute(const IDeviceBehaviourPtr &/*context*/) {
    boost::this_thread::sleep( boost::posix_time::milliseconds(_milliseconds) );
}

} // namespace
