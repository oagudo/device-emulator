#ifndef _ORDER_LIST_H
#define _ORDER_LIST_H

#include <queue>
#include <boost/shared_ptr.hpp>

namespace device_emulator {

class OrderList;
typedef boost::shared_ptr<OrderList> OrderListPtr;

class IDeviceOrder;
typedef boost::shared_ptr<IDeviceOrder> IDeviceOrderPtr;

/*!
    \class Represents a list of orders
*/
class OrderList
{
public:

    OrderList() { }

    virtual ~OrderList() { }

    /*!
        \brief Adds a new device order at the end of the collection
    */
    void Add(const IDeviceOrderPtr &order);

    /*!
        \brief Returns the next order and removes it from the list
    */    
    virtual IDeviceOrderPtr Next();

    /*!
        \brief Returns True is list is empty, False otherwise
    */    
    bool Empty() const;

    /*!
        \brief Returns the number of order of the list
    */    
    unsigned int Count() const;
    
protected:
    std::queue<IDeviceOrderPtr> _queue;
};

} // namespace

#endif
