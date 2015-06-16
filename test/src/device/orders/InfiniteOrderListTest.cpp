#include <boost/test/auto_unit_test.hpp>

#include <data/Message.h>
#include <device/orders/OrderList.h>
#include <device/orders/InfiniteOrderList.h>
#include <device/orders/SendOrder.h>

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( InfiniteOrderListTests )

struct Fixture {
    Message msg1;
    Message msg2;
    InfiniteOrderList infSendOrders;
    IDeviceOrderPtr orderSend1;
    IDeviceOrderPtr orderSend2;
    Fixture() :
        msg1(1, "msg1", "content1"),
        msg2(2, "msg2", "content2"),
        orderSend1(new SendOrder(msg1)),
        orderSend2(new SendOrder(msg2))
    {
        infSendOrders.Add(orderSend1);
        infSendOrders.Add(orderSend2);
    };
};

BOOST_AUTO_TEST_CASE( InfiniteOrderList_DoNotDecreaseWhenCallingNext ) {
    Fixture f;
    unsigned int numberOrders = f.infSendOrders.Count();
    f.infSendOrders.Next();
    BOOST_CHECK_EQUAL(f.infSendOrders.Count(), numberOrders);
}

BOOST_AUTO_TEST_CASE( InfiniteOrderList_SetOrderAtTheEndWhenCallingNext ) {
    Fixture f;
    IDeviceOrderPtr order1 = f.infSendOrders.Next();
    BOOST_CHECK(order1 != f.infSendOrders.Next());
}

BOOST_AUTO_TEST_SUITE_END()
