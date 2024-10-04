#!/bin/bash

# Part 1:
grep -i -E '(a.*a.*a)' ./dictionary.txt | wc -l

# Part 2:
grep -i -E 'e[^e]+e[^e]+e' ./dictionary.txt | wc -l

# Part 3:
grep -i -E 'ee' ./dictionary.txt | sed 's/.*\(.\{4\}\)$/\1/' | sort | uniq -c | sort -nr | head -n 3
