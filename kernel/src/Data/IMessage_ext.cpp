#include "Data/IMessage.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;


struct IMessageWrap : IMessage, wrapper<IMessage>
{
    std::string ToString() const {
        return this->get_override("ToString")();
    }

    std::vector<unsigned char> ToVector() const {
        std::vector<unsigned char> v; // TODO: Change dummy return
        return v;
    }

    unsigned int GetId() const {
        return 0; // TODO: Change dummy return
    }

    bool IsValid() const {
        return true; // TODO: Change dummy return
    }

};

void export_IMessage()
{
    class_<IMessageWrap, boost::noncopyable>("IMessage")
        .def("to_string", pure_virtual(&IMessage::ToString))
        ;
}

