#ifndef TRUECOMPUTERGRAPHICS_SRC_FILE_PPMREADER_H_
#define TRUECOMPUTERGRAPHICS_SRC_FILE_PPMREADER_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../Render/Color.h"

using std::vector;
using std::string;

class PPMReader {
public:
	PPMReader(string filepath);
	void setFilepath(string filepath);

	vector<vector<Color>> read();

private:
	string mFilepath;
	vector<vector<Color>> mPixels;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_FILE_PPMREADER_H_
