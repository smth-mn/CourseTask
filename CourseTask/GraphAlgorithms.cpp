#include "stdafx.h"
#include "GraphAlgorithms.h"
#include <set>

void GraphAlgorithms::findPath(Graph* graph, int row1, int col1, int row2, int col2) {
	vector<pair<int, int>> result;
	graph->vertices[row1][col1].setWave(0);
	int currentWave = 1;
	set<pair<int, int>> lastWaveIndices;
	lastWaveIndices.insert(make_pair(row1, col1));
	set<pair<int, int>> nextWaveIndices;
	while (graph->vertices[row2][col2].getWave() < 0 && !lastWaveIndices.empty()) {
		for (auto i = lastWaveIndices.begin(); i != lastWaveIndices.end(); i++) {
			pair<int, int> currentIndices = *i;
			for (int j = 0; j < 6; j++) {
				if (graph->links[currentIndices.first][currentIndices.second][j]) {
					switch (j) {
					case 0:
						//(graph->vertices[currentIndices.first][currentIndices.second + 1].getWave() > currentWave + 1) || 
						if ((graph->vertices[currentIndices.first][currentIndices.second + 1].getWave() == -1)) {
							nextWaveIndices.insert(make_pair(currentIndices.first, currentIndices.second + 1));
							graph->vertices[currentIndices.first][currentIndices.second + 1].setWave(currentWave);
						}
						break;
					case 1:
						//(graph->vertices[currentIndices.first - 1][currentIndices.second].getWave() > currentWave + 1) || 
						if ((graph->vertices[currentIndices.first - 1][currentIndices.second].getWave() == -1)) {
							nextWaveIndices.insert(make_pair(currentIndices.first - 1, currentIndices.second));
							graph->vertices[currentIndices.first - 1][currentIndices.second].setWave(currentWave);
						}
						break;
					case 2:
						//(graph->vertices[currentIndices.first - 1][currentIndices.second - 1].getWave() > currentWave + 1) || 
						if ((graph->vertices[currentIndices.first - 1][currentIndices.second - 1].getWave() == -1)) {
							nextWaveIndices.insert(make_pair(currentIndices.first - 1, currentIndices.second - 1));
							graph->vertices[currentIndices.first - 1][currentIndices.second - 1].setWave(currentWave);
						}
						break;
					case 3:
						//(graph->vertices[currentIndices.first][currentIndices.second - 1].getWave() > currentWave + 1) ||
						if ((graph->vertices[currentIndices.first][currentIndices.second - 1].getWave() == -1)) {
							nextWaveIndices.insert(make_pair(currentIndices.first, currentIndices.second - 1));
							graph->vertices[currentIndices.first][currentIndices.second - 1].setWave(currentWave);
						}
						break;
					case 4:
						//(graph->vertices[currentIndices.first + 1][currentIndices.second].getWave() > currentWave + 1) || 
						if ((graph->vertices[currentIndices.first + 1][currentIndices.second].getWave() == -1)) {
							nextWaveIndices.insert(make_pair(currentIndices.first + 1, currentIndices.second));
							graph->vertices[currentIndices.first + 1][currentIndices.second].setWave(currentWave);
						}
						break;
					case 5:
						//(graph->vertices[currentIndices.first + 1][currentIndices.second + 1].getWave() > currentWave + 1) || 
						if ((graph->vertices[currentIndices.first + 1][currentIndices.second + 1].getWave() == -1)) {
							nextWaveIndices.insert(make_pair(currentIndices.first + 1, currentIndices.second + 1));
							graph->vertices[currentIndices.first + 1][currentIndices.second + 1].setWave(currentWave);
						}
						break;
					}
				}
			}
		}
		currentWave += 1;
		lastWaveIndices = nextWaveIndices;
		nextWaveIndices = *(new set<pair<int, int>>);
	}

	if(graph->vertices[row2][col2].getWave() != -1){
		result.push_back(make_pair(row2, col2));
		pair<int, int> currentCellIndicies = make_pair(row2, col2);
		while (find(result.begin(), result.end(), make_pair(row1, col1)) == result.end()) {
			for (int i = 0; i < 6; i++) {
				if (graph->links[currentCellIndicies.first][currentCellIndicies.second][i]) {
					switch (i) {
					case 0:
						if (currentCellIndicies.second != currentCellIndicies.first) {
							if (graph->vertices[currentCellIndicies.first][currentCellIndicies.second + 1].getWave() == graph->vertices[currentCellIndicies.first][currentCellIndicies.second].getWave() - 1) {
								result.push_back(make_pair(currentCellIndicies.first, currentCellIndicies.second + 1));
								currentCellIndicies = make_pair(currentCellIndicies.first, currentCellIndicies.second + 1);
							}
						}
						break;
					case 1:
						if (currentCellIndicies.second != currentCellIndicies.first) {
							if (graph->vertices[currentCellIndicies.first - 1][currentCellIndicies.second].getWave() == graph->vertices[currentCellIndicies.first][currentCellIndicies.second].getWave() - 1) {
								result.push_back(make_pair(currentCellIndicies.first - 1, currentCellIndicies.second));
								currentCellIndicies = make_pair(currentCellIndicies.first - 1, currentCellIndicies.second);
							}
						}
						break;
					case 2:
						if (currentCellIndicies.second > 0) {
							if (graph->vertices[currentCellIndicies.first - 1][currentCellIndicies.second - 1].getWave() == graph->vertices[currentCellIndicies.first][currentCellIndicies.second].getWave() - 1) {
								result.push_back(make_pair(currentCellIndicies.first - 1, currentCellIndicies.second - 1));
								currentCellIndicies = make_pair(currentCellIndicies.first - 1, currentCellIndicies.second - 1);
							}
						}
						break;
					case 3:
						if (currentCellIndicies.second > 0) {
							if (graph->vertices[currentCellIndicies.first][currentCellIndicies.second - 1].getWave() == graph->vertices[currentCellIndicies.first][currentCellIndicies.second].getWave() - 1) {
								result.push_back(make_pair(currentCellIndicies.first, currentCellIndicies.second - 1));
								currentCellIndicies = make_pair(currentCellIndicies.first, currentCellIndicies.second - 1);
							}
						}
						break;
					case 4:
						if (currentCellIndicies.first < graph->getSize() - 1) {
							if (graph->vertices[currentCellIndicies.first + 1][currentCellIndicies.second].getWave() == graph->vertices[currentCellIndicies.first][currentCellIndicies.second].getWave() - 1) {
								result.push_back(make_pair(currentCellIndicies.first + 1, currentCellIndicies.second));
								currentCellIndicies = make_pair(currentCellIndicies.first + 1, currentCellIndicies.second);
							}
						}
						break;
					case 5:
						if (currentCellIndicies.first < graph->getSize() - 1) {
							if (graph->vertices[currentCellIndicies.first + 1][currentCellIndicies.second + 1].getWave() == graph->vertices[currentCellIndicies.first][currentCellIndicies.second].getWave() - 1) {
								result.push_back(make_pair(currentCellIndicies.first + 1, currentCellIndicies.second + 1));
								currentCellIndicies = make_pair(currentCellIndicies.first + 1, currentCellIndicies.second + 1);
							}
						}
						break;
					}
				}
			}
		}
		graph->lastFoundPath = result;
	}
}
