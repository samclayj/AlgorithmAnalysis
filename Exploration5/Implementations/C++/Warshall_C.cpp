//
//  main.cpp
//  Warshall_C
//
//  Created by Sam Jentsch on 11/9/14.
//  Copyright (c) 2014 Sam Jentsch. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <stdlib.h>
#include <string>

#define START 0
#define END 1

using namespace std;

void warshall(int **adjMatrix, int dimension);
void printArray(int **numberArray, int dimension);
int Time1(int);

int main(int argc, const char * argv[]) {
    
    //string pathToDataFile = "../instr/AdjacencyMatrix.dat";
    string pathToDataFile(argv[1]);
    
    ifstream inputFile;
    inputFile.open(pathToDataFile.c_str());

    int n, i, j;
    inputFile >> n;
    
    int **adjMatrix;
    
    adjMatrix = new int *[n];
    
    for (i = 0; i < n; i++) {
        adjMatrix[i] = new int[n];
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            inputFile >> adjMatrix[i][j];
        }
    }
    
    printArray(adjMatrix, n);
    
    cout << endl;
    
    //-----TIMING-----//
    double time = 0;
    
    time = Time1(START);
    warshall(adjMatrix, n);
    time = Time1(END);
    cout << "\nTIME: " << time << endl;
    
    
    return 0;
}

void warshall(int **R, int dimension) {

    for (int k = 0; k < dimension; k++) {
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                R[i][j] = R[i][j] | (R[i][k] && R[k][j]);
            }
        }
    }
    
    printArray(R, dimension);
}

void printArray(int **numberArray, int dimension) {
    //Print the array
    int i, j;
    for(i = 0; i < dimension; i++) {
        for(j = 0; j < dimension; j++) {
            cout << numberArray[i][j] << ' ';
        }
        cout << "\n";
    }
}//printArray


int Time1(int flag) {
    //Timing method described in assignment handout.
    static struct timeb time1;
    struct timeb time2;
    int sec;
    unsigned short mil;
    
    if (flag == START) {
        ftime(&time1);
        return 0;
    } else {
        ftime(&time2);
        if (time2.millitm < time1.millitm) {
            time2.time--;
            mil = time2.millitm + 1000 - time1.millitm;
        } else {
            mil = time2.millitm - time1.millitm;
        }
        sec = (int)time2.time - (int)time1.time;
        return sec * 1000 + (int)mil;
    }
}