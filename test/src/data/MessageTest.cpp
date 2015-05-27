#include <boost/test/included/unit_test.hpp>

#include <data/Message.h>

using namespace device_emulator;

BOOST_AUTO_TEST_SUITE( MessageTests )

BOOST_AUTO_TEST_CASE( Message_CanBeConvertedToVector ) {
    std::string contentTest("content of the message");
    Message msg(1, "Message Test", contentTest);
    std::vector<unsigned char> vector = msg.ToVector();

    // Same length
    BOOST_CHECK_EQUAL(vector.size(), contentTest.length());

    // Same content
    for(unsigned int i = 0; i < vector.size(); i++) {
        BOOST_CHECK_EQUAL(vector[i], (unsigned char)contentTest[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()
