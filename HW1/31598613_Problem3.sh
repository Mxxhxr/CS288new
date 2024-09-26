#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "Error: At least 3 file names are required"
    exit 1
fi

mkdir backup_$(date +%Y%m%d) 

for file in "$@"; do
    if [ -e "$file" ]; then
        echo "File '"$file"' exists."
        cp "$file" "backup_$(date +%Y%m%d)/"$file"_$(date +%Y%m%d)"

        cd backup_$(date +%Y%m%d) && touch log.txt
        echo "Old Name: $file ----> New Name: "$file"_$(date +%Y%m%d)" >> log.txt  
        cd ..
    else
        echo "Warning: File '"$file"' does not exist. Skipping this file."
        fi 
done

printf "\nBackup completed successfully.\n"
cd backup_$(date +%Y%m%d)
echo "Backup directory: $(pwd)"