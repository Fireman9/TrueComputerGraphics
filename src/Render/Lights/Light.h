#ifndef LIGHT_H
#define LIGHT_H

#include <cmath>
#include <random>

#include "../Color.h"
#include "../../Geometry/Vector.h"
#include "../../Geometry/Point.h"

class Light {
public:
	Light();
	Light(Color c);
	Light(double i);
	Light(Color c, double i);

	void setColor(Color c);
	void setIntensity(double i);

	Color color();
	double intensity() const;
	virtual Vector getDir(Point dot);

	virtual Color apply(Color startColor, Vector normal, Point dot);
	virtual Vector getDirInner(Point dot);
	virtual bool isAppropriate(Point dot, Point start);
	virtual bool isMain();

private:
	Color mColorW;
	double mIntens;
};

#endif //LIGHT_H
