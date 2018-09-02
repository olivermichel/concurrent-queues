#!/usr/bin/env bash

if [ "$#" -ne "4" ]
then
    echo "usage: $0 NUMA N B C";
    exit 1;
fi

if [ "$1" -eq "1" ]
then
    numa="numactl -N 0 -m 0 "
else
    numa=""
fi

mkdir -p out

cmd="${numa}${EXE_PATH:-./build}/queue5_detail --bytes $3 --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd 2>&1 | tee -a out/queue5_detail.csv
    sleep 1
done
