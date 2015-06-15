#ifndef _DEVICE_FWD_H_
#define _DEVICE_FWD_H_

#include <boost/shared_ptr.hpp>

namespace device_emulator {

// Forward declarations
class Device;
class DeviceBehaviour;

// typedefs
typedef boost::shared_ptr<Device> DevicePtr;
typedef boost::shared_ptr<DeviceBehaviour> DeviceBehaviourPtr;

}

#endif
