#!/bin/bash

echo "Enter a file name"
read fname


if [ -f $fname ]
then
    cp "$fname" "$fname.bak"
else
    echo "File does not exist"
fi