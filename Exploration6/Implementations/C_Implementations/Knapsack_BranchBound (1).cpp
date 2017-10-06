//
//  main.cpp
//  Knapsack_BranchBound
//
//  Created by Sam Jentsch on 11/23/14.
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

struct TreeNode {
    TreeNode() {
        upperBound = 0;
        totalWeight = 0;
        totalValue = 0;
        leftChild = NULL;
        rightChild = NULL;
    }
    
    TreeNode(int ub, int tw, int tv) {
        upperBound = ub;
        totalWeight = tw;
        totalValue = tv;
        leftChild = NULL;
        rightChild = NULL;
    }
    
    int upperBound;
    int totalWeight;
    int totalValue;
    TreeNode *leftChild;
    TreeNode *rightChild;
} TreeNode;

struct Item {
    int weight;
    int value;
    double WVRatio;
} Item;

struct TreeNode root;
vector<struct Item> items;
int capacity;

int branchBoundKnapsack(struct TreeNode *currentNode, int nodeLevel);
void BubbleSort(vector<struct Item> &vect);

void populateVariables(fstream& file);
int Time1(int);

int main(int argc, const char * argv[]) {
    //Sort items in descending order by their given value-to-weight
    //ratios.
    
    //First item gives best payoff per wight unit and last gives the
    //worst payoff per weight unit.
    
    //A branch going to the left indicates the inclusion of the next item,
    //a branch going to the right indicates the exclusion of the next item.
    
    //ub = v + (W - w)(nextI_V / nexti_W)
    
    fstream infile(argv[1], ios::in);
    if (!infile.is_open()) {
        cout<<"File not found."<<endl;
        return -1;
    }
    
    populateVariables(infile);
    
    //Figure out how to sort items.
    //items = {{3, 12}, {7, 42}, {5, 25}, {4, 40}};
    
    //capacity = 10;
    
    for (int i = 0; i < items.size(); i++) {
        items.at(i).WVRatio = (double)items.at(i).value/items.at(i).weight;
        //cout << items.at(i).WVRatio << endl;
    }
    
    BubbleSort(items);
    
    root = {0, 0, 0};
    
    //-----TIMING-----//
    int time = 0;
    
    time = Time1(START);
    int max = branchBoundKnapsack(&root, 0);
    cout << "FINAL VALUE: " << max << endl;
    time = Time1(END);
    cout << "\nTIME: " << time << endl;
    
    
    return 0;
}

int branchBoundKnapsack(struct TreeNode *currentNode, int nodeLevel) {
    int value = 0;
    
    //ub = v + (W-w)(vi+1/wi+1)
    int valueIncludeI = (currentNode->totalValue+items.at(nodeLevel).value);
    int weightIncludeI = (currentNode->totalWeight+items.at(nodeLevel).weight);
    
    if (nodeLevel+1 >= items.size()) {
        //Base case
        //Current Node is a leaf.
        int maxValue;
        if (valueIncludeI > currentNode->totalValue && (weightIncludeI <= capacity)) {
            maxValue = valueIncludeI;
        } else {
            maxValue = currentNode->totalValue;
        }
        
        //cout << "MAX VALUE: " << maxValue << endl;
        return maxValue;
    } else {
        //Current node is not a leaf.
        int upperBoundLeft = valueIncludeI + (capacity - weightIncludeI)*(items.at(nodeLevel+1).WVRatio);
        int upperBoundRight = currentNode->totalValue + (capacity - currentNode->totalWeight)*(items.at(nodeLevel+1).WVRatio);
        
        //cout << upperBoundLeft << " " << upperBoundRight << endl;
        
        struct TreeNode *leftChild = new struct TreeNode(upperBoundLeft, weightIncludeI, valueIncludeI);
        struct TreeNode *rightChild = new struct TreeNode(upperBoundRight, currentNode->totalWeight, currentNode->totalValue);
        
        currentNode->leftChild = leftChild;
        currentNode->rightChild = rightChild;
        
        
        //----Select Next Path----//
        int leftValue = -1;
        int rightValue = -1;
        if ((upperBoundLeft > upperBoundRight) && weightIncludeI <= capacity) {
            leftValue = branchBoundKnapsack(currentNode->leftChild, nodeLevel + 1);
            //Make sure it was the best
            if (leftValue < upperBoundRight) {
                rightValue = branchBoundKnapsack(currentNode->rightChild, nodeLevel + 1);
            }
        } else {
            rightValue = branchBoundKnapsack(currentNode->rightChild, nodeLevel + 1);
            //Make sure it was the best
            if (rightValue < upperBoundLeft && weightIncludeI <= capacity) {
                leftValue = branchBoundKnapsack(currentNode->leftChild, nodeLevel + 1);
            }
        }
        
        //Get the max from the 2 branches
        if (leftValue >= rightValue) {
            value = leftValue;
        } else {
            value = rightValue;
        }
    }
    
    return value;
}

void BubbleSort(vector<struct Item> &vect) {
    int i, j, flag = 1;    // set flag to 1 to start first pass
    struct Item temp;             // holding variable
    for(i = 1; i <= vect.size() && flag; i++) {
        flag = 0;
        for (j=0; j < (vect.size() - 1); j++)
        {
            if (vect.at(j+1).WVRatio > vect.at(j).WVRatio) {
                temp = vect.at(j);
                vect.at(j) = vect.at(j+1);
                vect.at(j+1) = temp;
                flag = 1;               // indicates that a swap occurred.
            }
        }
    }
    return;   //arrays are passed to functions by address; nothing is returned
}

void populateVariables(fstream& file){
    int count = 0;
    int value = 0;
    
    while(file >> value){
        if (count == 0){
            capacity= value;
            //cout << "Capacity = " << capacity << endl;
            
            count++;
        } else if (count==1){
           //int numItems = value;
           count++;
        } else if(count>1){
            int weight;
            
            weight = value;
            file >> value;
            
            struct Item newItem = {weight, value, 0};
            //cout << "Adding new Item. Weight: " << newItem.weight << " Value: " << newItem.value << endl;
            items.push_back(newItem);
            
            count++;
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
