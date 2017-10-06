//
//  main.cpp
//  Knapsack_Dynamic
//
//  Created by Sam Jentsch on 11/21/14.
//  Copyright (c) 2014 Sam Jentsch. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int **dynamicTable;

int capacity;
int items;
vector<int> weights;
vector<int> values;

void printTable();
int max(int num1, int num2);
int MFKnapsack(int i, int j);

int main(int argc, const char * argv[]) {
    
    weights = {2, 1, 3, 2};
    values = {12, 10, 20, 15};
    
    
    items = 4;
    capacity = 5;
    
    
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
            cout << dynamicTable[iCount][jCount] << " ";
        }
        cout << endl;
    }
    
}