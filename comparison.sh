#!/usr/bin/env bash

if [ "$#" -ne "5" ]
then
    echo "usage: $0 NUMA N C1 C2 OUT";
    exit 1;
fi

if [ "$1" -eq "1" ]
then
    numa="numactl -N 0 -m 0 "
else
    numa=""
fi

mkdir -p out

cmd="${numa}${EXE_PATH:-./build}/queue1 --count $3"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/queue2 --count $3"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/queue4 --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/queue5 --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/moodycamel_queue --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done
