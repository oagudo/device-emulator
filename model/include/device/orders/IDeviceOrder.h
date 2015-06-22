#ifndef _IDEVICE_ORDER_H
#define _IDEVICE_ORDER_H

#include "Common.h"

namespace device_emulator {

/*!
    \class Represents a device order
*/
class IDeviceOrder
{
public:
    /*!
        \brief Executes the order in the context of a device behaviour
        \return True if execution was ok, False otherwise
     */
    virtual bool Execute(const DeviceBehaviourPtr &context) = 0;

    /*!
        \brief Clones the order
     */
    virtual IDeviceOrderPtr Clone() const = 0;
};

} // namespace

#endif
