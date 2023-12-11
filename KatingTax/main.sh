#! /bin/bash

killall server
killall driver
killall passengers
sleep 1

./server &
sleep 1
./driver Низамидин к955ау &
sleep 1
./driver Арсен о456го &
sleep 1
#./driver Геннадий х777хх&
#sleep 1
#./driver Галина у511ум &
./passengers A &
#sleep 4
./passengers A 
#sleep 14
#./passengers B &
#sleep 13 
#./passengers A &
#sleep 12
#./passengers A &
#sleep 11 
#./passengers B &
#sleep 1 
#./passengers B &
#sleep 1 
#./passengers A 

exit 0;