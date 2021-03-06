#include "comms/CommunicationChannel.h"
#include "comms/tcp/TCPServerSetup.h"
#include "comms/tcp/TCPClientSetup.h"
#include "comms/tcp/TCPServer.h"
#include "comms/tcp/TCPClient.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

struct CommunicationChannelWrap : CommunicationChannel, wrapper<CommunicationChannel>
{
    CommunicationChannelWrap() { };

    bool Start() {
        return this->get_override("start")();
    }
    void Stop() {
        this->get_override("stop")();
    }
    bool Send(const Message &msg) {
        return this->get_override("send")(msg);
    }
    void OnMsgReceived(const Message &msg) {
        if (override n = this->get_override("on_msg_received"))
            n(msg);
        CommunicationChannel::OnMsgReceived(msg);
    }
    void default_OnMsgReceived(const Message &msg) { this->CommunicationChannel::OnMsgReceived(msg); }
};

struct TCPEndPointWrap : TCPEndPoint, wrapper<TCPEndPoint>
{
    TCPEndPointWrap() { };

    bool Start() {
        return this->get_override("start")();
    }
    void Stop() {
        if (override n = this->get_override("stop"))
            n();
        TCPEndPoint::Stop();
    }
    void default_Stop() { this->TCPEndPoint::Stop(); }

    bool Send(const Message &msg) {
        if (override n = this->get_override("send"))
            n(msg);
        return TCPEndPoint::Send(msg);
    }
    bool default_Send(const Message &msg) { return this->TCPEndPoint::Send(msg); }
};


void export_CommunicationChannel()
{

    class_<CommunicationChannel, boost::shared_ptr<CommunicationChannel>, boost::noncopyable >("CommunicationChannel", no_init)
        ;

    class_<TCPEndPoint, boost::shared_ptr<TCPEndPoint>, boost::noncopyable >("TCPEndPoint", no_init);
    

    class_<TCPEndPointWrap, boost::noncopyable>("TCPEndPoint", init<>())
        .def("start", pure_virtual(&TCPEndPoint::Start))
        .def("stop", &TCPEndPointWrap::Stop, &TCPEndPointWrap::default_Stop)
        .def("send", &TCPEndPointWrap::Send, &TCPEndPointWrap::default_Send)
        ;

    class_<TCPClientSetup>("TCPClientSetup", init<const std::string, const std::string>())
        .add_property("port", &TCPClientSetup::GetPort)
        .add_property("host", &TCPClientSetup::GetHost)
        ;

    class_<TCPClient, TCPClientPtr, boost::noncopyable, bases<TCPEndPoint> >("TCPClient", init<const TCPClientSetup>())
        .def("start", &TCPClient::Start)
        .def("stop", &TCPClient::Stop)
        .def("send", &TCPClient::Send)
        ;

    class_<TCPServerSetup>("TCPServerSetup", init<const std::string>())
        .add_property("port", &TCPServerSetup::GetPort)
        ;

    class_<TCPServer, TCPServerPtr, boost::noncopyable, bases<TCPEndPoint> >("TCPServer", init<const TCPServerSetup>())
        .def("start", &TCPServer::Start)
        .def("stop", &TCPServer::Stop)
        .def("send", &TCPServer::Send)
        ;

    implicitly_convertible<TCPClientPtr, boost::shared_ptr<CommunicationChannel> >();
    implicitly_convertible<TCPServerPtr, boost::shared_ptr<CommunicationChannel> >();

}
