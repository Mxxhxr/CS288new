#!/bin/bash

function traverse() {
    if [ -d "$1" ]; then
        entries=("$1"/*)
        for entry in "${entries[@]}"; do
            if [[ "$entry" == *.txt ]]; then
                # echo "$entry"
                grep -E '^[a-zA-Z0-9._+-]+@[a-zA-Z0-9]+\.[a-zA-Z]+$' $entry | sort | uniq >> unique_emails.txt
            elif [ -d "$entry" ]; then
                traverse "$entry"
            fi
            #
        done
    fi
}


if [ ! -e unique_emails.txt ]; then
    touch unique_emails.txt
fi

if [ ! -d $dirName ]; then
    echo "Directory does not exist"
    exit 1
fi

traverse $1

sort unique_emails.txt | uniq | tee unique_emails.txt > /dev/null