#!/bin/bash

printf \\n\\n
g++ Knapsack_BF.CPP -o KnapsackBF

printf \\n
printf "For n=4 objects: "\\n
./KnapsackBF ../DATAFILES/04objects.dat

printf \\n
printf "For n=8 objects: "\\n
./KnapsackBF ../DATAFILES/08objects.dat

printf \\n
printf "For n=16 objects: "\\n
./KnapsackBF ../DATAFILES/016objects.dat

printf \\n
printf "For n=32 objects: "\\n
./KnapsackBF ../DATAFILES/032objects.dat

printf \\n
printf "For n=64 objects: "\\n
./KnapsackBF ../DATAFILES/064objects.dat

printf \\n
printf "For n=128 objects: "\\n
./KnapsackBF ../DATAFILES/0128objects.dat

printf \\n
printf "For n=4 objects 10 capacity: "\\n
./KnapsackBF ../DATAFILES/10capacity.dat

printf \\n
printf "For n=4 objects 100 capacity: "\\n
./KnapsackBF ../DATAFILES/100capacity.dat

printf \\n
printf "For n=4 objects 1000 capacity: "\\n
./KnapsackBF ../DATAFILES/1000capacity.dat

printf \\n
printf "For n=4 objects 10000 capacity"\\n
./KnapsackBF ../DATAFILES/10000capacity.dat

printf \\n
printf "For n=4 objects 100000 capacity"\\n
./KnapsackBF ../DATAFILES/100000capacity.dat
printf \\n\\n

