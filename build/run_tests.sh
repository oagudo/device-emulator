echo 'Running model tests ...'
test/UnitTests

export PYTHONPATH=$PYTHONPATH:./model
echo 'Running python extension tests ...'

echo ' - Orders extension tests ...'
python ../test/src/device/orders/OrderList_ext.py

echo ' - Behaviour state extension tests ...'
python ../test/src/device/states/DeviceBehaviourState_ext.py

echo ' - TCP Comms extension tests ...'
python ../test/src/comms/tcp/TCPComms_ext.py
