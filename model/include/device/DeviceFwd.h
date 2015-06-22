#ifndef _DEVICE_FWD_H_
#define _DEVICE_FWD_H_

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

namespace device_emulator {

// Forward declarations
class Device;
class DeviceBehaviour;
class IDeviceOrder;
class IOrderList;
class DeviceBehaviourState;

// typedefs
typedef boost::shared_ptr<DeviceBehaviour> DeviceBehaviourPtr;
typedef boost::shared_ptr<IDeviceOrder> IDeviceOrderPtr;
typedef IOrderList* IOrderListPtr;
typedef boost::shared_ptr<DeviceBehaviourState> DeviceBehaviourStatePtr;

}

#endif
