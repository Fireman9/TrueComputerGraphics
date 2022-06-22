#ifndef LIGHT_H
#define LIGHT_H

#include <stdlib.h>
#include <time.h>
#include <iostream>

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
	double intensity();
	virtual const Vector getDir(Point dot);

	Color apply(Color startColor, Vector normal, Point dot);
private:
	Color colorW;
	double intens;
};

#endif //LIGHT_H
