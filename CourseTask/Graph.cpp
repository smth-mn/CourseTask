#include "stdafx.h"
#include "Graph.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Graph::Graph(int _size):size(_size){
	vector<vector<Vertex>>* temp = new vector<vector<Vertex>>(size);
	vertices = *temp;
	vector<Vertex>* temp1;
	for (int i = 0; i < size; i++) {
		temp1 = new vector<Vertex>(i + 1);
		vertices[i] = *temp1;
	}

	vector<vector<vector<bool>>>* temp2 = new vector<vector<vector<bool>>>(size);
	links = *temp2;
	for (int i = 0; i < size; i++){
		vector<vector<bool>>* temp3ptr = new vector<vector<bool>>(i + 1);
		vector<vector<bool>> temp3 = *temp3ptr;
		for (int j = 0; j <= i; j++) {
			vector<bool>* temp4 = new vector<bool>(6);
			temp3[j] = *temp4;
		}
		links[i] = temp3;
	}
	lastFoundPath = *(new vector<pair<int, int>>(0));
}


Graph::~Graph()
{
}

int Graph::getSize() {
	return size;
}

/*
Generates random hexagonal mesh
edges beween vertices can have two states only(passable or not)
relations between edge and its neighbours are written in bool array in "links" vector
if to assume that indexes of directions of each cell look like this:
	2	1	
	 / \
   3|   |0
	 \ /
	4	5
*/

Graph* Graph::generateGraph() {

	srand(time(0));

	//generating vertices

	Graph* graph = new Graph(rand() % 91 + 10);
	for (int i = 0; i < graph->getSize(); i++) {
		for (int j = 0; j <= i; j++) {
			(*graph).vertices[i][j] = *(new Vertex());
		}
	}
	
	//generating edges
	for(int i = 0; i < graph->getSize(); i++) {
		for (int j = 0; j <= i; j++) {
			//generating edges in 2 and 3 directions
			if (j == 0) {
				graph->links[i][j][2] = 0;
				graph->links[i][j][3] = 0;
			}
			else {
				graph->links[i][j][2] = graph->links[i-1][j-1][5];
				graph->links[i][j][3] = graph->links[i][j-1][0];
			}

			//generating edges in 0 and 1 directions
			if (j == i) {
				graph->links[i][j][0] = 0;
				graph->links[i][j][1] = 0;
			}
			else {
				graph->links[i][j][1] = graph->links[i-1][j][4];
				if (rand() % 2 == 1) {
					graph->links[i][j][0] = 1;
				}
				else {
					graph->links[i][j][0] = 0;
				}
			}

			//generating edges in 4 and 5 directions
			if (i == graph->getSize() - 1) {
				graph->links[i][j][4] = 0;
				graph->links[i][j][5] = 0;
			}
			else {
				if (rand() % 2 == 1) {
					graph->links[i][j][4] = 1;
				}
				else {
					graph->links[i][j][4] = 0;
				}
				if (rand() % 2 == 1) {
					graph->links[i][j][5] = 1;
				}
				else {
					graph->links[i][j][5] = 0;
				}
			}
		}
	}
	return graph;
}

void Graph::addVertex(Vertex vertex, unsigned rowIndex, unsigned colIndex) {
	if (rowIndex > vertices.size() || colIndex >= rowIndex) {
		cout << "Invalid position"<< "\n";
	}
	else {
		vertices[rowIndex][colIndex] = vertex;
	}
}

void Graph::clearPath() {
	lastFoundPath = *(new vector<pair<int, int>>(0));
}