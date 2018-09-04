#!/usr/bin/env bash

if [ "$#" -ne "4" ]
then
    echo "usage: $0 NUMA N M Bmax";
    exit 1;
fi

if [ "$1" -eq "1" ]
then
    numa="numactl -N 0 -m 0 "
else
    numa=""
fi

mkdir -p out

for (( i=1; i <= $4; i++ ))
do
    cmd="${numa}${EXE_PATH:-./build}/queue5_batch --count $2 --batch $i"
    for (( j=1; j <= $3; j++ ))
    do
        $cmd 2>&1 | tee -a data/queue5_batch.csv
        sleep 1
    done
done
