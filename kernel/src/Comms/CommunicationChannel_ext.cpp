#include "Comms/CommunicationChannel.h"
#include "Comms/TCP/TCPServerSetup.h"
#include "Comms/TCP/TCPClientSetup.h"
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

    class_<TCPServerSetup, TCPServerSetupPtr, bases<CommunicationChannelSetup> >("TCPServerSetup", init<const std::string>())
        .add_property("port", &TCPServerSetup::GetPort)
        ;

    class_<TCPClientSetup, TCPClientSetupPtr, bases<CommunicationChannelSetup> >("TCPClientSetup", init<const std::string, const std::string>())
        .add_property("port", &TCPClientSetup::GetPort)
        .add_property("host", &TCPClientSetup::GetHost)
        ;
    
}

