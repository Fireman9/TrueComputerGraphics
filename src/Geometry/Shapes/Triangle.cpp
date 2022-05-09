#include <cmath>
#include "Triangle.h"

Triangle::Triangle(Point first, Point second, Point third) : mV0(first),
															 mV1(second),
															 mV2(third) {}

bool Triangle::getRayIntersection(Ray ray, Point &intersectionPoint, double epsilon) {
	Vector v0v1 = Vector(v0(), v1());
	Vector v0v2 = Vector(v0(), v2());
	Vector normal = Vector::crossProduct(v0v1, v0v2);

	double denominator = Vector::dotProduct(normal, ray.direction());
	if (std::abs(denominator) < epsilon) return false; // parallel

	double D = -Vector::dotProduct(normal, Vector(v0()));
	double t = -(Vector::dotProduct(normal, Vector(ray.origin())) + D) / denominator;

	if (t < 0) return false; // triangle behind ray

	intersectionPoint = ray.origin() + ray.direction().toPoint() * t;

	Vector c;
	Vector edge0 = Vector(v0(), v1());
	Vector v0IntPoint = Vector(v0(), intersectionPoint);
	c = Vector::crossProduct(edge0, v0IntPoint);
	if (Vector::dotProduct(normal, c) < 0) return false;

	Vector edge1 = Vector(v1(), v2());
	Vector v1IntPoint = Vector(v1(), intersectionPoint);
	c = Vector::crossProduct(edge1, v1IntPoint);
	if (Vector::dotProduct(normal, c) < 0) return false;

	Vector edge2 = Vector(v2(), v0());
	Vector v2IntPoint = Vector(v2(), intersectionPoint);
	c = Vector::crossProduct(edge2, v2IntPoint);
	if (Vector::dotProduct(normal, c) < 0) return false;

	return true;
}

Point Triangle::v0() {
	return mV0;
}

Point Triangle::v1() {
	return mV1;
}

Point Triangle::v2() {
	return mV2;
}

void Triangle::setFirst(Point first) {
	mV0 = first;
}

void Triangle::setSecond(Point second) {
	mV1 = second;
}

void Triangle::setThird(Point third) {
	mV2 = third;
}
