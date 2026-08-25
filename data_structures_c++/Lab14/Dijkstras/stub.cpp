/****************************************************************
* 
* 
* Author: Zaelfenn Sandow
* 
* Date created: June 1st, 2024
* 
* Project Purpose: Create an algorithm that finds the shortest distance
* between any two locations. These locations are found in a file 
* which was given by the professor. The locations are arranged into
* a graph data structure.
* 
* 
****************************************************************/


#include "Graph.h"
#include <fstream>
using std::ifstream;
using std::ios;
#include <string>
using std::string;
using std::stoi;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include<iomanip>
using std::setw;
#include <stdlib.h>
#include <Windows.h>
Graph<string,string> pullFile();

void DijkstrasAlgortithm(string start, Graph<string,string> ref, int* distance, int* pred);

void output(string data) {
	cout << data << endl;
}

int main()
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 8);

	//Graph that holds the nodes
	Graph<string, string> oregonRoads(pullFile());

	//array that holds distance from start to end
	int* dist = new int[oregonRoads.getCount()];

	//array that holds index of previous location
	int* pred = new int[oregonRoads.getCount()];
	
	//useful variables for holding user information
	int endIndex, time_traveled;;
	bool loopQuestion = true, loopAnswer;
	char buffer[40];
	string start, end, location;
	bool found;
	stack<string> location_names;
	
	while (loopQuestion) {
		//reset the arrays to hold only 0s
		for (int i = 0; i < oregonRoads.getCount(); ++i) {
			dist[i] = -1;
			pred[i] = -1;
		}

		
		cout << "Welcome to Oregon!" << endl;
		cout << "Please enter your starting location: ";
	
		found = false;

		//loop to make sure user input is valid
		while (!found) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(buffer, 40);
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			start = buffer;

			for (int i = 0; i < oregonRoads.getCount() && !found; ++i) {
				if (start == oregonRoads[i].getData())
					found = true;
			}
			if (!found) {
				cout << "Invalid location entered. Please try again." << endl;
			}
		}

		//find the path from the user entered node to the every other node
		DijkstrasAlgortithm(start, oregonRoads, dist, pred);

		cout << "\nPlease enter the ending destination: ";
		found = false;

		//loop to make sure user input is valid
		while (!found) {
			cin.getline(buffer, 40);
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			end = buffer;

			for (int i = 0; i < oregonRoads.getCount() && !found; ++i) {
				if (end == oregonRoads[i].getData()) {
					found = true;
					endIndex = i;
				}
			}
			if (!found) {
				cout << "Invalid location entered. Please try again." << endl;
			}
		}

		//output data
		cout << "Distance from " << start << " to " << end << " is: " << dist[endIndex] << " miles" << endl;
		
		time_traveled = 0;
		int index = endIndex, tempIndex;
		while (pred[index] != -1) {
			found = false;
			for (typename list<Edge<string, string>>::iterator i = oregonRoads[index].getEdges().begin(); i != oregonRoads[index].getEdges().end() && !found; ++i) {
				//compare the addresses
				if (&i->getDestination() == &oregonRoads[pred[index]]) {
					found = true;
					//I-5 has a speed limit of 65 mph
					if (i->getData() == "I-5") {
						time_traveled += i->getWeight() * 65 / 60;
					}

					//every other road has a speed limit of 55 mph
					else {
						time_traveled += i->getWeight() * 55 / 60;
					}
					location_names.push(oregonRoads[pred[index]].getData());
					tempIndex = pred[index];
				}
			}
			index = tempIndex;
		}

		cout << "Taking the route from ";
		while (!location_names.empty()) {
			location = location_names.top();
			location_names.pop();
			SetConsoleTextAttribute(hConsole, 13);
			cout << location;
			SetConsoleTextAttribute(hConsole, 8);
			cout << " to ";
		}
		cout << end << ", it will take " << time_traveled << " minutes to get there." << endl;

		//loop to either find another distance or to end the program
		loopAnswer = false;
		while (!loopAnswer) {
			cout << "Would you like to go again?\n" <<
				"1. yes\n" <<
				"2. no" << endl;

			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());

			int answer;
			cin >> answer;
			switch (answer) {
			case 1:
				system("cls");
				loopAnswer = true;
				break;
			case 2:
				loopQuestion = false;
				loopAnswer = true;
				break;

			default:
				cout << "Please enter a valid response." << endl;
			}

		}
		
	}

	//no memory leaks !
	delete[] dist;
	delete[] pred;
	return 0;
}


