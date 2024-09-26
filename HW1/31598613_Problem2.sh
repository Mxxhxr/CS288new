#!/bin/bash

fileOrDir=$1

if [ -z $1  ]; then
    echo "Please enter a file or directory"
    read fileOrDir
fi

if [ -f "$fileOrDir" ]; then
    echo "It is a file"
    if [ -r "$fileOrDir" ]; then
        printf "It is readable\n\n"

        wordCount=$(wc -w < "$fileOrDir")
        lineCount=$(wc -l < "$fileOrDir" )
        charCount=$(wc -m < "$fileOrDir")
        
        echo "Word count: $wordCount"
        echo "Line count: $lineCount"
        printf "Character count: $charCount\n\n"
        
        if [ $charCount -lt 1000 ]; then
            echo "Light File"
        elif [[ $charCount -ge 1000 && $charCount -le 10000 ]]; then
            echo "Moderately Sized"
        elif [ $charCount -gt 10000 ]; then
            echo "Heavy File"
        fi
    else
        echo "Warning: File is not readable"
        exit 1
    fi

elif [ -d "$fileOrDir" ]; then
    echo "It is a directory"
    if [[ -r "$fileOrDir" && -x "$fileOrDir" ]]; then
        printf "It is readable and executable\n\n"

        numFiles=$(ls -l "$fileOrDir" | egrep -c ^-)
        numDirs=$(ls -l ""$fileOrDir"" | egrep -c ^d)
        
        echo "Number of files: $numFiles"
        printf "Number of subdirectories: $numDirs\n\n"

        for object in ""$fileOrDir""/*; do
            size=$(stat -c%s $object)  # had to look up how to get the size in bytes
            if [ -d $object ]; then
                echo "Directory: $(basename $object) --- $size bytes"
            else
                echo "File: $(basename $object) --- $size bytes"
            fi
        done
    else
        echo "Warning: Directory is not readable and/or executable"
        exit 1
    fi
else
    exit 1
fi