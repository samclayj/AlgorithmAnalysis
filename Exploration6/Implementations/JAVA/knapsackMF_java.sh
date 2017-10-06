#!/bin/bash

printf \\n\\n
javac Java_Knapsack_MF.java

printf \\n
printf "For n=4 objects: "\\n
java Java_Knapsack_MF ../DATAFILES/04objects.dat

printf \\n
printf "For n=8 objects: "\\n
java Java_Knapsack_MF ../DATAFILES/08objects.dat

printf \\n
printf "For n=16 objects: "\\n
java Java_Knapsack_MF ../DATAFILES/016objects.dat

printf \\n
printf "For n=32 objects: "\\n
java Java_Knapsack_MF ../DATAFILES/032objects.dat

printf \\n
printf "For n=64 objects: "\\n
java Java_Knapsack_MF ../DATAFILES/064objects.dat

printf \\n
printf "For n=128 objects: "\\n
java Java_Knapsack_MF ../DATAFILES/0128objects.dat

printf \\n
printf "For n=4 objects 10 capacity: "\\n
java Java_Knapsack_MF ../DATAFILES/10capacity.dat

printf \\n
printf "For n=4 objects 100 capacity: "\\n
java Java_Knapsack_MF ../DATAFILES/100capacity.dat

printf \\n
printf "For n=4 objects 1000 capacity: "\\n
java Java_Knapsack_MF ../DATAFILES/1000capacity.dat

printf \\n
printf "For n=4 objects 10000 capacity"\\n
java Java_Knapsack_MF ../DATAFILES/10000capacity.dat

printf \\n
printf "For n=4 objects 100000 capacity"\\n
java Java_Knapsack_MF ../DATAFILES/100000capacity.dat
printf \\n\\n

