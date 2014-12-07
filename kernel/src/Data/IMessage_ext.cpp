#include "Data/IMessage.h"
#include "Data/Message.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;


struct IMessageWrap : IMessage, wrapper<IMessage>
{
    std::string ToString() const {
        return this->get_override("to_string")();
    }

    std::vector<unsigned char> ToVector() const {
        return this->get_override("to_vector")();
    }

    unsigned int GetId() const {
        return this->get_override("get_id")();
    }

    bool IsValid() const {
        return this->get_override("is_valid")();
    }

};

void export_IMessage()
{
    class_<IMessageWrap, boost::noncopyable>("IMessage")
        .def("to_string", pure_virtual(&IMessage::ToString))
        .def("to_vector", pure_virtual(&IMessage::ToVector))
        .def("get_id", pure_virtual(&IMessage::GetId))
        .def("is_valid", pure_virtual(&IMessage::IsValid))
        ;

    class_<Message, MessagePtr, bases<IMessage> >("Message")
        .def(init<const unsigned int, const std::string, const std::string>())
        .def("to_string", &Message::ToString)
        .def("to_vector", &Message::ToVector)
        .def("get_id", &Message::GetId)
        .def("is_valid", &Message::IsValid)
        ;

}

