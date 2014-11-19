#ifndef _DEVICE_H
#define _DEVICE_H

#include <string>
#include <vector>
#include "Device/Behaviour/IDeviceBehaviour.h"

namespace device_emulator {

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
      Name Getter 
    */
    std::string GetName() const { return _deviceName; }
    
private:
    std::string _deviceName;

    std::vector< IDeviceBehaviourPtr > _behaviours;
};

} // namespace

#endif
