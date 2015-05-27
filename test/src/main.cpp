#define BOOST_TEST_MODULE DeviceEmulator

#include <boost/test/auto_unit_test.hpp>
#include <boost/filesystem.hpp>

#include <log/Logger.h>

struct InitTests {
    InitTests() {
        device_emulator::Logger::Init();
        if ( boost::filesystem::exists("log4cxx.xml") ) {
            // Configures log4cxx
            device_emulator::Logger::Configure("log4cxx.xml");
        }
    }
    ~InitTests() { }
};

BOOST_GLOBAL_FIXTURE(InitTests)
