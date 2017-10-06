//
//  main.cpp
//  Knapsack_BruteForce
//
//  Created by Sam Jentsch on 11/20/14.
//  Copyright (c) 2014 Sam Jentsch. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

string knapsack(vector<int> weights, vector<int> values, int capacity);
std::vector<string> BRGC(int n);
void printVect(vector<string> vect);

int main(int argc, const char * argv[]) {
    //Given n items of known weights and values and a knapsack of capapcity W,
    //find the most valuable subset of items that fit into the knapsack.
    
    //Generate all subsets of the set of n items given, computing the total weight
    //of each subset to identify feasible subsets and find the subset with the largest
    //value among them.
    
    //Number of subsets of an n element set is 2^n
    
    vector<int> weights = {7, 3, 4, 5};
    vector<int> values = {42, 12, 40, 25};
    
    string solution = knapsack(weights, values, 10);
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