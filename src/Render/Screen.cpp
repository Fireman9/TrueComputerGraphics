#include "Screen.h"

Screen::Screen() {
	SetAllData(20, 20, Point(0,0,0), 50.0);
}

Screen::Screen(int W, int H, double Z) {
	SetAllData(W, H, Point(0, 0, 0), Z);
};
Screen::Screen(int W, int H, Point start) { 
	SetAllData(W, H, Point(0, 0, 0), start); 
};
Screen::Screen(double X, double Y, double Z, int W, int H, double Z_s) { 
	SetAllData(W, H, Point(X, Y, Z), Z_s); 
};
Screen::Screen(double X, double Y, double Z, int W, int H, Point start) {
	SetAllData(W, H, Point(X, Y, Z), start);
};

void Screen::SetSize(int x, int y) { this->w = x; this->h = y; };
void Screen::ChangePixelsSize(int x, int y) { 
	this->w = x; this->h = y;
	ClearPixelsArray();
	InicializePixelsArray();
	SetPixelsToZerro();
};
void Screen::SetCamera(Point C) { this->camera = C; };
void Screen::SetStartPoint(Point start) { this->startPoint = start; };

Point Screen::GetStartPoint() { return this->startPoint; };
Point Screen::GetCamera() { return this->camera; }
int Screen::GetWidth() { return this->w; };
int Screen::GetHeight() { return this->h; };
double** Screen::GetPixels() { return this->pixels; };

void Screen::SetPixelsToZerro() {
	for (int i = 0; i < this->w; i++) {
		for (int j = 0; j < this->h; j++) {
			pixels[j][i] = 0;
		}
	}
};
void Screen::ClearPixelsArray() {
	for (int i = 0; i < this->h; i++)
		delete[] pixels[i];
	delete[] pixels;
};
void Screen::InicializePixelsArray() {
	pixels = new double* [this->h];
	for (int i = 0; i < this->h; i++) {
		pixels[i] = new double[this->w];
	}
};

void Screen::SetAllData(int W, int H, Point C, double Z) {
	SetSize(W, H);
	InicializePixelsArray();
	SetPixelsToZerro();
	SetCamera(C);
	Point sp = (C * 0.5);
	sp.setZ(Z);
	SetStartPoint(sp);
}

void Screen::SetAllData(int W, int H, Point C, Point sp) {
	SetSize(W, H);
	InicializePixelsArray();
	SetPixelsToZerro();
	SetCamera(C);
	SetStartPoint(sp);
}