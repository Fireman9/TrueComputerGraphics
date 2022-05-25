#include <cmath>
#include "Triangle.h"

Triangle::Triangle(Point v0, Point v1, Point v2) : mV0(v0), mV1(v1), mV2(v2) {}

Triangle::Triangle(Point v0, Point v1, Point v2, Vector v0Normal, Vector v1Normal, Vector v2Normal)
	: mV0(v0), mV1(v1), mV2(v2), mV0Normal(v0Normal), mV1Normal(v1Normal), mV2Normal(v2Normal) {}

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

void Triangle::setV0(Point v0) {
	mV0 = v0;
}

void Triangle::setV1(Point v1) {
	mV1 = v1;
}

void Triangle::setV2(Point v2) {
	mV2 = v2;
}

Vector Triangle::v0Normal() {
	return mV0Normal;
}

Vector Triangle::v1Normal() {
	return mV1Normal;
}

Vector Triangle::v2Normal() {
	return mV2Normal;
}

void Triangle::setV0Normal(Vector v0Normal) {
	mV0Normal = v0Normal;
}

void Triangle::setV1Normal(Vector v1Normal) {
	mV1Normal = v1Normal;
}

void Triangle::setV2Normal(Vector v2Normal) {
	mV2Normal = v2Normal;
}
