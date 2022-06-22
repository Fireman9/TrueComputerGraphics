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
			if (mPixels[i][j].a() == -300) {
				mOutput[i][j] = {0, 0, 0};
			} else {
				mPixels[i][j].normalize();
				mOutput[i][j] = {(double)mPixels[i][j].r(), (double)mPixels[i][j].g(), (double)mPixels[i][j].b()};
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

void PPMWriter::setPixels(vector<vector<Color>> pixels) {
	this->mPixels = std::move(pixels);
}
