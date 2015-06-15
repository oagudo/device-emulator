#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <boost/serialization/base_object.hpp>
#include "IMessage.h"

namespace device_emulator {

/*!
  \class Message implementation
*/
class Message : public IMessage {
public:

    Message(const unsigned int msgID, const std::string &msgName, const std::string &msgContent) : _msgId(msgID), _msgName(msgName), _msgContent(msgContent) { };
    Message() { };

    virtual ~Message() { };

    std::string ToString() const;
    std::vector<unsigned char> ToVector() const;
    unsigned int GetId() const;
    bool IsValid() const;

private:

    // Allowes boost serialization access
    friend class boost::serialization::access;

    /*!
      \brief Serialization template used by boost
    */
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) 
    { 
        ar & boost::serialization::base_object<IMessage>(*this);
        ar & _msgId;
        ar & _msgName;
        ar & _msgContent;
    }

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
