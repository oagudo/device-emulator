echo 'Running model tests ...'
test/UnitTests

export PYTHONPATH=$PYTHONPATH:./model
echo 'Running python extension tests ...'

echo ' - Orders extension tests ...'
python ../test/src/device/orders/order_list_ext.py

echo ' - Behaviour state extension tests ...'
python ../test/src/device/states/device_behaviour_state_ext.py

echo ' - TCP Comms extension tests ...'
python ../test/src/comms/tcp/tcp_comms_ext.py

echo ' - Device extension tests ...'
python ../test/src/device/device_ext.py
