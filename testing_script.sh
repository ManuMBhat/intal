#!/bin/sh
$max = 1000
for i in 'seq $max'
do
	python3 testing.py
	a.out < input.txt > output.txt
	if grep -F "failed" "output.txt"; then
		echo "Failed"
done


