//Java_Knapsack_MF.java

import java.io.*;
import java.util.*;


public class Java_Knapsack_MF {
    
	
	static int[] weights;
	static int[] values;
	static int items;
	static int capacity;
    static int dynamicTable[][];
    
	public static void main(String[] args) throws FileNotFoundException {
		Scanner infile = new Scanner(new File(args[0]));
		populateVariables(infile);
	    

	    
	    //---INITIALIZE TABLE---//
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
	   
	    long startTime = System.nanoTime();
        long stopTime = System.nanoTime();
        long overTime = stopTime - startTime;
        
        startTime = System.nanoTime();
        
        
	    System.out.println(MFKnapsack(dynamicTable,weights,values,items, capacity));
        

        stopTime = System.nanoTime();
        //Stop time for the algorithm
        
        long time = stopTime - startTime - overTime;
        System.out.println("Total time is: " +(time/1000000));
	    
	    
	    printTable(dynamicTable,items,capacity);
		
	}
	
	static int MFKnapsack(int dynamicTable[][],int weights[],int values[],int i, int j) {
	    int value = 0;
	    if (dynamicTable[i][j] < 0) {
	        if (j < weights[i-1]) {
	            value = MFKnapsack(dynamicTable,weights,values,i-1, j);
	        } else {
	            value = max(MFKnapsack(dynamicTable,weights,values,i-1, j), values[i-1] + MFKnapsack(dynamicTable,weights,values,i-1, j-weights[i-1]));
	        }
	        dynamicTable[i][j] = value;
	    }
	    return dynamicTable[i][j];
	}
	
	
	static int max(int num1, int num2) {
	    if (num1 >= num2) {
	        return num1;
	    } else {
	        return num2;
	    }
	}
	
	static void printTable(int dynamicTable[][], int items, int capacity) {
	    System.out.println("PRINT TABLE");
	    for (int iCount = 0; iCount <= items; iCount++) {
	        for (int jCount = 0; jCount <= capacity; jCount++) {
	            System.out.printf(" %3d",dynamicTable[iCount][jCount]);
	        }
	        System.out.println();
	    }
	    
	}
	static void populateVariables(Scanner file){
		int count = 0;
		int i = 0;
		while(file.hasNext()){
			if (count==0){
				capacity = file.nextInt();
				count++;
			}
			if (count==1){
				items = file.nextInt();
				values = new int[items];
				weights = new int[items];
				dynamicTable = new int [items+1][capacity+1];
				count++;
			}
			else{
				
				weights[i] = file.nextInt();
				values[i] = file.nextInt();
				
				count++;
				i++;
			}
		}
		file.close();
	}

}
