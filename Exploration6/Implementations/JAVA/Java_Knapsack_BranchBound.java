import java.util.*;
import java.io.*;

public class Java_Knapsack_BranchBound {
	static TreeNode root;
	static ArrayList<Item> items;
	static int capacity;

	public static void main(String args[]) throws FileNotFoundException {
		//Sort items in descending order by their given value-to-weight
	    //ratios.
	    
	    //First item gives best payoff per weight unit and last gives the
	    //worst payoff per weight unit.
	    
	    //A branch going to the left indicates the inclusion of the next item,
	    //a branch going to the right indicates the exclusion of the next item.
	    
	    //ub = v + (W - w)(nextI_V / nexti_W)
	    items = new ArrayList<Item>();

		Scanner infile = new Scanner(new File(args[0]));
		populateVariables(infile);
	    
	    for (int i = 0; i < items.size(); i++) {
	        items.get(i).WVRatio = (double)items.get(i).value/items.get(i).weight;
	        //cout << items.at(i).WVRatio << endl;
	    }
	    
	    BubbleSort(items);
	    
	    for (int i = 0; i < items.size(); i++) {
	        System.out.println(items.get(i).WVRatio);
	    }
	    
	    root = new TreeNode(0,0,0);
	    
	    //start time
        long startTime = System.nanoTime();
        long stopTime = System.nanoTime();
        long overTime = stopTime - startTime;
        
        startTime = System.nanoTime();
        
	    int max = branchBoundKnapsack(root, 0);
	    System.out.println("FINAL VALUE: " + max);
	    
	    stopTime = System.nanoTime();
        //Stop time for the algorithm
        
        long time = stopTime - startTime - overTime;
        System.out.println("Total time is: " +(time/1000000));
	  
	}
	
	static int branchBoundKnapsack(TreeNode currentNode, int nodeLevel) {
	    int value = 0;
	    
	    //ub = v + (W-w)(vi+1/wi+1)
	    int valueIncludeI = (currentNode.totalValue+items.get(nodeLevel).value);
	    int weightIncludeI = (currentNode.totalWeight+items.get(nodeLevel).weight);
	    
	    if (nodeLevel+1 >= items.size()) {
	        //Base case
	        //Current Node is a leaf.
	        int maxValue;
	        if (valueIncludeI > currentNode.totalValue && (weightIncludeI <= capacity)) {
	            maxValue = valueIncludeI;
	        } else {
	            maxValue = currentNode.totalValue;
	        }
	        
	        //cout << "MAX VALUE: " << maxValue << endl;
	        return maxValue;
	    } else {
	        //Current node is not a leaf.
	        int upperBoundLeft = (int)(valueIncludeI + (capacity - weightIncludeI)*(items.get(nodeLevel+1).WVRatio));
	        int upperBoundRight = (int)(currentNode.totalValue + (capacity - currentNode.totalWeight)*(items.get(nodeLevel+1).WVRatio));
	        
	        //cout << upperBoundLeft << " " << upperBoundRight << endl;
	        
	        TreeNode leftChild = new TreeNode(upperBoundLeft, weightIncludeI, valueIncludeI);
	        TreeNode rightChild = new TreeNode(upperBoundRight, currentNode.totalWeight, currentNode.totalValue);
	        
	        currentNode.leftChild = leftChild;
	        currentNode.rightChild = rightChild;
	        
	        
	        //----Select Next Path----//
	        int leftValue = -1;
	        int rightValue = -1;
	        if ((upperBoundLeft > upperBoundRight) && weightIncludeI <= capacity) {
	            leftValue = branchBoundKnapsack(currentNode.leftChild, nodeLevel + 1);
	            //Make sure it was the best
	            if (leftValue < upperBoundRight) {
	                rightValue = branchBoundKnapsack(currentNode.rightChild, nodeLevel + 1);
	            }
	        } else {
	            rightValue = branchBoundKnapsack(currentNode.rightChild, nodeLevel + 1);
	            //Make sure it was the best
	            if (rightValue < upperBoundLeft && weightIncludeI <= capacity) {
	                leftValue = branchBoundKnapsack(currentNode.leftChild, nodeLevel + 1);
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

	static void BubbleSort(ArrayList<Item> vect) {
	    int i, j; 
	    boolean flag = true;    // set flag to 1 to start first pass
	    Item temp;             // holding variable
	    for(i = 1; i <= vect.size() && flag; i++) {
	        flag = false;
	        for (j=0; j < (vect.size() - 1); j++)
	        {
	            if (vect.get(j+1).WVRatio > vect.get(j).WVRatio) {
	                temp = vect.get(j);
	                vect.set(j, vect.get(j+1));
	                vect.set(j+1, temp);
	                flag = true;               // indicates that a swap occurred.
	            }
	        }
	    }
	    return;    //arrays are passed to functions by address; nothing is returned
	}

	static void populateVariables(Scanner file){
		int count = 0;
		while(file.hasNext()){
			if (count==0){
				capacity = file.nextInt();
				//System.out.println("Capacity is:"+capacity);
				count++;
			}
			if (count==1){
				int numItems = file.nextInt();
				count++;
			}
			else{
				
				Item newItem = new Item(file.nextInt(), file.nextInt());
				items.add(newItem);
				count++;
			}
		}
		file.close();
	}

}

class TreeNode {
	int upperBound;
    int totalWeight;
    int totalValue;
    TreeNode leftChild;
    TreeNode rightChild;
    
    TreeNode() {
        upperBound = 0;
        totalWeight = 0;
        totalValue = 0;
        leftChild = null;
        rightChild = null;
    }
    
    TreeNode(int ub, int tw, int tv) {
        upperBound = ub;
        totalWeight = tw;
        totalValue = tv;
        leftChild = null;
        rightChild = null;
    }
}

class Item {
	int weight;
    int value;
    double WVRatio;
    
    Item(int w, int v) {
    	weight = w;
    	value = v;
    }
}
