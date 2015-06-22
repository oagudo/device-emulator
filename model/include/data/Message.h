#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <boost/serialization/serialization.hpp>
#include <vector>

namespace device_emulator {

// TODO: Provide movement contructors

/*!
  \class Represents a Message
*/
class Message {

public:

    Message(const unsigned int msgID, const std::string &msgName, const std::string &msgContent);

    Message();

    virtual ~Message();

    std::string ToString() const;

    std::vector<unsigned char> ToVector() const;

    unsigned int GetId() const;

private:

    // Allowes boost serialization access
    friend class boost::serialization::access;

    /*!
      \brief Serialization template used by boost
    */
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) 
    { 
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
