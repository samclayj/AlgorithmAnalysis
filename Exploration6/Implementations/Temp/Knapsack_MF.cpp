//
//  Knapsack_MF.cpp
//  Knapsack_Dynamic
//
//  Created by Sam Jentsch on 11/21/14.
//  Copyright (c) 2014 Sam Jentsch. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sys/timeb.h>
#include <time.h>

#define START 0
#define END 1

using namespace std;

int **dynamicTable;

int capacity;
int items;
vector<int> weights;
vector<int> values;

void printTable();
int max(int num1, int num2);
int MFKnapsack(int i, int j);
void populateVariables(fstream& file);
int Time1(int);


int main(int argc, const char * argv[]) {
    
    fstream infile(argv[1], ios::in);
    if (!infile.is_open()) {
        cout<<"File not found."<<endl;
        return -1;
    }
    
    populateVariables(infile);
    
    
    //---INITIALIZE TABLE---//
    dynamicTable = new int *[items + 1];
    for (int i = 0; i <= items; i++) {
        dynamicTable[i] = new int[capacity + 1];
    }
    
    for (int i = 0; i <= items; i++) {
        for (int j = 0; j <= capacity; j++) {
            if (i == 0 || j == 0) {
                dynamicTable[i][j] = 0;
            } else {
                dynamicTable[i][j] = -1;
            }
        }
    }
    
    //printTable();
    //-----TIMING-----//
    int time = 0;
    
    time = Time1(START);
    //warshall(adjMatrix, n);
    time = Time1(END);
    cout << "\nTIME: " << time << endl;
    cout << MFKnapsack(items, capacity) << endl;
    
    printTable();
    
    return 0;
}

int MFKnapsack(int i, int j) {
    int value = 0;
    if (dynamicTable[i][j] < 0) {
        if (j < weights[i-1]) {
            value = MFKnapsack(i-1, j);
        } else {
            value = max(MFKnapsack(i-1, j), values[i-1] + MFKnapsack(i-1, j-weights[i-1]));
        }
        dynamicTable[i][j] = value;
    }
    return dynamicTable[i][j];
}

int max(int num1, int num2) {
    if (num1 >= num2) {
        return num1;
    } else {
        return num2;
    }
}

void printTable() {
    cout << "PRINT TABLE\n";
    for (int iCount = 0; iCount <= items; iCount++) {
        for (int jCount = 0; jCount <= capacity; jCount++) {
            cout <<setw(3)<< dynamicTable[iCount][jCount];
        }
        cout << endl;
    }
}

void populateVariables(fstream& file){
        int count = 0;
        int i = 0;
        int value = 0;
    
        while(file >> value){
            if (count==0){
                capacity= value;
                cout<<"Capacity = "<<capacity<<endl;

                //System.out.println("Capacity is:"+capacity);
                count++;
                file>>value;
            }
            if (count==1){
                
                items = value;
                cout<<"Items = "<<items<<endl;

                //System.out.println(items+" items");
                count++;
            }
            else if(count>1){
                
                weights.push_back(value);
                file >>value;
                
                values.push_back(value);
                cout<<weights[i]<<" "<<values[i]<<endl;
                count++;
                i++;
            }
        }
        file.close();
    }
    
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


