#include "Screen.h"

Screen::Screen() : Screen(100, 100) {}

Screen::Screen(int width, int height) {
	setSize(width, height);
	//setCoordPerPixel(1);
	setCoordPerPixel((double) FIX_HEIGHT / height);
}

void Screen::setSize(int width, int height) {
	mWidth = width;
	mHeight = height;
}

void Screen::setCoordPerPixel(double x) { mCoordPerPixel = x; }

void Screen::setPixels(vector<vector<Color>> pixels) { mPixels = std::move(pixels); }

int Screen::getWidth() { return mWidth; }

int Screen::getHeight() { return mHeight; }

double Screen::getCoordPerPixel() { return mCoordPerPixel; }

vector<vector<Color>> Screen::getPixels() { return mPixels; }
