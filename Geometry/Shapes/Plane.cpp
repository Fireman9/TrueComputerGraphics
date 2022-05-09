#include <cmath>
#include "Plane.h"

Plane::Plane(double a, double b, double c, double d) : mA(a), mB(b), mC(c), mD(d) {}

Plane::Plane(Vector normalizedNormal, double d) : mA(normalizedNormal.x()),
												  mB(normalizedNormal.y()),
												  mC(normalizedNormal.z()),
												  mD(d) {}

Vector Plane::getNormal() const {
	return {mA, mB, mC};
}

bool Plane::isRayIntersection(Ray ray, double epsilon) const {
	double denominator = Vector::dotProduct(this->getNormal(), ray.direction());
	if (std::abs(denominator) > epsilon) return true;
	else return false;
}

Point Plane::getRayIntersection(Ray ray, double epsilon) const {
	double denominator = Vector::dotProduct(this->getNormal(), ray.direction());
	if (std::abs(denominator) > epsilon) {
		double t = -(Vector::dotProduct(
			Vector(ray.origin().x(), ray.origin().y(), ray.origin().z()),
			this->getNormal()
		) + mD) / denominator;
		return (ray.direction() * t).toPoint() + ray.origin();
	} else return ray.origin();
}
