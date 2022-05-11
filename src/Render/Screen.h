#ifndef SCREEN_H
#define SCREEN_H
#include "../Geometry/Point.h"

class Screen {
public:
	Screen();
	Screen(int W, int H, double Z );
	Screen(int W, int H, Point start);
	Screen(double X, double Y, double Z, int W, int H, double Z_s);
	Screen(double X, double Y, double Z, int W, int H, Point start);
	void SetSize(int x, int y);
	void SetCamera(Point C);
	void SetStartPoint(Point start);
	void SetCoordPerPixel(double x);
	void SetPixelsToZerro();
	void ClearPixelsArray();
	void ChangePixelsSize(int x, int y);
	Point GetStartPoint();
	Point GetCamera();
	int GetWidth();
	int GetHeight();
	double** GetPixels();
	double GetCoordPerPixel();

private:
	double** pixels;
	int w, h;
	Point startPoint; //top left corner of screen 
	Point camera; //for different camera angle, but screen always with normal(0,0,1)
	void SetAllData(int W, int H, Point C, double Z);
	void SetAllData(int W, int H, Point C, Point S);
	void InicializePixelsArray();
	static const double screenSizeH;
	double coordPerPixel;
};
#endif //SCREEN_H