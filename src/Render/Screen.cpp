#include "Screen.h"

#include <utility>

Screen::Screen() : Screen(100, 100) {}

Screen::Screen(int width, int height) {
	setSize(width, height);
	setCoordPerPixel(1);
}

void Screen::setSize(int width, int height) {
	mWidth = width;
	mHeight = height;
}

void Screen::setCoordPerPixel(double x) { mCoordPerPixel = x; }

void Screen::setPixels(vector<vector<double>> pixels) { mPixels = std::move(pixels); }

int Screen::getWidth() { return mWidth; }

int Screen::getHeight() { return mHeight; }

double Screen::getCoordPerPixel() { return mCoordPerPixel; }

vector<vector<double>> Screen::getPixels() { return mPixels; }
