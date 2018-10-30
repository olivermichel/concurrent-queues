#!/usr/bin/env bash

if [ "$#" -ne "6" ]
then
    echo "usage: $0 NUMA N B C1 C2 OUT";
    exit 1;
fi

if [ "$1" -eq "1" ]
then
    numa="numactl -N 0 -m 0 "
else
    numa=""
fi

mkdir -p out

cmd="${numa}${EXE_PATH:-./build}/queue1 --bytes $3 --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/queue2 --bytes $3 --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/queue3 --bytes $3 --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/queue4 --bytes $3 --count $5"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/queue5 --bytes $3 --count $5"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done

cmd="${numa}${EXE_PATH:-./build}/moodycamel_queue --bytes $3 --count $5"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a $6
    sleep 1
done
