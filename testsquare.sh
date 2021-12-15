#!/bin/bash

for i in {1..4}; do
	echo export OMP_NUM_THREADS
	echo ./main.exe $1 >> times.dat
done
