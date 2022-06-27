#include "PPMReader.h"

PPMReader::PPMReader(string filepath) : mFilepath(filepath) {}

void PPMReader::setFilepath(string filepath) {
	mFilepath = filepath;
}

vector<vector<Color>> PPMReader::read() {
	vector<vector<Color>> result;
	std::ifstream file(mFilepath);
	if (file.is_open()) {
		std::string temp;
		file >> temp; // P3

		int width, height;
		file >> width >> height;
		result.resize(height);
		for (auto &i : result) {
			i.resize(width);
		}

		file >> temp; // color max

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				int r, g, b;
				file >> r >> g >> b;
				result[i][j] = Color(r, g, b, 1);
			}
		}
		file.close();
	}
	return result;
}
