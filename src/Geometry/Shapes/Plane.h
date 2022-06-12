#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_

#include "../Vector.h"
#include "../Ray.h"

class Plane {
public:
	Plane(double a, double b, double c, double d);

	Plane(Vector normalizedNormal, double d);

	Vector getNormal() const;

	bool getRayIntersection(Ray ray, Point &intersectionPoint, double epsilon = 0.01) const;

private:
	double mA, mB, mC, mD;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_
