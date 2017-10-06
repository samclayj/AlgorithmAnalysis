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
void bottomUpKnapsack(vector<int> weights, vector<int> values);
void populateVariables(fstream& file)

int main(int argc, const char * argv[]) {

    fstream infile("../instr/list5.dat", ios::in);
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
            dynamicTable[i][j] = 0;
        }
    }

    //printTable();
    
    bottomUpKnapsack(weights, values);
    
    printTable();

    return 0;
}

void bottomUpKnapsack(vector<int> weights, vector<int> values) {
 //if j - iWeight >= 0, F(i, j) = max{F(i-1,j), iValue + F(i-1), j-iWeight)}
 //else F(i,j) = F(i-1,j)
    
    for (int i = 1; i <= items; i++) {
        for (int j = 1; j <= capacity; j++) {
            if (j - weights.at(i-1) >= 0) {
                //F(i, j) = max{F(i-1,j), iValue + F(i-1), j-iWeight)}
                dynamicTable[i][j] = max(dynamicTable[i-1][j], values.at(i-1) + dynamicTable[i-1][j-weights.at(i-1)]);
            } else {
                //F(i,j) = F(i-1,j)
                dynamicTable[i][j] = dynamicTable[i-1][j];
            }
        }
    }
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
