#ifndef _COMMS_FWD_H_
#define _COMMS_FWD_H_

#include <boost/shared_ptr.hpp>
#include <functional>

namespace device_emulator {

// Forward declarations
class CommunicationChannel;
class TCPClient;
class TCPServer;
class IMessage;

// typedefs
typedef boost::shared_ptr<CommunicationChannel> ComChannelPtr;
typedef boost::shared_ptr<IMessage> IMessagePtr;
typedef std::function<void(const IMessagePtr &)> ComChannelReceiveCallback;
typedef boost::shared_ptr<TCPClient> TCPClientPtr;
typedef boost::shared_ptr<TCPServer> TCPServerPtr;

}

#endif
