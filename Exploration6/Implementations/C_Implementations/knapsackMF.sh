#!/bin/bash

printf \\n\\n
g++ Knapsack_MF.cpp -o KnapsackMF

printf \\n
printf "For n=4 objects: "\\n
./KnapsackMF ../DATAFILES/04objects.dat

printf \\n
printf "For n=8 objects: "\\n
./KnapsackMF ../DATAFILES/08objects.dat

printf \\n
printf "For n=16 objects: "\\n
./KnapsackMF ../DATAFILES/016objects.dat

printf \\n
printf "For n=32 objects: "\\n
./KnapsackMF ../DATAFILES/032objects.dat

printf \\n
printf "For n=64 objects: "\\n
./KnapsackMF ../DATAFILES/064objects.dat

printf \\n
printf "For n=128 objects: "\\n
./KnapsackMF ../DATAFILES/0128objects.dat

printf \\n
printf "For n=4 objects 10 capacity: "\\n
./KnapsackMF ../DATAFILES/10capacity.dat

printf \\n
printf "For n=4 objects 100 capacity: "\\n
./KnapsackMF ../DATAFILES/100capacity.dat

printf \\n
printf "For n=4 objects 1000 capacity: "\\n
./KnapsackMF ../DATAFILES/1000capacity.dat

printf \\n
printf "For n=4 objects 10000 capacity"\\n
./KnapsackMF ../DATAFILES/10000capacity.dat

printf \\n
printf "For n=4 objects 100000 capacity"\\n
./KnapsackMF ../DATAFILES/100000capacity.dat
printf \\n\\n

