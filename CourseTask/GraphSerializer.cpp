#include "stdafx.h"
#include "GraphSerializer.h"
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

void GraphSerializer::serializeGraph(Graph* graph, string fileName) {
	ofstream file;
	file.open(fileName, ios::out | ios::trunc);

	for (int i = 0; i < graph->size; i++) {
		file << "Line " << i << "\n\n";
		for (int j = 0; j <= i; j++) {
			file << j << " : ";
			for (int k = 0; k < 4; k++) {
				file << (graph->links[i][j][k] ? 1 : 0) << " ";
			}
			if (i == graph->size - 1) {
				file << (graph->links[i][j][4] ? 1 : 0) << " ";
				file << (graph->links[i][j][5] ? 1 : 0) << " ";
			}
			file << "\n";
		}
		file << "\n\n\n";
	}

	file.close();
}


Graph* GraphSerializer::deserializeGraph(string fileName) {
	Graph* result = Graph::generateGraph();
	try {
		ifstream file;
		file.open(fileName, ios::in);
		string str = " ";
		char newStrChars[256];

		while (str != "") {
			file.getline(newStrChars, 256);
			str = newStrChars;
			istringstream iss(str);
			vector<string> words;
			copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(words));
			for (string i : words) {
				cout << i << "\n";
			}
		}
	}
	catch(...){
		cout << "exception caught\n";
	}
	return result;
}