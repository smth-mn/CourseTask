#include "stdafx.h"
#include "Vertex.h"
#include <random>

using namespace std;

Vertex::Vertex()
{
	wave = -1;
	lastId++;
	id = lastId;
	color = new int[3];
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 255);
	color[0] = distribution(generator);
	color[1] = distribution(generator);
	color[2] = distribution(generator);

}

Vertex::~Vertex()
{
}

int* Vertex::getColor() {
	return color;
}

int Vertex::getId() {
	return id;
}

int Vertex::getWave(){
	return wave;
}

void Vertex::setWave(int newWave) {
	wave = newWave;
}
int Vertex::lastId = -1;