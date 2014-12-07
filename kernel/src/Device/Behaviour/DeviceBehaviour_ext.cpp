#include "Device/Behaviour/DeviceBehaviour.h"
#include "Device/Behaviour/States/DeviceBehaviourState.h"
#include "Device/Orders/OrderList.h"
#include "Comms/CommunicationChannel.h"
#include <boost/python.hpp>

using namespace boost::python;
using namespace device_emulator;

struct DeviceBehaviourStateWrap : DeviceBehaviourState, wrapper<DeviceBehaviourState>
{
    bool IsErrorState() {
        return this->get_override("is_error_state")();
    }
    bool AllowToContinue() {
        return this->get_override("allow_to_continue")();
    }
    std::string GetErrorMsg() {
        if (override n = this->get_override("get_error_msg"))
            return n();
        return DeviceBehaviourState::GetErrorMsg();
    }
    std::string default_GetErrorMsg() { return this->DeviceBehaviourState::GetErrorMsg(); }

    void Start(const DeviceBehaviourPtr &context) {
        if (override n = this->get_override("start"))
            n(context);
        DeviceBehaviourState::Start(context);
    }
    void default_Start(const DeviceBehaviourPtr &context) { this->DeviceBehaviourState::Start(context); }

    void ExecuteOrders(const DeviceBehaviourPtr &context) {
        if (override n = this->get_override("execute_orders"))
            n(context);
        DeviceBehaviourState::ExecuteOrders(context);
    }
    void default_ExecuteOrders(const DeviceBehaviourPtr &context) { this->DeviceBehaviourState::ExecuteOrders(context); }

    void Stop(const DeviceBehaviourPtr &context) {
        if (override n = this->get_override("stop"))
            n(context);
        DeviceBehaviourState::Stop(context);
    }
    void default_Stop(const DeviceBehaviourPtr &context) { this->DeviceBehaviourState::Stop(context); }
};


void export_DeviceBehaviour()
{
    class_<DeviceBehaviour, DeviceBehaviourPtr, boost::noncopyable>("DeviceBehaviour", init<const std::string, const ComChannelPtr, const OrderListPtr>())
        .add_property("state", &DeviceBehaviour::GetState)
        .add_property("name", &DeviceBehaviour::GetName)
        .add_property("orders", &DeviceBehaviour::GetOrders)
        .add_property("channel", &DeviceBehaviour::GetCommChannel)
        .def("start", &DeviceBehaviour::Start)
        .def("stop", &DeviceBehaviour::Stop)
        .def("wait", &DeviceBehaviour::Wait)
        ;

    class_<DeviceBehaviourStateWrap, boost::noncopyable>("DeviceBehaviourState")
        .def("is_error_state", pure_virtual(&DeviceBehaviourState::IsErrorState))
        .def("allow_to_continue", pure_virtual(&DeviceBehaviourState::AllowToContinue))
        .def("get_error_msg", &DeviceBehaviourStateWrap::GetErrorMsg, &DeviceBehaviourStateWrap::default_GetErrorMsg)
        .def("start", &DeviceBehaviourStateWrap::Start, &DeviceBehaviourStateWrap::default_Start)
        .def("execute_orders", &DeviceBehaviourStateWrap::ExecuteOrders, &DeviceBehaviourStateWrap::default_ExecuteOrders)
        .def("stop", &DeviceBehaviourStateWrap::Stop, &DeviceBehaviourStateWrap::default_Stop)
        ;
}
