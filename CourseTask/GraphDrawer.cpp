#include "stdafx.h"
#include "GraphDrawer.h"
#include "Vertex.h"
#include "GraphAlgorithms.h"
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

//draws graph in svg format puting it into file with given name in project directory

void GraphDrawer::createDocument(Graph* graph, string fileName)
{
	//declaring constants for html-page
	string title = "Hello graph";
	int svgWidth = 5000;
	int svgHeight = 5000;
	double edge = fmin( svgHeight / (3 / 2 * (graph->getSize() + 1)), svgWidth / (2 * graph->getSize()) ) ;

	//opening input-output filestream
	fstream file;
	file.open(fileName, ios::out | ios::in | ios::trunc);
	

	file << "<!DOCTYPE html>" << "\n";
	file << "<html>" << "\n";
	
	//creating "head" of document
	file << "<head>" << "\n";
	file << "\t" << "<title>" << title << "</title>" << "\n";
	file << "\t" << "<meta charset=\"utf-8\"> " << "\n";
	file << "</head>" << "\n";

	//creating "body" of document
	file << "<body>" << "\n";

	file << "\t" << "<svg height = \"" << svgHeight << "\" width = \"" << svgWidth << "\">" << "\n";
	double startX = svgWidth / 2;
	double startY = edge;
	double xMove = 0;
	double yMove = 0;
	int i = rand() % graph->getSize();
	vector<pair<int, int>> path = graph->lastFoundPath;
	for (int i = 0; i < (*graph).vertices.size(); i++) {
		for (int j = 0; j <= i; j++) {
			xMove = (sqrt(3) / 2 * edge)*(2 * j - i);
			drawHexagon(file, startX + xMove, startY + yMove, edge, (*graph).vertices[i][j].getColor(), (*graph).links[i][j], i, j);
			file << "<text x = \"" << startX + xMove << "\" y = \"" << startY + yMove << "\" fill = \"blue\"> " <<
				graph->vertices[i][j].getWave()<<" </text>" << "\n";
		}
		yMove = yMove + (edge * 3 / 2);
	}

	cout << path.size() << "\n";
	if (path.size() > 1) {
		for (int iter = 1; iter < path.size(); iter++) {
			auto pointOfPath = path[iter-1];
			auto otherPointOfPath = path[iter];
			double firstYMove = (edge * 3 / 2 * pointOfPath.first);
			double secondYMove = (edge * 3 / 2 * otherPointOfPath.first);
			double firstXMove = (sqrt(3) / 2 * edge)*(2 * pointOfPath.second - pointOfPath.first);
			double secondXMove = (sqrt(3) / 2 * edge)*(2 * otherPointOfPath.second - otherPointOfPath.first);

			file << "<line x1 = \"" << startX + firstXMove << "\" y1 = \"" << startY + firstYMove << "\" ";
			file << "x2 = \"" << startX + secondXMove << "\" y2 = \"" << startY + secondYMove << "\" ";
			file << "style = \"stroke:rgb(176,54,168);stroke-width:2\" />" << "\n";
		}
	}

	file << "\t" << "</svg>" << "\n";

	file << "</body>" << "\n";

	file << "</html>";
	file.close();
}

void GraphDrawer::drawHexagon(fstream& file, double centerX, double centerY, double edge, int* color, vector<bool> links, int row, int col) {
	
	if (col == 0) {
		//left upper line
		file << "\t\t" << "<line x1 = \"" << centerX << "\" y1 = \"" << centerY - edge << "\" ";
		file << "x2 =\"" << centerX - edge / 2 * sqrt(3) << "\" y2 = \"" << centerY - edge / 2 << "\" ";
		if (links[2]) {
			file << "style = \"stroke:rgb(0,255,0); stroke-width: 2\" />" << "\n";
		}
		else {
			file << "style = \"stroke:rgb(255,0,0); stroke-width: 2\" />" << "\n";
		}

		//left line
		file << "\t\t" << "<line x1 =\"" << centerX - edge / 2 * sqrt(3) << "\" y1 = \"" << centerY - edge / 2 << "\" ";
		file << "x2 =\"" << centerX - edge / 2 * sqrt(3) << "\" y2 = \"" << centerY + edge / 2 << "\" ";
		if (links[3]) {
			file << "style = \"stroke:rgb(0,255,0); stroke-width: 2\" />" << "\n";
		}
		else {
			file << "style = \"stroke:rgb(255,0,0); stroke-width: 2\" />" << "\n";
		}
	}

	//left bottom line
	file << "\t\t" << "<line x1 =\"" << centerX - edge / 2 * sqrt(3) << "\" y1 = \"" << centerY + edge / 2 << "\" ";
	file << "x2 =\"" << centerX << "\" y2 = \"" << centerY + edge << "\" ";
	if (links[4]) {
		file << "style = \"stroke:rgb(0,255,0); stroke-width: 2\" />" << "\n";
	}
	else {
		file << "style = \"stroke:rgb(255,0,0); stroke-width: 2\" />" << "\n";
	}

	//right bottom line
	file << "\t\t" << "<line x1 = \"" << centerX << "\" y1 = \"" << centerY + edge << "\" ";
	file << "x2 =\"" << centerX + edge / 2 * sqrt(3) << "\" y2 = \"" << centerY + edge / 2 << "\" ";
	if (links[5]) {
		file << "style = \"stroke:rgb(0,255,0); stroke-width: 2\" />" << "\n";
	}
	else {
		file << "style = \"stroke:rgb(255,0,0); stroke-width: 2\" />" << "\n";
	}

	//rigt line
	file << "\t\t" << "<line x1 =\"" << centerX + edge / 2 * sqrt(3) << "\" y1 = \"" << centerY + edge / 2 << "\" ";
	file << "x2 =\"" << centerX + edge / 2 * sqrt(3) << "\" y2 = \"" << centerY - edge / 2 << "\" ";
	if (links[0]) {
		file << "style = \"stroke:rgb(0,255,0); stroke-width: 2\" />" << "\n";
	}
	else {
		file << "style = \"stroke:rgb(255,0,0); stroke-width: 2\" />" << "\n";
	}

	if (row == col) {
		//right upper line
		file << "\t\t" << "<line x1 =\"" << centerX + edge / 2 * sqrt(3) << "\" y1 = \"" << centerY - edge / 2 << "\" ";
		file << "x2 =\"" << centerX << "\" y2 = \"" << centerY - edge << "\" ";
		if (links[1]) {
			file << "style = \"stroke:rgb(0,255,0); stroke-width: 2\" />" << "\n";
		}
		else {
			file << "style = \"stroke:rgb(255,0,0); stroke-width: 2\" />" << "\n";
		}
	}
}

