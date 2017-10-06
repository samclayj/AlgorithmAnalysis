import java.io.File;
import java.io.IOException;
import java.util.*;

public class Warshall_Java {

	public static void main(String[] args) throws IOException {	

		//String pathToDataFile = "/Users/SamJ/Desktop/AdjacencyMatrix.dat";

		String pathToDataFile = args[0];

		File inputFile = new File(pathToDataFile);

		Scanner fileReader = new Scanner(inputFile);

		int n, i, j;
		n = fileReader.nextInt();

		int [][]adjMatrix = new int[n][n];

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				adjMatrix[i][j] = fileReader.nextInt();
			}
		}

		printArray(adjMatrix, n);

		System.out.println();


		//---TIMING---//
		long startTime, stopTime, overTime = 0;
		startTime = System.nanoTime();
		stopTime = System.nanoTime();
		//overhead time for the program is calculated
		overTime = stopTime - startTime;
		long time;

		startTime = System.nanoTime();
		//CALL HORSPOOL
		warshall(adjMatrix, n);

		stopTime = System.nanoTime();
		time = stopTime - startTime - overTime;
		System.out.println("Total time: " + (time/1000000));


	}


	static void warshall(int R[][], int dimension) {

		for (int k = 0; k < dimension; k++) {
			for (int i = 0; i < dimension; i++) {
				for (int j = 0; j < dimension; j++) {
					//R[i][j] = R[i][j] | (R[i][k] && R[k][j]);
					if(R[i][j] == 1)
						R[i][j] = R[i][j];
					else if(R[i][k] == 1 && R[k][j] == 1)
						R[i][j] = 1;
				}
			}
		}

		printArray(R, dimension);
	}

	static void printArray(int numberArray[][], int dimension) {
		//Print the array
		int i, j;
		for(i = 0; i < dimension; i++) {
			for(j = 0; j < dimension; j++) {
				System.out.print(numberArray[i][j] + " ");
			}
			System.out.println();
		}
	}//printArray

}
