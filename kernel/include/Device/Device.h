#ifndef _DEVICE_H
#define _DEVICE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Device/Behaviour/IDeviceBehaviour.h"

namespace device_emulator {

class Device;
typedef boost::shared_ptr< Device > DevicePtr;

/*!
    \class This class is responsible for emulating a Device, which is composed of a set of behaviours
*/
class Device
{
public:
    
    /*! Default constructor */
    Device(const std::string &deviceName) : _deviceName(deviceName) { }

    /*!
        \brief Adds a behaviour to the device
    */
    void AddBehaviour(const IDeviceBehaviourPtr &behaviour);

    /*!
      \brief Starts all its behaviours
     */
    void Start();

    /*!
      \brief Stops all its behaviours
     */
    void Stop();

    /*!
      Name Getter 
    */
    std::string GetName() const { return _deviceName; }
    
private:
    std::string _deviceName;

    std::vector< IDeviceBehaviourPtr > _behaviours;
};

} // namespace

#endif
