# Boost Libraries
# For custom BOOST libraries
#set(Boost_INCLUDE_DIR $ENV{BOOST_HOME})
#set(Boost_LIBRARY_DIR $ENV{BOOST_HOME}/stage/x64)

# set( Boost_USE_STATIC_LIBS OFF )

find_package(Boost 1.49 COMPONENTS system thread date_time serialization REQUIRED)

FILE(GLOB_RECURSE KERNEL_SOURCES "src/*.cpp")
FILE(GLOB_RECURSE KERNEL_INCLUDES "include/*.h")

# Create named folders 
source_group("src" FILES ${KERNEL_SOURCES})
source_group("include" FILES ${KERNEL_INCLUDES})

# Include Directories
include_directories (./include) 
include_directories (${Boost_INCLUDE_DIR})

link_directories(${Boost_LIBRARY_DIR})

add_library (DeviceEmulatorKernel ${KERNEL_SOURCES})

target_link_libraries( DeviceEmulatorKernel ${Boost_LIBRARIES} )

# Creates a folder "libraries" and adds target project under it
set_property(TARGET DeviceEmulatorKernel PROPERTY FOLDER "libraries")
