Device emulator
===============

Project for emulating devices which help us to test systems in isolation and run regression tests. 

Getting Started
---------------

To build device-emulator you will need:

 * CMake >= 2.8   
 * Boost libraries 1.49

To compile all the modules:

    cd build
    cmake ..
    make
    
To run all tests:   

    ./build/test/UnitTests
    
Definitions
---------------

Emulation is the process of mimicking the outwardly observable behaviour to match an existing target. The internal state of the emulation mechanism does not have to accurately reflect the internal state of the target which it is emulating.
Simulation, on the other hand, involves modelling the underlying state of the target. The end result of a good simulation is that the simulation model will emulate the target which it is simulating.

Goals
---------------

1) Create an API in C++ for emulating devices.
2) Wrap the C++ device emulator API with Boost-Python.
3) Use Python for writing test cases. This will allow us to use the power of an interpreted language to write fast tests and compose them easily.

Logical view
---------------

  * A device communicates with other devices through communication channels and exchange some data with them in a specific order (protocol).
  * A device is composed of a set of behaviours.
  * A behaviour is a runnable instance which executes a set of device orders (mainly send and receive commands). 
    This set of orders could be an infinite set (i.e. for polling behaviours).
  * This schema allow us to write test cases reusing device behaviours. 
    For example we could seen the initial handshake of a protocol as the initial behaviour of a device (which will be present in all tests cases)


{Device A}  ---------- Comm. channel ---------- {Device B}

Device A (emulated device): 

Behaviours
 - Handshake: For initializing the communication (several messages are interchanged). Reused between test cases.
 - Polling: Every n seconds a message shall be sent and a timing window shall be opened for waiting the response. Reused between test cases.
 - Others: Other behaviours which could be reused. For example, response with a message to a specific one. (GetCurrentTime, ...). Reused between test cases.
 - Test-specific-behaviour: Specific behaviour for executing the test case (probably some messages are interchanged). Not reused.
