#!/usr/bin/env bash


cmd="${numa}${EXE_PATH:-./build}/queue5_detail --bytes 8 --count 50000000"
echo "# $2 * $cmd"

for (( i=0; i < 20; i++ ))
do
    $cmd
    sleep 1
done
