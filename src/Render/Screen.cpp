#include "Screen.h"

const double Screen::screenSizeH = 50;

Screen::Screen() {
	setAllData(100, 100, Point(0,0,0), 80.0);
}

Screen::Screen(int w, int h, double z) {
	setAllData(w, h, Point(0, 0, 0), z);
};
Screen::Screen(int w, int h, Point start) { 
	setAllData(w, h, Point(0, 0, 0), start); 
};
Screen::Screen(double x, double y, double z, int w, int h, double z_s) { 
	setAllData(w, h, Point(x, y, z), z_s); 
};
Screen::Screen(double x, double y, double z, int w, int h, Point start) {
	setAllData(w, h, Point(x, y, z), start);
};

void Screen::setSize(int x, int y) { this->w = x; this->h = y; };
void Screen::changePixelsSize(int x, int y) { 
	this->w = x; this->h = y;
	inicializePixelsArray();
};
void Screen::setCamera(Point C) { this->camera = C; };
void Screen::setPixels(vector<vector<double>> p) { this->pixels = p; };
void Screen::setStartPoint(Point start) { this->startPoint = start; };

Point Screen::getStartPoint() { return this->startPoint; };
Point Screen::getCamera() { return this->camera; }
int Screen::getWidth() { return this->w; };
int Screen::getHeight() { return this->h; };
vector<vector<double>>  Screen::getPixels() { return this->pixels; };
double Screen::getCoordPerPixel() { return this->coordPerPixel; };

void Screen::inicializePixelsArray() {
	pixels = {};
};

void Screen::setCoordPerPixel(double x) { this->coordPerPixel = x; };

void Screen::setAllData(int W, int H, Point C, double Z) {
	setSize(W, H);
	inicializePixelsArray();
	setCamera(C);
	setCoordPerPixel(this->screenSizeH / H);
	Point sp = C - Point(W * this->coordPerPixel *0.5, this->screenSizeH * 0.5, 0);
	sp.setZ(Z);
	setStartPoint(sp);
}

void Screen::setAllData(int W, int H, Point C, Point sp) {
	setSize(W, H);
	inicializePixelsArray();
	setCamera(C);
	setCoordPerPixel(this->screenSizeH / H);
	setStartPoint(sp);
}