echo 'Running model tests ...'
test/UnitTests

export PYTHONPATH=$PYTHONPATH:./model
echo 'Running python extension tests ...'

echo ' - Message extension tests ...'
python ../test/src/Data/IMessage_ext.py

echo ' - Orders extension tests ...'
python ../test/src/Device/Orders/OrderList_ext.py

echo ' - Behaviour state extension tests ...'
python ../test/src/Device/States/DeviceBehaviourState_ext.py

echo ' - TCP Comms extension tests ...'
python ../test/src/Comms/TCP/TCPComms_ext.py
