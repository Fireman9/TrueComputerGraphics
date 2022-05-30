#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

#include "../Geometry/Point.h"

using std::vector;

class Screen {
public:
	Screen();

	Screen(int width, int height);

	void setSize(int width, int height);

	void setPixels(vector<vector<double>> pixels);

	void setCoordPerPixel(double x);

	int getWidth();

	int getHeight();

	double getCoordPerPixel();

	vector<vector<double>> getPixels();

private:
	int mWidth, mHeight;
	double mCoordPerPixel;
	vector<vector<double>> mPixels;
};

#endif //SCREEN_H