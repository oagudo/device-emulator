#ifndef _IDEVICE_ORDER_H
#define _IDEVICE_ORDER_H

#include <iostream>
#include <boost/format.hpp>

#include "Comms/CommunicationChannel.h"

namespace device_emulator {

class IDeviceOrder;
typedef boost::shared_ptr<IDeviceOrder> IDeviceOrderPtr;

class IDeviceBehaviour;
typedef boost::shared_ptr<IDeviceBehaviour> IDeviceBehaviourPtr;

class CommunicationChannel;
typedef boost::shared_ptr<CommunicationChannel> ComChannelPtr;

/*!
    \class Represents a device order
*/
class IDeviceOrder
{
public:
    virtual void Execute(const IDeviceBehaviourPtr &context) = 0;
};

} // namespace

#endif
