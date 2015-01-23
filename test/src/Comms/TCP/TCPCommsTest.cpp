#include <boost/test/auto_unit_test.hpp>

#include <Comms/TCP/TCPClient.h>
#include <Comms/TCP/TCPServer.h>
#include <Device/Behaviour/DeviceBehaviour.h>
#include <Device/Behaviour/States/DeviceBehaviourState.h>
#include <Device/Behaviour/States/ErrorState.h>
#include <Data/Message.h>
#include <Device/Orders/OrderList.h>
#include <Device/Orders/IDeviceOrder.h>
#include <Device/Orders/ReceiveOrder.h>
#include <Device/Orders/SendOrder.h>
#include <Device/Orders/WaitOrder.h>

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( TCPCommsTests )

struct Fixture {
    IMessagePtr msg1;
    TCPClientSetup clientSetup;
    TCPClientPtr clientChannel;
    TCPServerSetup serverSetup;
    TCPServerPtr serverChannel;
    OrderList ordersClient;
    OrderList ordersServer;
    DeviceBehaviourPtr behaviourClient;
    DeviceBehaviourPtr behaviourServer;
    IDeviceOrderPtr orderReceive;
    IDeviceOrderPtr orderSend;
    IDeviceOrderPtr orderWait;
    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        clientSetup("localhost", "2222"),
        clientChannel(new TCPClient(clientSetup)),
        serverSetup("2222"),
        serverChannel(new TCPServer(serverSetup)),
        orderReceive(new ReceiveOrder(1, 250)),
        orderSend(new SendOrder(msg1)),
        orderWait(new WaitOrder(50))
    { 
        ordersClient.Add(orderReceive);
        ordersServer.Add(orderWait);
        ordersServer.Add(orderSend);

        behaviourClient.reset(new DeviceBehaviour("Test Behaviour", clientChannel, ordersClient));
        behaviourServer.reset(new DeviceBehaviour("Test Behaviour2", serverChannel, ordersServer));
    };

    ~Fixture()
    {
        clientChannel->Stop();
        serverChannel->Stop();
    }
    
};

BOOST_AUTO_TEST_CASE( TCPCommsTests_ServerStartsListenningCorrectly ) {
    Fixture f;
    BOOST_CHECK (f.serverChannel->Start());
}

BOOST_AUTO_TEST_CASE( TCPCommsTests_ClientConnectsToServerCorrectly ) {
    Fixture f;
    f.serverChannel->Start();
    BOOST_CHECK(f.clientChannel->Start());
}

BOOST_AUTO_TEST_CASE( TCPCommsTests_MessagesAreSentAndReceivedCorrectly ) {
    Fixture f;
    f.serverChannel->Start();
    f.clientChannel->Start();
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) ); // Waits for connection
    f.clientChannel->Send(f.msg1);
    boost::this_thread::sleep( boost::posix_time::milliseconds(50) ); // Waits for message to be received
    BOOST_CHECK(f.serverChannel->WantMessage(f.msg1->GetId(), f.behaviourServer));
}

BOOST_AUTO_TEST_CASE( TCPCommsTests_DeviceBehavioursSendAndReceiveMessagesThroughtTCPChannel ) {
    Fixture f;
    f.serverChannel->Start();
    f.clientChannel->Start();

    f.behaviourServer->Start();
    f.behaviourClient->Start();

    f.behaviourServer->Wait();
    f.behaviourClient->Wait();
    
    BOOST_CHECK(f.behaviourServer->GetState() != ErrorState::Instance());
    BOOST_CHECK(f.behaviourClient->GetState() != ErrorState::Instance());
}

BOOST_AUTO_TEST_SUITE_END()
