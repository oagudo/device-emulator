#include <boost/test/auto_unit_test.hpp>

#include <Comms/TCP/TCPClient.h>
#include <Comms/TCP/TCPServer.h>

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( TCPCommsTests )

struct Fixture {
    IMessagePtr msg1;

    TCPClientSetupPtr clientSetup;
    TCPClientPtr client;

    TCPServerSetupPtr serverSetup;
    TCPServerPtr server;

    Fixture() :
        msg1(new Message(1, "msg1", "content1")),
        clientSetup(new TCPClientSetup("localhost", "2222")),
        client(new TCPClient(clientSetup)),
        serverSetup(new TCPServerSetup("2222")),
        server(new TCPServer(serverSetup)) { };
};

BOOST_AUTO_TEST_CASE( TCPCommsTests_ServerStartsListenningCorrectly ) {

    Fixture f;
    BOOST_CHECK (f.server->Start());
    f.server->Stop();
}

BOOST_AUTO_TEST_CASE( TCPCommsTests_ClientConnectsToServerCorrectly ) {

    Fixture f;
    f.server->Start();
    BOOST_CHECK(f.client->Start());
    f.server->Stop();
    f.client->Stop();
}

BOOST_AUTO_TEST_SUITE_END()
