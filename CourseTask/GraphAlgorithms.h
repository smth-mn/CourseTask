#pragma once

#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

class GraphAlgorithms
{
public:
	static void findPath(Graph* graph, int row1, int col1, int row2, int col2);
};

