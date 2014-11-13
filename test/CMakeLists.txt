# Boost Libraries
# For custom BOOST libraries
#set(Boost_INCLUDE_DIR $ENV{BOOST_HOME})
#set(Boost_LIBRARY_DIR $ENV{BOOST_HOME}/stage/x64)

set( Boost_USE_STATIC_LIBS ON ) # or Off, depending on what you want

find_package(Boost 1.49 COMPONENTS system filesystem unit_test_framework thread serialization REQUIRED)

set(log4cxx_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(log4cxx)

if (LOG4CXX_FOUND)
	ADD_DEFINITIONS(-DWITH_LOG4CXX)
endif()

# Unit testing definition for inserting main function automatically
# ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

add_definitions( -DBOOST_ALL_NO_LIB )

FILE(GLOB_RECURSE TEST_SOURCES "src/*.cpp")
FILE(GLOB_RECURSE TEST_INCLUDES "src/*.h")

source_group("src" FILES ${TEST_SOURCES})
source_group("include" FILES ${TEST_INCLUDES})

include_directories ("${PROJECT_SOURCE_DIR}/kernel/include") 
include_directories (./src/) 

link_directories(${Boost_LIBRARY_DIR})

# Creates executable
add_executable(UnitTests ${TEST_SOURCES})

# Additional Dependencies
target_link_libraries(UnitTests
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      DeviceEmulatorKernel
                      )

# Creates a folder "executables" and adds target project under it
set_property(TARGET UnitTests PROPERTY FOLDER "executables")

# Adds logic to copy app to destination directory
install (TARGETS UnitTests RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

