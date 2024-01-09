#! /bin/bash
killall server
killall driver
killall passengers

if [ $# -ne 2 ]; then
  echo "Необходимо 2 параметра, 1 - количество водителей(1-4), 2 - количество пассажиров(1-6)"
else
    if [[ "$1" =~ ^[1-4]+$ ]]; then
        drivers=$1
        if [[ "$2" =~ ^[1-6]+$ ]]; then
        passengers=$2
    else 
        echo "Параметр пассажиров "$2" не подходит"
        exit 0;
    fi
    else 
        echo "Параметр водителей "$1" не подходит"
    exit 0;
    fi
./server &
sleep 2
driver1="./driver Низамидин к955ау"
driver2="./driver Арсен о456го"
driver3="./driver Геннадий х777хх"
driver4="./driver Галина у511ум"
passenger1="./passengers A"
passenger2="./passengers B"
if [ $drivers -eq 1 ]; then
    $driver1 &
fi
if [ $drivers -eq 2 ]; then
    $driver1 &
    sleep 2
    $driver2 &
fi
if [ $drivers -eq 3 ]; then
    $driver1 &
    sleep 2
    $driver2 &
    sleep 2
    $driver3 &
fi
if [ $drivers -eq 4 ]; then
    $driver1 &
    sleep 2
    $driver2 &
    sleep 2
    $driver3 &
    sleep 2
    $driver4 &
fi

if [ $passengers -eq 1 ]; then
    $passenger1 &
fi
if [ $passengers -eq 2 ]; then
    $passenger1 &
    sleep 1
    $passenger1 
fi
if [ $passengers -eq 3 ]; then
    $passenger1 &
    sleep 1
    $passenger1 &
    sleep 5
    $passenger1
fi
if [ $passengers -eq 4 ]; then
    $passenger1 &
    sleep 1
    $passenger1 &
    sleep 5
    $passenger1 &
    sleep 5
    $passenger2 
fi
if [ $passengers -eq 5 ]; then
    $passenger1 &
    sleep 1
    $passenger1 &
    sleep 5
    $passenger1 &
    sleep 5
    $passenger2 &
    sleep 8
    $passenger2 
fi
if [ $passengers -eq 6 ]; then
    $passenger1 &
    sleep 1
    $passenger1 &
    sleep 5
    $passenger1 &
    sleep 5
    $passenger2 &
    sleep 8
    $passenger2 &
    sleep 8
    $passenger2 
fi
fi