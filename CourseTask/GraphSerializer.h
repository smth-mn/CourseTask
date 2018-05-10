#pragma once
#include "Graph.h"
#include <string>

class GraphSerializer
{
public:
	static void serializeGraph(Graph* graph, string fileName);
	static Graph* deserializeGraph(string fileName);
};

