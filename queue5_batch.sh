#!/usr/bin/env bash

if [ "$#" -ne "3" ]
then
    echo "usage: $0 NUMA N Bmax";
    exit 1;
fi

if [ "$1" -eq "1" ]
then
    numa="numactl -N 0 -m 0 "
else
    numa=""
fi

mkdir -p out


#TODO: i % $2 must be 0, other results currently omitted

for (( i=1; i <= $3; i++ ))
do
    cmd="${numa}${EXE_PATH:-./build}/queue5_batch --count $2 --batch $i"
    $cmd 2>&1 | tee -a out/queue5_batch.csv
    sleep 1
done
