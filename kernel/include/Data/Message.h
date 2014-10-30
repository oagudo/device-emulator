#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "IMessage.h"

namespace device_emulator {

/*!
    \class Message implementation
*/
class Message : public IMessage {
public:

    Message(unsigned int msgID, std::string msgName, std::string msgContent) : _msgId(msgID), _msgName(msgName), _msgContent(msgContent) { };

    virtual ~Message() { };

	  std::string ToString() const;
	  std::vector<unsigned char> ToVector() const;
    unsigned int GetId() const;
    bool IsValid() const;

private:
    /*!
        \brief Unique identifier of the message
    */
    unsigned int _msgId;

	  /*! 
	    \brief Contains the name of the message
	  */
	  std::string _msgName;

	  /*! 
	    \brief Contains the message information
	  */
	  std::string _msgContent;
};

} // namespace

#endif
