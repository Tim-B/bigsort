#!/bin/bash

FILE="bin/sorted.txt"

current=0

# 32-bit signed limit
prev=-2147483647

fail=0
total=0

while read -r line;
do
    current=$line
    if [ "$current" -lt "$prev" ]; then
        echo "Failure! $current not greater than $prev on line $total"
        ((fail++))
    fi
    prev=$current
    ((total++))
done < $FILE

echo "Finished, there were $fail failures from $total lines examined."