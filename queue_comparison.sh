#!/usr/bin/env bash

#
# jetstream network analytics
# (c) Oliver Michel 2018
#

if [ "$#" -ne "5" ]
then
    echo "usage: $0 NUMA N B C1 C2";
    exit 1;
fi

if [ "$1" -eq "1" ]
then
    numa="numactl -N 0 -m 0 "
else
    numa=""
fi

cmd="${numa}${EXE_PATH:-./../../build/experiments/queue_performance}/queue1 --bytes $3 --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd >> queue1.csv
done

cmd="${numa}${EXE_PATH:-./../../build/experiments/queue_performance}/queue2 --bytes $3 --count $4"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd >> queue2.csv
done

cmd="${numa}${EXE_PATH:-./../../build/experiments/queue_performance}/queue3 --bytes $3 --count $5"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd >> queue3.csv
done

cmd="${numa}${EXE_PATH:-./../../build/experiments/queue_performance}/moodycamel_queue --bytes $3 --count $5"
echo "# $2 * $cmd"

for (( i=0; i < $2; i++ ))
do
    $cmd >> moodycamel_queue.csv
done

python queue_comparison_analysis.py
