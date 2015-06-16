#include "data/Message.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

void export_IMessage()
{
    class_<Message>("Message")
        .def(init<const unsigned int, const std::string, const std::string>())
        .def("to_string", &Message::ToString)
        .def("to_vector", &Message::ToVector)
        .def("get_id", &Message::GetId)
        ;
}
