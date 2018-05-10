#pragma once
#include <vector>
#include "Vertex.h"

using namespace std;

class Graph
{
	friend class GraphSerializer;
	friend class GraphDrawer;
	friend class GraphAlgorithms;
public:
	~Graph();
	void addVertex(Vertex vertex, unsigned row, unsigned col);
	int getSize();
	void clearPath();
	
	static Graph* generateGraph();
	
private:
	vector<pair<int, int>> lastFoundPath;
	Graph(int _size);
	int size;
	vector<vector<Vertex>> vertices;
	vector<vector<vector<bool>>> links;	
};