#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_

#include "../Point.h"

class Sphere {
public:
	Sphere(double radius, Point center);

	Sphere(double radius, double x, double y, double z);

	double radius() const;

	Point center() const;

	void setRadius(double radius);

	void setCenter(Point center);

private:
	double mRadius;
	Point mCenter;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_
