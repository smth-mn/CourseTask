#pragma once

#include "Graph.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class GraphDrawer
{
public:
	static void createDocument(Graph* graph, std::string fileName);

private:
	static void drawHexagon(fstream& file, double centerX, double centerY, double edge, int* color, vector<bool> links, int row, int col);
};