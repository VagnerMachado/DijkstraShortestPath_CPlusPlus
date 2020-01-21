# DijkstraShortestPath_CPlusPlus
Dijkstra's shortest path coded in C++

<pre>

<b>Project 8: All paths shortest paths, by using Dijkstra’s algorithm for the Single-Source-Shortest Paths problem 
N times.
Problem Statement: Given a directed graph, G = <N, E>, and the source node, S, in G, the task is find the shortest paths from S to every other nodes in G, using the Dijkstra’s algorithm.</b>

*** Please note that in your program, the source node will be 1, 2, 3, …, N.  // i.e., Your program will produce *all pairs* shortest paths. 
 
*** -4 pts for hard coded file names!!!!!!

********************************
Language: C++ 
Due date (soft copy): 4/28/2019 Sunday before Midnight
	Early submission +1 deadline: 4/24/2019 Wednesday before Midnight
	-1 pt due: 4/29/2019 Monday before midnight
	After 4/29/2019, -12 pts for all students who did not submit soft copy 

Due Date (hard copy):   4/30/2019 Tuesday in class, 
-1 pt for late hard copy submission after Thursday 3/21/2019 (in class).
All projects without hard copy after 4/30/2019will receive 0 pts even you have submit soft copy on time and even if it works.

**************************************
I. inFile (argv [1]): a directed graph, represented by a list of edges with costs, {<ni, nj, c>}  
// You may assume that nodes’ Id is from 1 to N.  

The format of the input file is as follows:

The first text line is the number of nodes, N, follows by a list of triplets, <ni, nj, cost>
	For example:
		5		// there are 5 nodes in the graph 
		1  5 10 	// an  edge <1, 5, 10> 
    		2  3  5 		// an edge <2, 3, 5> 
     		1  2  20 	//an edge <1, 2, 20> 
		3  5  2 		// an edge <3, 5, 2> 
    		:	
		:
**************************************
II. Outputs: 
a) outFile1 (argv [2]) :  for the result of all pairs shortest paths. The format is given below:
	
// If there are 7 nodes in the graph G. Then your output will be as follows:

==============================
There are 7 nodes in the input graph. Below are the all pairs of shortest paths:
 ===============================
Source node = 1 

The path from 1 to 1 :  1 <- 1 : cost = 0 
The path from 1 to 2 :  2 <- … <- 1: cost = whatever
The path from 1 to 3 :  3 <- … <- 1: cost = whatever
:
:
The path from 1 to 7 :  7 <- … <- 1: cost = whatever

===============================
The source node = 2 

The path from 2 to 1 :  1 <- … <- 2 : cost = whatever
The path from 2 to 2 :  2 <-  2: cost = 0 
The path from 2 to 3 :  3 <- … <- 2: cost = whatever
:
:
The path from 2 to 7 :  7 <- … <- 2: cost = whatever
	:
:
===============================
The source node = 7 

The path from 7 to 1 :  1 <- … <- 7 : cost = whatever
The path from 7 to 2 :  2 <- … <- 7 : cost = whatever
The path from 7 to 3 :  3 <- … <- 7 : cost = whatever
:
:
The path from 2 to 7 :  7 <- … <- 7: cost = 0

	b) outFile2 (argv [3]): For all debugging outputs. You do NOT need to print outFile2 for your hard copies.

**************************************
III. Data structure:
	1) A DijktraSSS class
	
	- numNodes (int) //number of nodes in G
	- sourceNode (int)
	- minNode (int)
	- currentNode (int)
	- newCost (int)
	- costMatrix (int **)
// a 2-D cost matrix (integer array), size of N+1 X N+1, should be dynamically allocated.
		// Initially, costMatrix[i][i] set to zero and all others set to infinity, 99999
		// Note: 0 is not used for node Id.

	- fatherAry (int*) // a 1-D integer array, size of N+1, should be dynamically allocated.
		// initially set to itself, i.e., father[i] = i

 	- markedAry(int*) // 1-D integer array, size of N+1, should be dynamically allocated.
		// initially set to 0 (not marked)
	- bestCostAry (int*) // a 1-D integer array, size of N+1, should be dynamically allocated.
		// initially set to 9999 (infinity)

   Methods:
	- loadCostMatrix // read from input file and fill the costMatrix, 
	- setBestCostAry (sourceNode) // copy the row of source node from costMatrix, 
- setFatherAry (sourceNode) // set all to itself
- setMarkedAry ( ) // set all to 0
- int findMinNode() // find an *unmarked* node with  minimum cost from bestCostAry
		// Algorithm is given below
	- int computeCost (minNode, currentNode) 
// computes the best cost for currentNode, which is
// bestCostAry [minNode] plus the edge cost from minNode to currentNode.
// return the computed best cost for currentNode

	- debugPrint (outFile2) // This method 
// Prints sourceNode to outFile2 (with proper heading, ie., the sourceNode is: )
// Prints fatherAry to outFile2 (with proper heading)
// Prints bestCostAry to outFile2 (with proper heading)
// Prints markedAry to outFile2 (with proper heading)

	- printShortestPath (currentNode, sourceNode, outFile1) 
// trace from currentNode back to sourceNode (via fatherAry), 
// print to outFile1, the shortest path from
 // currentNode to sourceNode with the total cost, using the format given in the above
	// You should know how to do this method.

**************************************	
V.  main(…)
**************************************
// A lot of debugging statements are embedded in the algorithm for debugging your program!

step 0:   open inFile, outFile1, outFIle2
numNodes <- get from inFile
Allocate and initialize all members  in the DijkstraSSS class accordingly
	
step 1:   loadMatrix (inFile) // make sure costMatrix[i][i] set to 0
	 sourceNode <- 1

step 2:  setBestCostAry (sourceNode)
setFatherAry ()
setMarkedAry ( )

step 3: minNode <- findMinNode() 
           markedAry[minNode] <- 1
call debugPrint () 
     
step 4: // expanding the minNode
          currenNode <- 1



step 5: if markedAry[currentNode] == 0
           		newCost <- computeCost(minNode, currentNode)
 if newCost < bestCostAry [currentNode]
bestCostAry[currentNode] <-  newCost
  		 fatherAry[currentNode] <- minNode   
  	            	 call debugPrint (outFile2)

Step 6: currenNode ++

Step 7: repeat step 5 to step 6 while currentNode <= numNodes

step 8: repeat step 3 to step 8 until all nodes are marked

	//  begin printing the paths
step 9: currentNode <- 1

step 10:  printShortestPath (currentNode, sourceNode, outFile1)

step 11:  currentNode ++

step 12: repeat 10 and step 11 while currentNode <= numNodes

step 13: sourceNode ++

step 14:  repeat step 2 to step 13 while sourceNode <= numNodes

step 15: close all files

**************************************	
V.  int findMinNode ()
**************************************
Step 0: minCost <- 99999
minNode <- 0

Step 1: index <- 1

Step 2: if markedAry[index] == 0 // unmarked
	     if bestCostAry[index] < minCost
	           minCost <- bestCostAry[index]
	           minNode <-index
step3: index++

step 4: repeat step 2 – step 3 while index <= numNodes

step 5: return minNode



<pre>
