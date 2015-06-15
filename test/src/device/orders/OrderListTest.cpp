#include <boost/test/auto_unit_test.hpp>

#include <data/Message.h>
#include <device/orders/OrderList.h>
#include <device/orders/InfiniteOrderList.h>
#include <device/orders/ReceiveOrder.h>

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( OrderListTests )

struct Fixture {
    IMessagePtr msg1;
    IMessagePtr msg2;
    OrderList orders;
    IDeviceOrderPtr orderReceive1;
    IDeviceOrderPtr orderReceive2;
    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        msg2(new Message(2, "msg2", "content2")),
        orderReceive1(new ReceiveOrder(1, 1000)),
        orderReceive2(new ReceiveOrder(2, 1000))
    {
        orders.Add(orderReceive1);
        orders.Add(orderReceive2);
    };
};

BOOST_AUTO_TEST_CASE( OrderList_GrowsWhenNeeded ) {
    Fixture f;
    unsigned int numberOrders = f.orders.Count();
    f.orders.Add(IDeviceOrderPtr (new ReceiveOrder (1, 1000)));
    BOOST_CHECK_EQUAL(f.orders.Count(), numberOrders + 1);
}

BOOST_AUTO_TEST_CASE( OrderList_NextRemovesElementFromList ) {
    Fixture f;
    unsigned int numberOrders = f.orders.Count();
    f.orders.Next();
    BOOST_CHECK_EQUAL(f.orders.Count(), numberOrders - 1);
}

BOOST_AUTO_TEST_CASE( OrderList_EmptyReturnsTrueIfThereAreNoOrders ) {
    Fixture f;
    while (f.orders.Count() > 0) {
        f.orders.Next();
    }
    BOOST_CHECK_EQUAL(f.orders.Empty(), true);
}

BOOST_AUTO_TEST_SUITE_END()