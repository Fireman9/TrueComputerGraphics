#ifndef TRUECOMPUTERGRAPHICS_SRC_FILE_PPMWRITER_H_
#define TRUECOMPUTERGRAPHICS_SRC_FILE_PPMWRITER_H_

#include <vector>
#include <string>
#include <fstream>
#include <cmath>

#include "../Geometry/Vector.h"

using std::vector;
using std::string;
using std::ostream;
using std::endl;

class PPMWriter {
public:
	PPMWriter(vector<string> &arguments);

	PPMWriter(string filepath);

	void convert();

	void write();

	void setFilepath(string filepath);

	void setPixels(vector<vector<double>> pixels);

private:
	string mFilepath;
	vector<vector<double>> mPixels;
	vector<vector<Vector>> mOutput;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_FILE_PPMWRITER_H_