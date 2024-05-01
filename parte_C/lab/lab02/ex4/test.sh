#!/bin/zsh
#File test.sh
#This script tests the program ex4

list=(10 125 255 256 355 -1)

if [ ! -f provaValoriWait ]; then
    echo "File not found! Compile the program first."
    exit 1
fi

for i in $(seq 1 6);
do
    echo "Test $i -> INPUT: ${list[$i]}\n"
    echo "${list[$i]}" | ./provaValoriWait
    echo "$i ok\n"
done

