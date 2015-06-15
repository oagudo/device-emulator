#ifndef _IORDER_LIST_H
#define _IORDER_LIST_H

#include "Common.h"

namespace device_emulator {

/*!
    \class IOrderList
    \brief Interface for list of orders. Avoid Object slicing if creating and passing derived objects directly
*/
class IOrderList {
public:
    virtual ~IOrderList() { };
    virtual void Add(const IDeviceOrderPtr &order) = 0;
    virtual IDeviceOrderPtr Next() = 0;
    virtual bool Empty() const = 0;
    virtual unsigned int Count() const = 0;
    virtual IOrderList* Clone() const = 0;  // Virtual constructor
};

} // namespace

#endif
