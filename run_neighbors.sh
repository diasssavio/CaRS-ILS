#!/bin/bash
for i in $(seq 17)
do
	for j in instances/neighborhoods_tests/*.txt
	do
		FILE=$(basename "$j" .txt)
		echo "Instance $FILE:"
		./CaRS-ILS $j 1 $i >> logs/individual.csv
		echo "$i...ok!"
	done
done
