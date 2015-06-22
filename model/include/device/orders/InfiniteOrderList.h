#ifndef _INF_ORDER_LIST_H
#define _INF_ORDER_LIST_H

#include "device/orders/OrderList.h"

namespace device_emulator {

/*!
    \class Represents an infinite list of orders. 
           When Next element is retrieved it is enqueue in the list again
*/
class InfiniteOrderList : public OrderList
{
public:
    IDeviceOrderPtr Next();

    /*!
        \brief Implements virtual constructor
    */
    IOrderListPtr Clone() const;  // Virtual constructor
};

} // namespace

#endif
