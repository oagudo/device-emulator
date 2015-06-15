#ifndef _DEVICE_H
#define _DEVICE_H

#include <string>
#include <vector>
#include "Common.h"

namespace device_emulator {

/*!
    \class This class is responsible for emulating a Device, which is composed of a set of behaviours
*/
class Device
{
public:
    
    /*! Default constructor */
    Device(const std::string &deviceName);

    /*!
        \brief Adds a behaviour to the device
    */
    void AddBehaviour(const DeviceBehaviourPtr &behaviour);

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
    std::string GetName() const;
    
private:
    std::string _deviceName;

    std::vector< DeviceBehaviourPtr > _behaviours;
};

} // namespace

#endif
