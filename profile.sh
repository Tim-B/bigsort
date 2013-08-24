#!/bin/bash

EXEC="bin/bigsort"
SRCFILE="bin/random.txt"
DESTFILE="bin/sorted.txt"
RES="results.txt"

POINTS=(1000 2000 4000 8000 16000 32000 64000 128000 256000 512000 1024000 2048000 4096000 8192000 16384000 32768000 65536000 131072000 262144000 524288000)

rm -f $RES
touch $RES

for i in "${POINTS[@]}";
do
    echo "==========" >> $RES
    echo "$i" >> $RES
    { time $EXEC $SRCFILE $DESTFILE $i ; } 2>> $RES
    echo "==========" >> $RES
done
echo "Done"