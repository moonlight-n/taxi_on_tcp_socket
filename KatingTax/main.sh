#! /bin/bash

killall server
killall driver
killall passengers
sleep 1

./server &
sleep 1
./driver Низамидин к955ау &
sleep 1 
./passengers A

exit 0;