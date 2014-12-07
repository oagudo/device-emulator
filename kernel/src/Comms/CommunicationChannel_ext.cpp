#include "Comms/CommunicationChannel.h"
#include "Comms/TCP/TCPServerSetup.h"
#include "Comms/TCP/TCPClientSetup.h"
#include "Comms/TCP/TCPServer.h"
#include "Comms/TCP/TCPClient.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

struct CommunicationChannelWrap : CommunicationChannel, wrapper<CommunicationChannel>
{
    CommunicationChannelWrap(const ComChannelSetupPtr &setup) : CommunicationChannel(setup) { };

    bool Start() {
        return this->get_override("start")();
    }
    void Stop() {
        this->get_override("stop")();
    }
    void Send(const IMessagePtr &msg) {
        this->get_override("send")(msg);
    }
    void OnMsgReceived(const IMessagePtr &msg) {
        if (override n = this->get_override("on_msg_received"))
			n();
		CommunicationChannel::OnMsgReceived(msg);
    }
    void default_OnMsgReceived(const IMessagePtr &msg) { this->CommunicationChannel::OnMsgReceived(msg); }
};

struct TCPEndPointWrap : TCPEndPoint, wrapper<TCPEndPoint>
{
    TCPEndPointWrap(const ComChannelSetupPtr &setup) : TCPEndPoint(setup) { };

    bool Start() {
        return this->get_override("start")();
    }
    void Stop() {
        if (override n = this->get_override("stop"))
			n();
		TCPEndPoint::Stop();
    }
    void default_Stop() { this->TCPEndPoint::Stop(); }

    void Send(const IMessagePtr &msg) {
        if (override n = this->get_override("send"))
			n();
		TCPEndPoint::Send(msg);
    }
    void default_Send(const IMessagePtr &msg) { this->TCPEndPoint::Send(msg); }
};


void export_CommunicationChannel()
{
    class_<CommunicationChannelSetup, ComChannelSetupPtr>("CommunicationChannelSetup")
        ;
    
    class_<boost::shared_ptr<CommunicationChannel> >("CommunicationChannel")
        ;

    class_<CommunicationChannelWrap, boost::noncopyable>("CommunicationChannel", init<const ComChannelSetupPtr>())
		.def("start", pure_virtual(&CommunicationChannel::Start))
		.def("stop", pure_virtual(&CommunicationChannel::Stop))
		.def("send", pure_virtual(&CommunicationChannel::Send))
		.def("on_msg_received", &CommunicationChannelWrap::OnMsgReceived, &CommunicationChannelWrap::default_OnMsgReceived)
		.def("want_message", &CommunicationChannel::WantMessage)
		;	 

  	class_<TCPEndPointWrap, boost::noncopyable>("TCPEndPoint", init<const ComChannelSetupPtr>())
		.def("start", pure_virtual(&TCPEndPoint::Start))
		.def("stop", &TCPEndPointWrap::Stop, &TCPEndPointWrap::default_Stop)
		.def("send", &TCPEndPointWrap::Send, &TCPEndPointWrap::default_Send)
		;

    class_<TCPClientSetup, TCPClientSetupPtr, bases<CommunicationChannelSetup> >("TCPClientSetup", init<const std::string, const std::string>())
        .add_property("port", &TCPClientSetup::GetPort)
        .add_property("host", &TCPClientSetup::GetHost)
        ; 
    
    class_<TCPClient, boost::noncopyable, bases<TCPEndPoint> >("TCPClient", init<const TCPClientSetupPtr>())
		.def("start", &TCPClient::Start)
		.def("stop", &TCPClient::Stop)
		.def("send", &TCPClient::Send)
        ;   

    class_<TCPServerSetup, TCPServerSetupPtr, bases<CommunicationChannelSetup> >("TCPServerSetup", init<const std::string>())
        .add_property("port", &TCPServerSetup::GetPort)
        ;

    class_<TCPServer, boost::noncopyable, bases<TCPEndPoint> >("TCPServer", init<const TCPServerSetupPtr>())
		.def("start", &TCPServer::Start)
		.def("stop", &TCPServer::Stop)
		.def("send", &TCPServer::Send)
        ;   


}

