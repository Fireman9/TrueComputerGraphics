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

	Color apply(Color startColor, Vector normal, Point dot) override;

	bool isAppropriate(Point dot, Point start) override;
	bool isMain() override;

	Vector direction();

	Vector getDir(Point dot) override;
	Vector getDirInner(Point dot) override;
	void setDirection(Vector p);

private:
	Vector directionV;
};

#endif //DIRECTLIGHT_H