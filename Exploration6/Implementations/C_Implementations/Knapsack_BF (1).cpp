
//
//  Knapsack_BF.cpp
//  Knapsack_BruteForce
//
//  Created by Sam Jentsch on 11/20/14.
//  Copyright (c) 2014 Sam Jentsch. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sys/timeb.h>
#include <time.h>

#define START 0
#define END 1

int capacity;
int items;
std::vector<int> weights;
std::vector<int> values;

using namespace std;

string knapsack(vector<int> weights, vector<int> values, int capacity);
std::vector<string> BRGC(int n);
void printVect(vector<string> vect);
void populateVariables(fstream& file);
int Time1(int);


int main(int argc, const char * argv[]) {
    //Given n items of known weights and values and a knapsack of capapcity W,
    //find the most valuable subset of items that fit into the knapsack.
    
    //Generate all subsets of the set of n items given, computing the total weight
    //of each subset to identify feasible subsets and find the subset with the largest
    //value among them.
    
    //Number of subsets of an n element set is 2^n

    fstream infile(argv[1], ios::in);
    if (!infile.is_open()) {
        cout<<"File not found."<<endl;
        return -1;
    }
    
    populateVariables(infile);
    
    //-----TIMING-----//
    int time = 0;
    
    time = Time1(START);

    string solution = knapsack(weights, values, capacity);
    time = Time1(END);
    cout << "\nTIME: " << time << endl;
    cout << solution << endl;
    
    
    return 0;
}

string knapsack(vector<int> weights, vector<int> values, int capacity) {
    string bestSet;
    int bestValue = 0;
    
    vector<string> subsets = BRGC((int)weights.size());
    printVect(subsets);
    
    for (int i = 0; i < subsets.size(); i++) {
        string set = subsets.at(i);
        int setValue = 0;
        int setWeight = 0;
        
        bool isFeasible = true;
        
        //cout << "Checking set: " << set << endl;
        for (int j = 0; j < set.size() && isFeasible; j++) {
            if (set.at(j) == '1') {
                //Value at position j is in the subset.
                setValue += values.at(j);
                setWeight += weights.at(j);
            }
            
            if (setWeight > capacity) {
                isFeasible = false;
            }
        }
        
        if (setValue > bestValue && isFeasible) {
            bestValue = setValue;
            bestSet = set;
        }
    }//end go through all subsets.
    
    
    cout << "Best Value: " << bestValue << endl;
    return bestSet;
}

vector<string> BRGC(int n) {
    //Generates the binary reflected gray code of order n
    //Input: positive integer n
    //Output: A list of all bit strings of length n composing the gray code.
    
    vector<string> L;
    
    if (n == 1) {
        //make list L containing bit strings 0 and 1 in this order.
        L.push_back("0");
        L.push_back("1");
        //printVect(L);
    } else {
        //Generate list L1 of bit strings of size n-1 by calling BRGC(n-1)
        vector<string> L1 = BRGC(n-1);
        //cout << "N = " << n << " L1 size: " << L1.size() << "\n";
        
        //Copy list L1 to List L2 in reverse order.
        vector<string> L2;
        for (int i = (int)L1.size() - 1; i >= 0; i--) {
            //cout << "i = " << i << "\n";
            L2.push_back(L1.at(i));
        }
        
        //Add 0 in front of each bit string in List L1 and 1 in front of each
        //bit string in L2.
        for (int i = 0; i < L1.size(); i++) {
            L1.at(i).insert(0, "0");
            //cout << "L1." << i << " is now " << L1.at(i) << endl;
            L2.at(i).insert(0, "1");
            //cout << "L2." << i << " is now " << L2.at(i) << endl;
        }
        
        //Append L2 to L1 to get list L.
        for (int i = 0; i < L2.size(); i++) {
            L1.push_back(L2.at(i));
        }
        
        //L is the combination of L2 and L1.
        L = L1;
    }
    
    return L;
}

void printVect(vector<string> vect) {
    cout << "PRINT VECT\n";
    for (int i = 0; i < vect.size(); i++) {
        cout << vect.at(i);
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
