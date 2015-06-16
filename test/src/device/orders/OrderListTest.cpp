#include <boost/test/auto_unit_test.hpp>
#include <boost/make_shared.hpp>
#include <data/Message.h>
#include <device/orders/OrderList.h>
#include <device/orders/InfiniteOrderList.h>
#include <device/orders/ReceiveOrder.h>

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( OrderListTests )

struct Fixture {
    Message msg1;
    Message msg2;
    OrderList orders;
    IDeviceOrderPtr orderReceive1;
    IDeviceOrderPtr orderReceive2;
    Fixture() :
        msg1(1, "msg1", "content1"),
        msg2(2, "msg2", "content2"),
        orderReceive1(boost::make_shared<ReceiveOrder>(1, 1000)),
        orderReceive2(boost::make_shared<ReceiveOrder>(2, 1000))
    {
        orders.Add(orderReceive1);
        orders.Add(orderReceive2);
    };
};

BOOST_AUTO_TEST_CASE( OrderList_GrowsWhenNeeded ) {
    Fixture f;
    unsigned int numberOrders = f.orders.Count();
    f.orders.Add(boost::make_shared<ReceiveOrder>(1, 1000));
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
