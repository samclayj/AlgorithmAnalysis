//Java_Knapsack_BF.java

import java.util.*;
import java.lang.*;
import java.io.*;

public class Java_Knapsack_BF {

	static int[] weights;
	static int[] values;
	static int items;
	static int capacity;
	
	public static void main(String[] args) throws FileNotFoundException {

		Scanner infile = new Scanner(new File(args[0]));
		populateVariables(infile);
		

		int weights2[] = weights;
		int values2[] = values;
	      
		//start time
        long startTime = System.nanoTime();
        long stopTime = System.nanoTime();
        long overTime = stopTime - startTime;
        
        startTime = System.nanoTime();
        
        
	    String solution = knapsack(weights2, values2);
	    System.out.println(solution);        
        

        stopTime = System.nanoTime();
        //Stop time for the algorithm
        
        long time = stopTime - startTime - overTime;
        System.out.println("Total time is: " +(time/1000000));
        

	    
	}

	private static String knapsack(int[] weights2, int[] values2) {
	    String bestSet = "";
	    int bestValue = 0;

	    ArrayList<String> subsets = BRGC((int)weights2.length);
	    
	    //printVect(subsets);
	    
	    for (int i = 0; i < subsets.size(); i++) {
	        String set = subsets.get(i).toString();
	        int setValue = 0;
	        int setWeight = 0;
	        
	        boolean isFeasible = true;
	        
	        //cout << "Checking set: " << set << endl;
	        for (int j = 0; j < set.length() && isFeasible; j++) {
	            if (set.charAt(j) == '1') {
	                //Value at position j is in the subset.
	                setValue += values2[j];
	                setWeight += weights2[j];
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
	    
	    
	    System.out.println("Best Value: "+bestValue);
	    return bestSet;
	}

	static ArrayList<String> BRGC(int n) {
	    //Generates the binary reflected gray code of order n
	    //Input: positive integer n
	    //Output: A list of all bit strings of length n composing the gray code.
	    
	    ArrayList<String> L = new ArrayList();
	    
	    if (n == 1) {
	        //make list L containing bit strings 0 and 1 in this order.

	    	L.add("0");
	        L.add("1");
	        //printVect(L);
	    } else {
	        //Generate list L1 of bit strings of size n-1 by calling BRGC(n-1)
	        ArrayList<String> L1 = BRGC(n-1);
	        
	        //Copy list L1 to List L2 in reverse order.
	        ArrayList<String> L2 = new ArrayList();
	        for (int i = (int)L1.size() - 1; i >= 0; i--) {
	            L2.add(L1.get(i));
	        }
	        
	        //Add 0 in front of each bit string in List L1 and 1 in front of each
	        //bit string in L2.
	        for (int i = 0; i < L1.size(); i++) {
	            L1.set(i,append("0",L1.get(i)));
	            L2.set(i,append("1",L2.get(i)));
	        }
	        
	        //Append L2 to L1 to get list L.
	        for (int i = 0; i < L2.size(); i++) {
	            L1.add(L2.get(i));
	        }
	        
	        //L is the combination of L2 and L1.
	        L = L1;
	    }
	    
	    return L;
	}
	
	static void printVect(ArrayList<String> vect) {
	    System.out.println("PRINT LIST");
	    for (int i = 0; i < vect.size(); i++) {
	        System.out.println(vect.get(i));
	    }
	    
	    System.out.println();
	}
	
	static String append(String value, String str){
		value += str;
		return value;
		
	}
	
	static void populateVariables(Scanner file){
		int count = 0;
		int i = 0;
		while(file.hasNext()){
			if (count==0){
				capacity = file.nextInt();
				//System.out.println("Capacity is:"+capacity);
				count++;
			}
			if (count==1){
				items = file.nextInt();
				//System.out.println(items+" items");
				values = new int[items];
				weights = new int[items];
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


