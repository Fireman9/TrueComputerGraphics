#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include "Light.h"

class DirectLight : public Light {
public:
	DirectLight();
	DirectLight(Color c);
	DirectLight(double i);
	DirectLight(Vector p);
	DirectLight(Vector p, Color c);
	DirectLight(Vector p, double i);
	DirectLight(Color c, double i);
	DirectLight(Vector p, Color c, double i);

	void setDirection(Vector p);
	Vector direction();

	virtual const Vector getDir(Point dot);

private:
	Vector directionV;
};

#endif //DIRECTLIGHT_H