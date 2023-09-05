#!/bin/bash

# you should execute this script giving the number of philosophers as argument
# and having an outfile in the current directory

idx=-1
philos="$1"

while [ $((++idx)) -lt "$philos" ]
do
    cat outfile | grep "$idx is eating" | wc -l
done
