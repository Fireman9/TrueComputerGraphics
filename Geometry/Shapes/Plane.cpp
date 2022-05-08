#include "Plane.h"

Plane::Plane(double a, double b, double c, double d) : mA(a), mB(b), mC(c), mD(d) {}

Plane::Plane(const Vector &normalizedNormal, double d) : mA(normalizedNormal.x()),
														 mB(normalizedNormal.y()),
														 mC(normalizedNormal.z()),
														 mD(d) {}
