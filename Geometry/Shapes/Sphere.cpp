#include "Sphere.h"

Sphere::Sphere(double radius, Point center) : mRadius(radius), mCenter(center) {}

Sphere::Sphere(double radius, double x, double y, double z) : mRadius(radius), mCenter(Point(x, y, z)) {}

double Sphere::radius() const {
	return this->mRadius;
}

Point Sphere::center() const {
	return this->mCenter;
}

void Sphere::setRadius(double radius) {
	this->mRadius = radius;
}

void Sphere::setCenter(Point center) {
	this->mCenter = center;
}
