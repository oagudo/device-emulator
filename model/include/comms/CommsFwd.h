#ifndef _COMMS_FWD_H_
#define _COMMS_FWD_H_

#include <boost/shared_ptr.hpp>

namespace device_emulator {

// Forward declarations
class CommunicationChannel;
class TCPClient;
class TCPServer;

// typedefs
typedef boost::shared_ptr<CommunicationChannel> ComChannelPtr;
typedef boost::shared_ptr<TCPClient> TCPClientPtr;
typedef boost::shared_ptr<TCPServer> TCPServerPtr;

}

#endif
