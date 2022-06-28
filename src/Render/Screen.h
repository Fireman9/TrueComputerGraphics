#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <utility>

#include "../Geometry/Point.h"
#include "../Render/Color.h"

using std::vector;

class Screen {
public:
	Screen();
	Screen(int width, int height);

	void setSize(int width, int height);
	void setPixels(vector<vector<Color>> pixels);
	void setCoordPerPixel(double x);

	int getWidth();
	int getHeight();
	double getCoordPerPixel();
	vector<vector<Color>> getPixels();

private:
	int mWidth, mHeight;
	double mCoordPerPixel;
	vector<vector<Color>> mPixels;
	int FIX_HEIGHT = 120;
};

#endif //SCREEN_H