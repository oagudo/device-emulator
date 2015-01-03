#ifndef _COMMUNICATION_CHANNEL_SETUP_H
#define _COMMUNICATION_CHANNEL_SETUP_H

namespace device_emulator {

class CommunicationChannelSetup;
typedef boost::shared_ptr<CommunicationChannelSetup> ComChannelSetupPtr;

/*! 
    This class represents a setup for a communication channel
    TODO: Provide abstractions for each type of communication channel
*/
class CommunicationChannelSetup {
 public:
    CommunicationChannelSetup() { };
    virtual ~CommunicationChannelSetup() { };
};

} // namespace

#endif
