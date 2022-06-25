#include <cmath>

#include "Plane.h"

Plane::Plane(double a, double b, double c, double d, Material m)
	: Shape(m), mA(a), mB(b), mC(c), mD(d) {}

Plane::Plane(Vector normalizedNormal, double d, Material m)
	: Shape(m),
	  mA(normalizedNormal.x()),
	  mB(normalizedNormal.y()),
	  mC(normalizedNormal.z()),
	  mD(d) {}

Vector Plane::getNormal() const {
	return {mA, mB, mC};
}

bool Plane::getRayIntersection(Ray ray, Point &intersectionPoint, double epsilon) const {
	double denominator = Vector::dotProduct(this->getNormal(), ray.direction());
	if (std::abs(denominator) > epsilon) {
		double t = -(Vector::dotProduct(
			Vector(ray.origin()),
			this->getNormal()
		) + mD) / denominator;
		intersectionPoint = (ray.direction() * t).toPoint() + ray.origin();
		return true;
	} else return false;
}