/************************************
* 
* Function Name: pullFile
* 
* Function Purpose: pulls from a file
* named "assign13.txt". Adds all of the 
* data in the file to a graph data structure.
* Returns the graph data structure by value.
* 
* 
************************************/
Graph<string, string> pullFile()
{
	//create a graph to return
	Graph<string, string> retVal;

	//create a file to read from
	ifstream roads("assign13.txt");

	//check to see if the file is open
	if (roads.is_open()) {

		//useful variables for reading from the file
		char buffer[130];
		char *start, *end, *path;
		int weight;

		while (!roads.eof()) {
			//read the line	
			roads.getline(buffer, 130);

			//grab the starting string
			start = strtok(buffer, ",");
			
			//try to find the vertex in the graph
			try {
				retVal.findVertex(start);
			}
			//if the vertex is not found, create it.
			catch (Exception& e){
				e.getMsg();
				retVal.InsertVertex(start);
			}
			
			//grab the destination string
			end = strtok(NULL, ",");

			//try to find the vertex in the graph
			try {
				retVal.findVertex(end);
			}
			//if it is not found, create it
			catch (Exception& e) {
				e.getMsg();
				retVal.InsertVertex(end);
			}
			//find the edge data
			path = strtok(NULL, ",");
			//find the edge weight
			weight = stoi(strtok(NULL," "));

			//add an edge from start to end, and end to start.
			retVal.InsertArc(start, end, path, weight);
			retVal.InsertArc(end, start, path, weight);
		}

		//close the file
		roads.close();
	}

	//return the new graph
	return retVal;
}


/***************************************
* 
* 
* Function Name: DijkstrasAlgorithm
* 
* Function Purpose: Pass in a string, 
* a string/string graph, and 2 integer 
* pointers. The string will be used to 
* find a starting location in the graph. 
* The integer pointers will hold the necessary
* data to draw a path between the starting 
* position and every connected node in the graph.
* 
* 
****************************************/
void DijkstrasAlgortithm(string start, Graph<string, string> ref, int* distance, int* pred)
{
	//the current index is the index of the starting location
	int cur_index = ref.findVertex(start).getIndex();
	//the distance from the starting location is 0. the predecessor does not exist and is therefore -1.
	distance[cur_index] = 0;

	//useful variables while looping
	bool loop = true;
	bool proc;
	int total_proc = 0;

	//define a way to move through the connecting paths of the vertices
	list<Edge<string, string>> edges;
	typename list<Edge<string, string>>::iterator i;

	//loop once for every node
	while (loop) {
		
		edges = ref[cur_index].getEdges();
		proc = false;
		
		//traverse all the edges
		for (i = edges.begin(); i != edges.end(); ++i) {
			//if the node that is being looked at has been processed, skip it
			if (!i->getDestination().getProcessed()) {
				//if the distance between this node and the other node is less than the distance at the destination node
				//or if the destination node has not yet been seen
				if (distance[cur_index] + i->getWeight() < distance[i->getDestination().getIndex()] || pred[i->getDestination().getIndex()] == -1) {
					//set the distance to be the lesser of the two values
					distance[i->getDestination().getIndex()] = distance[cur_index] + i->getWeight();

					//change the index of the predecessor 
					pred[i->getDestination().getIndex()] = cur_index;
				}
			}
		}

		//process the current node
		ref[cur_index].setProcessed();
		//add one to the total processed
		total_proc += 1;

		//if every node has been processed, end the loop
		if (total_proc == ref.getCount() - 1)
			loop = false;

		//keep a temporary value to hold the old index
		int temp_index = cur_index;
		for (int i = 0; i < ref.getCount(); ++i) {
			//check to make sure the current vertex has not been processed and has been seen
			if (!ref[i].getProcessed() && pred[i] != -1) {
				//check if the current node is processed or if the distance at the looked at node has a lower distance than the current node
				if (ref[cur_index].getProcessed() || distance[i] < distance[cur_index]) {
					//change the current index
					cur_index = i;
				}
			}
		}

		//if the index hasnt changed, all possible nodes have been processed. 
		if (cur_index == temp_index)
			loop = false;
	}
}