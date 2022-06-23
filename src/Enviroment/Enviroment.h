#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <memory>
#include "../File/PPMWriter.h"
#include "../File/OBJReader.h"
#include "../Geometry/Shapes/Triangle.h"
#include "../Render/Scene.h"
#include "../Render/Screen.h"
#include "../Geometry/Point.h"
#include "../Tree/Node.h"

using std::vector;
using std::endl;
using std::string;

class Enviroment {
public:
	Enviroment(vector<string> arg);

	Scene prepare();
	void writeTofile(Scene scene);
	OBJReader readTriangles();
	vector<Triangle> transformTriangles(Matrix4x4 matrix, OBJReader objReader, Point start);

	void setArg(vector<string> arg);
	void setInput(string inp);
	void setOut(string out);
	void setHeight(int px);
	void setWidth(int px);
	void setIsTesting(bool b);

	string input();
	string output();
	int height();
	int width();
	bool isTesting();

private:
	bool isTestImg;
	string inputfileName;
	string outPutFileName;
	int heightS;
	int widthS;
	vector<string> arg;
	vector<Triangle> triangles;
	string findKey(string ex, bool* find);
	clock_t tStart;
};

#endif //ENVIROMENT_H