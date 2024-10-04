#!/bin/bash

filteredLines=()

while IFS= read -r line || [ -n "$line" ]; do
    if echo "$line" | grep -i -E '^.*,.*,\s[a-zA-z]+\s[a-zA-Z]+.*,.*$' > /dev/null; then
        filteredLines+=("$line")
    fi
done < $1

declare -A peopleData

for line in "${filteredLines[@]}"; do
    dateOfBirth=$(echo "$line" | sed -n 's/.*,\s*\([0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}\).*/\1/p')
    birthYear=$(echo "$dateOfBirth" | cut -d'-' -f1) #this cuts before first delimiter aka the -

    name=$(echo "$line" | sed -n 's/^\s*\([a-zA-Z]\+\s[a-zA-Z]\+\),.*$/\1/p')
    
    age=$((2024 - $birthYear))

    peopleData["$name"]="$age"
done

for name in "${!peopleData[@]}"; do
    echo "$name: ${peopleData[$name]}"
done | sort -t ':' -k2 -nr

