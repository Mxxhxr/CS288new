#!/bin/bash

echo "Enter a file name"
read fname

if [ -z "$fname" ]
then
    echo "Error no input"
else
    if [ -f "$fname" ]
    then
        tail -n 10 "$fname"
    else
        echo "File does not exist"
        exit 100
    fi
fi