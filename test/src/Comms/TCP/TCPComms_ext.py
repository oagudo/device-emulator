#!/usr/bin/env python

import sys
sys.path.append('../../../../build/kernel')

import DeviceEmulatorKernel_ext as emulator_ext
import time

emulator_ext.Logger.init()

server_setup = emulator_ext.TCPServerSetup("3500")
server = emulator_ext.TCPServer(server_setup)

# Starting server ...
server.start()
time.sleep(1)

client_setup = emulator_ext.TCPClientSetup("localhost", "3500")
client = emulator_ext.TCPClient(client_setup)
client.start()

# Starting client ...
time.sleep(1)

msg = emulator_ext.Message(1, "name", "hello world!")
send_order = emulator_ext.SendOrder(msg)
wait_order = emulator_ext.WaitOrder(1000)

list_order_send = emulator_ext.OrderList()
list_order_send.add(send_order)
list_order_send.add(wait_order)

receive_order = emulator_ext.ReceiveOrder(1, 2000)
list_order_receive = emulator_ext.OrderList()
list_order_receive.add(receive_order)

behaviour_send = emulator_ext.DeviceBehaviour("Sender", client, list_order_send)
behaviour_receive = emulator_ext.DeviceBehaviour("Receiver", server, list_order_receive)

behaviour_receive.start()
behaviour_send.start()

behaviour_receive.wait()
behaviour_send.wait()

behaviour_receive.stop()
behaviour_send.stop()

client.stop()
server.stop() 

assert behaviour_send.state.to_string() == "Finished"
assert behaviour_receive.state.to_string() == "Finished"
