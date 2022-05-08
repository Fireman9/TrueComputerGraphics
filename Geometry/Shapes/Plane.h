#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_

#include "../Vector.h"

class Plane {
public:
	Plane(double a, double b, double c, double d);

	Plane(const Vector &normalizedNormal, double d);

private:
	double mA, mB, mC, mD;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_PLANE_H_
