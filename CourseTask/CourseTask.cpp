// CourseTask.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include "Graph.h"
#include "GraphDrawer.h"
#include "GraphAlgorithms.h"
#include "GraphSerializer.h"
#include <iostream>

using namespace std;

int main()
{
	Graph* graph = Graph::generateGraph();
	cout << graph->getSize() << "\n";
	GraphAlgorithms::findPath(graph, 0, 0, graph->getSize() - 1, graph->getSize() - 1);
	GraphSerializer::serializeGraph(graph, "savedGraph.txt");
	GraphDrawer::createDocument(graph, "result.html");
	return 0;
}