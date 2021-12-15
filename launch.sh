#!/bin/bash

for i in {1..4}; do
    for j in {1..5}; do
	 echo export OMP_NUM_THREADS=$i
	 echo $(./main.exe $1 $i) >> times.dat
    done
done
