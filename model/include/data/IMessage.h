#ifndef _IMESSAGE_H
#define _IMESSAGE_H

#include <vector>
#include <string>
#include <boost/serialization/serialization.hpp>
#include "Common.h"

namespace device_emulator {

/*!
  \class Interface for messages
*/
class IMessage {

public:

    virtual ~IMessage() {};
    /*!
      \brief Returns the string representation of the message
    */
    virtual std::string ToString() const = 0;

    /*!
      \brief Returns the vector representation of the message
    */
    virtual std::vector<unsigned char> ToVector() const = 0;

    /*!
      \brief Returns unique identifier of a message
    */
    virtual unsigned int GetId() const = 0;

    /*!
      \brief True if content is valid, False otherwise
    */
    virtual bool IsValid() const = 0;

    /*!
      \brief Serialization template used by boost
    */
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) { }

private:

    // Allowes boost serialization access
    friend class boost::serialization::access;
};

} // namespace

#endif
