#ifndef SCREEN_H
#define SCREEN_H
#include "../Geometry/Point.h"

class Screen {
public:
	Screen();
	Screen(int w, int h, double z );
	Screen(int w, int h, Point start);
	Screen(double x, double y, double z, int w, int h, double z_s);
	Screen(double x, double y, double z, int w, int h, Point start);
	void setSize(int x, int y);
	void setCamera(Point C);
	void setStartPoint(Point start);
	void setCoordPerPixel(double x);
	void setPixelsToZerro();
	void clearPixelsArray();
	void changePixelsSize(int x, int y);
	Point getStartPoint();
	Point getCamera();
	int getWidth();
	int getHeight();
	double** getPixels();
	double getCoordPerPixel();

private:
	double** pixels;
	int w, h;
	Point startPoint; //top left corner of screen 
	Point camera; //for different camera angle, but screen always with normal(0,0,1)
	void setAllData(int w, int h, Point c, double z);
	void setAllData(int w, int h, Point c, Point s);
	void inicializePixelsArray();
	static const double screenSizeH;
	double coordPerPixel;
};
#endif //SCREEN_H