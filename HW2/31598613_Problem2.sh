# !/bin/bash

numScanf=`grep -E 'scanf' $1 | wc -l`
numPrintf=`grep -E 'printf' $1 | wc -l`
totalLines=`wc -l < $1`
percentScanf=$((numScanf * 100 / totalLines))
percentPrintf=$((numPrintf * 100 / totalLines))
echo "Number of scanf: $numScanf"
echo "Number of printf: $numPrintf"
echo "Total number of lines: $totalLines"

echo "Percent of lines containing scan: $percentScanf%"
echo "Percent of lines containing scan: $percentPrintf%"

if [ ! -e scanf_log.txt ]; then
    touch scanf_log.txt
fi

if [ ! -e printf_log.txt ]; then
    touch printf_log.txt
fi

for i in $numScanf; do
    grep -E 'scanf' $1 >> scanf_log.txt
done

for j in $numPrintf; do
    grep -E 'printf' $1 >> printf_log.txt
done