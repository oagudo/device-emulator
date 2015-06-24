#!/usr/bin/env python
import sys
import time
import DeviceEmulatorModel_ext as emulator_ext

emulator_ext.Logger.init()

number_connections = 40
base_port = 4000
servers = []
clients = []

for port_number in range(number_connections):
    server_setup = emulator_ext.TCPServerSetup(str(port_number + base_port))
    servers.append(emulator_ext.TCPServer(server_setup))
    client_setup = emulator_ext.TCPClientSetup("localhost", str(port_number + base_port))
    clients.append(emulator_ext.TCPClient(client_setup))

msg = emulator_ext.Message(1, "name", "hello world!")

list_order_send = emulator_ext.OrderList()
list_order_send.add(emulator_ext.SendOrder(msg))
list_order_send.add(emulator_ext.WaitOrder(100))

list_order_receive = emulator_ext.OrderList()
list_order_receive.add(emulator_ext.ReceiveOrder(1, 2000))

server_controller = emulator_ext.Device("server_controller")
client_controller = emulator_ext.Device("client_controller")
server_behaviours = []
client_behaviours = []

for server, idx in zip(servers, range(number_connections)):
    server.start()
    server_behaviour = emulator_ext.DeviceBehaviour("server" + str(idx), server, list_order_send)
    server_behaviours.append(server_behaviour)
    server_controller.add_behaviour(server_behaviour)

for client, idx in zip(clients, range(number_connections)):
    client.start()
    client_behaviour = emulator_ext.DeviceBehaviour("client" + str(idx), client, list_order_receive)
    client_behaviours.append(client_behaviour)
    client_controller.add_behaviour(client_behaviour)

server_controller.start()
client_controller.start()

server_controller.wait()
client_controller.wait()

for server, client in zip(servers, clients):
    server.stop()
    client.stop()

for client_behaviour, server_behaviour in zip(client_behaviours, server_behaviours):
    assert client_behaviour.state.to_string() == "Finished"
    assert server_behaviour.state.to_string() == "Finished"
