#!/usr/bin/env python

import sys

from DeviceEmulatorModel_ext import OrderList, InfiniteOrderList, WaitOrder, SendOrder, ReceiveOrder, Message

# Orders
wait_order = WaitOrder(500)
send_order = SendOrder(Message(1, "msg name", "msg content"))
receive_order = ReceiveOrder(1, 500)

# OrderList
order_list = OrderList()
assert order_list.count() == 0
assert order_list.empty() == True
order_list.add(wait_order)
assert order_list.count() == 1
order_list.next()
assert order_list.count() == 0

# Infinite OrderList
infinite_list = InfiniteOrderList()
assert infinite_list.count() == 0
assert infinite_list.empty() == True
infinite_list.add(send_order)
infinite_list.add(receive_order)
assert infinite_list.count() == 2
infinite_list.next()
assert infinite_list.count() == 2
