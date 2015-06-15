#ifndef _DATA_H_
#define _DATA_H_

#include <boost/shared_ptr.hpp>

namespace device_emulator {

// Forward declarations
class IMessage;
class Message;

// typedefs
typedef boost::shared_ptr<IMessage> IMessagePtr;
typedef boost::shared_ptr<Message> MessagePtr;

}

#endif
