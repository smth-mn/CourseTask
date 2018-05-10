#pragma once
class Vertex
{
public:
	Vertex();
	~Vertex();

	int* getColor();
	int getId();
	int getWave();
	void setWave(int newWave);

private:
	int id;
	int wave;
	int* color;
	static int lastId;
};