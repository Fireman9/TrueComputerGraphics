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
	clearPixelsArray();
	inicializePixelsArray();
	setPixelsToZerro();
};
void Screen::setCamera(Point C) { this->camera = C; };
void Screen::setStartPoint(Point start) { this->startPoint = start; };

Point Screen::getStartPoint() { return this->startPoint; };
Point Screen::getCamera() { return this->camera; }
int Screen::getWidth() { return this->w; };
int Screen::getHeight() { return this->h; };
double** Screen::getPixels() { return this->pixels; };
double Screen::getCoordPerPixel() { return this->coordPerPixel; };

void Screen::setPixelsToZerro() {
	for (int i = 0; i < this->w; i++) {
		for (int j = 0; j < this->h; j++) {
			pixels[j][i] = 0;
		}
	}
};
void Screen::clearPixelsArray() {
	for (int i = 0; i < this->h; i++)
		delete[] pixels[i];
	delete[] pixels;
};
void Screen::inicializePixelsArray() {
	pixels = new double* [this->h];
	for (int i = 0; i < this->h; i++) {
		pixels[i] = new double[this->w];
	}
};

void Screen::setCoordPerPixel(double x) { this->coordPerPixel = x; };

void Screen::setAllData(int W, int H, Point C, double Z) {
	setSize(W, H);
	inicializePixelsArray();
	setPixelsToZerro();
	setCamera(C);
	setCoordPerPixel(this->screenSizeH / H);
	Point sp = C - Point(W * this->coordPerPixel *0.5, this->screenSizeH * 0.5, 0);
	sp.setZ(Z);
	setStartPoint(sp);
}

void Screen::setAllData(int W, int H, Point C, Point sp) {
	setSize(W, H);
	inicializePixelsArray();
	setPixelsToZerro();
	setCamera(C);
	setCoordPerPixel(this->screenSizeH / H);
	setStartPoint(sp);
}