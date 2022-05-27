#ifndef TRUECOMPUTERGRAPHICS_SRC_FILE_OBJREADER_H_
#define TRUECOMPUTERGRAPHICS_SRC_FILE_OBJREADER_H_

#include <string>
#include <vector>
#include "../Geometry/Shapes/Triangle.h"

class OBJReader {
public:
	OBJReader(std::vector<std::string> &arguments);

	OBJReader(std::string filepath);

	void read();

	static std::string getSubstring(std::string &string, std::string delimiter);

	void setFilepath(std::string filepath);

	std::vector<Point> getVertices();

	std::vector<Vector> getNormals();

	std::vector<Triangle> getTriangles();

private:
	std::string mFilepath;
	std::vector<Point> mVertices;
	std::vector<Vector> mNormals;
	std::vector<Triangle> mTriangles;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_FILE_OBJREADER_H_
