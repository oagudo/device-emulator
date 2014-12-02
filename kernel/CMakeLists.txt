# Boost Libraries
# For custom BOOST libraries
#set(Boost_INCLUDE_DIR $ENV{BOOST_HOME})
#set(Boost_LIBRARY_DIR $ENV{BOOST_HOME}/stage/x64)

# set( Boost_USE_STATIC_LIBS OFF )

find_package(Boost 1.49 COMPONENTS system thread date_time serialization python REQUIRED)

find_package(PythonLibs 2.7 REQUIRED)

set(log4cxx_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(log4cxx)

FILE(GLOB_RECURSE KERNEL_SOURCES "src/*.cpp")
FILE(GLOB_RECURSE KERNEL_SOURCES_EXT "src/*_ext.cpp")
LIST(REMOVE_ITEM KERNEL_SOURCES ${KERNEL_SOURCES_EXT})

FILE(GLOB_RECURSE KERNEL_INCLUDES "include/*.h")

# Create named folders 
source_group("src" FILES ${KERNEL_SOURCES})
source_group("include" FILES ${KERNEL_INCLUDES})

# Include Directories
include_directories (./include) 
include_directories (${Boost_INCLUDE_DIR})
include_directories (${PYTHON_INCLUDE_DIRS})

if (LOG4CXX_FOUND)
	ADD_DEFINITIONS(-DWITH_LOG4CXX)
	include_directories(${LOG4CXX_INCLUDE_DIR})
	message("Logging enabled")
else()
	set(LOG4CXX_LIBRARIES "")
	message("Logging not enabled (install log4cxx)")
endif()

link_directories(${Boost_LIBRARY_DIR})

add_library (DeviceEmulatorKernel SHARED ${KERNEL_SOURCES})
target_link_libraries( DeviceEmulatorKernel ${Boost_LIBRARIES} ${LOG4CXX_LIBRARIES} )

# Creates a folder "libraries" and adds target project under it
set_property(TARGET DeviceEmulatorKernel PROPERTY FOLDER "libraries")

# Define the wrapper library 
add_library( DeviceEmulatorKernel_ext SHARED ${KERNEL_SOURCES_EXT} )
target_link_libraries( DeviceEmulatorKernel_ext ${Boost_LIBRARIES} DeviceEmulatorKernel )

# Don't prepend wrapper library name with lib
set_target_properties( DeviceEmulatorKernel_ext PROPERTIES PREFIX "" )
set_property(TARGET DeviceEmulatorKernel_ext PROPERTY FOLDER "libraries")
