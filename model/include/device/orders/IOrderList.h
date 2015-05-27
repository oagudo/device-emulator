#ifndef _IORDER_LIST_H
#define _IORDER_LIST_H

#include <boost/scoped_ptr.hpp>

namespace device_emulator {

class IDeviceOrder;
typedef boost::shared_ptr<IDeviceOrder> IDeviceOrderPtr;

class IOrderList;
typedef boost::scoped_ptr<IOrderList> IOrderListScopedPtr;

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
