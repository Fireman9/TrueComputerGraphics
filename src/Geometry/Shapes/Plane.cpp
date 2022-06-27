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

Vector Plane::getNormal(Point dot) {
	return {mA, mB, mC};
}

double Plane::d() const {
	return mD;
}

vector<Point> Plane::getRayIntersection(Ray ray, double epsilon) {
	Point intersectionPoint;
	double denominator = Vector::dotProduct(this->getNormal(intersectionPoint), ray.direction());
	if (std::abs(denominator) > epsilon) {
		double t = -(Vector::dotProduct(
			Vector(ray.origin()),
			this->getNormal(intersectionPoint)
		) + mD) / denominator;
		intersectionPoint = (ray.direction() * t).toPoint() + ray.origin();
		return {intersectionPoint};
	}
	else return {};
}

Point Plane::center() {
	Point p (0,0,-d()/getNormal(Point()).z());
	if (-0.001 < Vector::dotProduct(Vector(p), getNormal(Point())) < 0.001) p = Point(-d() / getNormal(Point()).x(), 0, 0);
	if (-0.001 < Vector::dotProduct(Vector(p), getNormal(Point())) < 0.001) p = Point(0, -d() / getNormal(Point()).y(), 0);
	return p;
}
