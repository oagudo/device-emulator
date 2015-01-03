# Boost Libraries
# For custom BOOST libraries
#set(Boost_INCLUDE_DIR $ENV{BOOST_HOME})
#set(Boost_LIBRARY_DIR $ENV{BOOST_HOME}/stage/x64)

# set( Boost_USE_STATIC_LIBS OFF )

find_package(Boost 1.49 COMPONENTS system thread date_time serialization python REQUIRED)

find_package(PythonLibs 2.7 REQUIRED)

set(log4cxx_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(log4cxx)

FILE(GLOB_RECURSE MODEL_SOURCES "src/*.cpp")
FILE(GLOB_RECURSE MODEL_SOURCES_EXT "src/*_ext.cpp")
LIST(REMOVE_ITEM MODEL_SOURCES ${MODEL_SOURCES_EXT})

FILE(GLOB_RECURSE MODEL_INCLUDES "include/*.h")

# Create named folders 
source_group("src" FILES ${MODEL_SOURCES})
source_group("include" FILES ${MODEL_INCLUDES})

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

add_library (DeviceEmulatorModel SHARED ${MODEL_SOURCES})
target_link_libraries( DeviceEmulatorModel ${Boost_LIBRARIES} ${LOG4CXX_LIBRARIES} ${PYTHON_LIBRARIES})

# Creates a folder "libraries" and adds target project under it
set_property(TARGET DeviceEmulatorModel PROPERTY FOLDER "libraries")

# Define the wrapper library 
add_library( DeviceEmulatorModel_ext SHARED ${MODEL_SOURCES_EXT} )
target_link_libraries( DeviceEmulatorModel_ext ${Boost_LIBRARIES} DeviceEmulatorModel ${PYTHON_LIBRARIES})

# Don't prepend wrapper library name with lib
set_target_properties( DeviceEmulatorModel_ext PROPERTIES PREFIX "" )
set_property(TARGET DeviceEmulatorModel_ext PROPERTY FOLDER "libraries")
