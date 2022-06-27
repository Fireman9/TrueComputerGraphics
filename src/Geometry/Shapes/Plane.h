#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_

#include "../Vector.h"
#include "../Ray.h"
#include "../Shapes/Shape.h"

class Plane : public Shape {
public:
	Plane(double a, double b, double c, double d, Material m = Lambert);
	Plane(Vector normalizedNormal, double d, Material m = Lambert);

	Vector getNormal() const;
	double d() const;

	bool getRayIntersection(Ray ray, Point &intersectionPoint, double epsilon = 0.01) const;

private:
	double mA, mB, mC, mD;
};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_
