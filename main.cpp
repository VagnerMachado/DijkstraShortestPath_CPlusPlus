/*
 * main.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: Vagner Machado
 */
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class DijkstraSSS
{
public:
	int numNodes;   		 //done
	int sourceNode;			 //done in main
	int minNode;			 //done in main
	int currentNode;         //done in main
	int newCost;			 //done in main
	int ** costMatrix;  	 //done
	int * fatherArray;  	 //done
	int * markedArray;		 //done
	int * bestCostArray;	 //done
	DijkstraSSS(int numNodes);
	void loadCostMatrix(ifstream & infile);
	void setBestCostArray(int sourceNode);
	void setFatherArray();
	void setMarkedArray(int source);
	int findMinNode();
	int computeCost(int minNode, int currentNode);
	void debugPrint(ofstream & outfile);
	void printShortestPath (int currentNode, int sourceNOde, ofstream & ourfile);

	//auxiliary methods
	string printCostMatrix();
	string printFatherArray();
	string printMarkedArray();
	string printBestCostArray();
	bool nodesUnmarked();
	void printOutputHeader(ofstream & outfile);
};

int main (int argc, char ** argv)
{
	ifstream infile;
	infile.open(argv[1]);
	ofstream result;
	result.open(argv[2]);
	ofstream debug;
	debug.open(argv[3]);

	int nodes;
	infile >> nodes;
	DijkstraSSS sss(nodes);
	sss.printOutputHeader(result);
	sss.loadCostMatrix(infile);
	sss.sourceNode = 1;

	while (sss.sourceNode <= sss.numNodes)
	{
		sss.setBestCostArray(sss.sourceNode);
		sss.setFatherArray();
		sss.setMarkedArray(sss.sourceNode);

		while (sss.nodesUnmarked())
		{
			sss.minNode = sss.findMinNode();
			sss.markedArray[sss.minNode] = 1;
			sss.currentNode = 1;
			while(sss.currentNode <= sss.numNodes)
			{
				if (sss.markedArray[sss.currentNode] == 0)
				{
					sss.newCost = sss.computeCost(sss.minNode, sss.currentNode);
					if (sss.newCost < sss.bestCostArray[sss.currentNode])
					{
						sss.bestCostArray[sss.currentNode] = sss.newCost;
						sss.fatherArray[sss.currentNode] = sss.minNode;
					}
				}
				sss.debugPrint(debug);
				sss.currentNode++;
			}
		}
		sss.currentNode = 1;
		result << "\nSource node = " << sss.sourceNode << endl << endl;
		while(sss.currentNode <= sss.numNodes)
		{
			sss.printShortestPath(sss.currentNode, sss.sourceNode, result);
			sss.currentNode++;
		}
		result << "\n=============================================================================\n";
		sss.sourceNode++;
	}
	infile.close();
	result.close();
	debug.close();
	return 0;
}

DijkstraSSS::DijkstraSSS(int nodes)
{
	numNodes = nodes;

	//instantiate cost matrix
	costMatrix = new int * [numNodes + 1];
	for(int i = 1; i < (numNodes + 1); i++)
		costMatrix[i] = new int [numNodes+1];

	//initialize the cost matrix
	for (int i  = 1; i < numNodes + 1; i++)
		for (int j = 1; j < numNodes + 1; j++)
			costMatrix[i][j] = (i == j) ? 0 : 99999;

	fatherArray = new int[numNodes + 1];
	markedArray = new int[numNodes + 1];
	bestCostArray = new int[numNodes + 1];
	for (int i = 1; i < (numNodes + 1); i++)
	{
		fatherArray[i] = i;
		markedArray[i] = 0;
		bestCostArray[i] = 99999;
	}
}

void DijkstraSSS::loadCostMatrix(ifstream & infile)
{
	int row, col, cost;
	while (infile >> row)
	{
		infile >> col;
		infile >> cost;
		costMatrix[row][col] = cost;
	}
}

void DijkstraSSS::setBestCostArray(int sourceNode)
{
	for (int i = 1; i < (numNodes + 1); i++)
		bestCostArray[i] = costMatrix[sourceNode][i];
}

void DijkstraSSS::setFatherArray()
{
	for (int i = 1; i < (numNodes + 1); i++)
		fatherArray[i] = i;
}

void DijkstraSSS::setMarkedArray(int source)
{
	for (int i = 1; i < (numNodes + 1); i++)
		markedArray[i] = 0;
	markedArray[source] = 1;
}

int DijkstraSSS::findMinNode()
{
	int minCost = 99999;
	int minNode = 0;
	int index = 1;

	while(index <= numNodes)
	{
		if(markedArray[index] == 0 )
			if(bestCostArray[index] < minCost)
			{
				minCost = bestCostArray[index];
				minNode = index;
			}
		index++;
	}
	return minNode;
}

int DijkstraSSS::computeCost(int minNode, int currentNode)
{
	return (bestCostArray[minNode] + costMatrix[minNode][currentNode]);
}

void DijkstraSSS::debugPrint(ofstream & outfile)
{
	outfile << "\n\n";
	outfile << "    Source Node: " << sourceNode << endl;
	outfile << "   Father Array: " << printFatherArray();
	outfile << "\nBest Cost Array: " << printBestCostArray();
	outfile << "\n   Marked Array: " << printMarkedArray();
}

void DijkstraSSS::printShortestPath (int currentNode, int sourceNode, ofstream & outfile)
{

	int theCost = bestCostArray[currentNode];
	outfile << "The path from " << sourceNode << " to " << currentNode <<": ";
	outfile << currentNode << " <-- ";
	int place = currentNode;
	while(fatherArray[place] != place)
	{
		outfile << fatherArray[place] << " <-- ";
		place = fatherArray[place];
	}
	outfile << sourceNode << " : Cost = " << theCost;
	outfile << "\n";
}

string DijkstraSSS::printCostMatrix()
{
	stringstream ss;
	ss << "\t";
	for (int i  = 1; i < numNodes + 1; i++)
		ss << "(" << i << ")\t";
	ss << "\n";

	for (int i  = 1; i < numNodes + 1; i++)
	{
		ss << "(" << i << ")\t";
		for (int j = 1; j < numNodes + 1; j++)
		{
			ss << costMatrix[i][j] << "\t";
		}
		ss << "\n";
	}
	return ss.str();
}

string DijkstraSSS::printFatherArray()
{
	stringstream ss;
	for (int i = 1; i < (numNodes + 1); i++)
		ss  << fatherArray[i] << "\t";
	return ss.str();
}

string DijkstraSSS::printMarkedArray()
{
	stringstream ss;
	for (int i = 1; i < (numNodes + 1); i++)
		ss  << markedArray[i] << "\t";
	return ss.str();
}

string DijkstraSSS::printBestCostArray()
{
	stringstream ss;
	for (int i = 1; i < (numNodes + 1); i++)
		ss  << bestCostArray[i] << "\t";
	return ss.str();
}

bool DijkstraSSS::nodesUnmarked()
{
	int mark;
	for(int i = 1; i < numNodes + 1; i++)
	{
		mark = markedArray[i];
		if(mark == 0 )
			return 1;
	}
	return 0;
}

void DijkstraSSS::printOutputHeader(ofstream & result)
{
	result << "\n=============================================================================";
	result << "\nThere are " << numNodes << " nodes in the input graph. Below are all pairs of shortest paths:";
	result << "\n=============================================================================\n";
}

