#include "PPMWriter.h"

PPMWriter::PPMWriter(vector<string> &arguments) {
	std::string temp = "--output=";
	for (auto argument : arguments) {
		if (argument.find(temp) != std::string::npos) {
			mFilepath = argument.erase(0, temp.length());
			break;
		}
	}
}

PPMWriter::PPMWriter(string filepath) : mFilepath(filepath) {}

void PPMWriter::convert() {
	mOutput.resize(mPixels.size());
	for (int i = 0; i < mPixels.size(); ++i) {
		mOutput[i].resize(mPixels[i].size());
	}

	for (int i = 0; i < mPixels.size(); ++i) {
		for (int j = 0; j < mPixels[i].size(); ++j) {
			Vector white(255, 255, 255);
			if (mPixels[i][j] == -2) {
				mOutput[i][j] = {0, 0, 0};
			} else {
				if (mPixels[i][j] > 0) {
					mOutput[i][j] = {
						floor((white * mPixels[i][j]).x()),
						floor((white * mPixels[i][j]).y()),
						floor((white * mPixels[i][j]).z())
					};
				} else {
					mOutput[i][j] = {0, 0, 0};
				}
			}
		}
	}
}

void PPMWriter::write() {
	std::ofstream file(mFilepath);
	if (file.is_open()) {
		file << "P3" << endl;
		file << mOutput[0].size() << " " << mOutput.size() << endl;
		file << "255" << endl;
		for (auto &i : mOutput) {
			for (auto &j : i) {
				file << j.x() << " " << j.y() << " " << j.z() << endl;
			}
		}
		file.close();
	}
}

void PPMWriter::setFilepath(string filepath) {
	this->mFilepath = filepath;
}

void PPMWriter::setPixels(vector<vector<double>> pixels) {
	this->mPixels = std::move(pixels);
}
