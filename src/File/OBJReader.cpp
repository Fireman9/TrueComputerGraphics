#include <fstream>
#include <sstream>
#include "OBJReader.h"

OBJReader::OBJReader(std::vector<std::string> &arguments) {
	std::string temp = "--source=";
	for (auto argument : arguments) {
		if (argument.find(temp) != std::string::npos) {
			mFilepath = argument.erase(0, temp.length());
			break;
		}
	}
}

OBJReader::OBJReader(std::string filepath) {
	mFilepath = filepath;
}

void OBJReader::read() {
	std::ifstream file(mFilepath);
	std::string temp;
	if (file.is_open()) {
		while (getline(file, temp)) {
			std::istringstream iss(temp);
			iss >> temp;
			if (!temp.empty() && temp == "v") {
				double x, y, z;
				iss >> x >> y >> z;
				mVertices.emplace_back(x, y, z);
			} else if (!temp.empty() && temp == "vn") {
				double x, y, z;
				iss >> x >> y >> z;
				mNormals.emplace_back(x, y, z);
			} else if (!temp.empty() && temp == "f") {
				std::string x, y, z;
				std::vector<size_t> verticeIndexes, normalIndexes;
				iss >> x >> y >> z;

				verticeIndexes.emplace_back(std::stoul(getSubstring(x, "/")));
				getSubstring(x, "/");
				normalIndexes.emplace_back(std::stoul(getSubstring(x, "/")));

				verticeIndexes.emplace_back(std::stoul(getSubstring(y, "/")));
				getSubstring(y, "/");
				normalIndexes.emplace_back(std::stoul(getSubstring(y, "/")));

				verticeIndexes.emplace_back(std::stoul(getSubstring(z, "/")));
				getSubstring(z, "/");
				normalIndexes.emplace_back(std::stoul(getSubstring(z, "/")));

				mTriangles.emplace_back(mVertices[verticeIndexes[0] - 1],
										mVertices[verticeIndexes[1] - 1],
										mVertices[verticeIndexes[2] - 1],
										mNormals[normalIndexes[0] - 1],
										mNormals[normalIndexes[1] - 1],
										mNormals[normalIndexes[2] - 1]);
			}
		}
		file.close();
	}
}

std::string OBJReader::getSubstring(std::string &string, std::string delimiter) {
	size_t pos = string.find(delimiter);
	std::string result;
	if (pos != std::string::npos) {
		result = string.substr(0, pos);
		string.erase(0, pos + delimiter.length());
	} else return string;
	return result;
}

void OBJReader::setFilepath(std::string filepath) {
	mFilepath = filepath;
}

std::vector<Point> OBJReader::getVertices() {
	return mVertices;
}

std::vector<Vector> OBJReader::getNormals() {
	return mNormals;
}

std::vector<Triangle> OBJReader::getTriangles() {
	return mTriangles;
}
