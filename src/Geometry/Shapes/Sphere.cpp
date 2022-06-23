#include <cmath>
#include <exception>
#include "Sphere.h"

Sphere::Sphere(double radius, Point center, Material m)
	: Shape(m), mRadius(radius), mCenter(center) {}

Sphere::Sphere(double radius, double x, double y, double z, Material m)
	: Shape(m), mRadius(radius), mCenter(Point(x, y, z)) {}

void Sphere::getIntersectionVars(double &a, double &b, double &c, double &delta, Ray ray) const {
	a = pow(ray.direction().x(), 2) +
		pow(ray.direction().y(), 2) +
		pow(ray.direction().z(), 2);
	Vector centerToOrigin(center(), ray.origin());
	b = 2 * Vector::dotProduct(ray.direction(), centerToOrigin);
	c = pow(centerToOrigin.x(), 2) + pow(centerToOrigin.y(), 2) +
		pow(centerToOrigin.z(), 2) - pow(radius(), 2);
	delta = pow(b, 2) - 4 * a * c;
}

Sphere::Intersections Sphere::isRayIntersection(Ray ray) const {
	double a, b, c, delta;
	getIntersectionVars(a, b, c, delta, ray);
	if (delta < 0) return NoIntersection;
	else if (delta == 0) {
		double t = -b / (2 * a);
		if (t < 0) return NoIntersection;
		return OnePointIntersection;
	} else {
		double t1 = (-b - sqrt(delta)) / (2 * a);
		double t2 = (-b + sqrt(delta)) / (2 * a);
		if (t1 < 0 || t2 < 0) return NoIntersection;
		return TwoPointIntersection;
	}
}

Point Sphere::getOnePointRayIntersection(Ray ray) const {
	double a, b, c, delta;
	getIntersectionVars(a, b, c, delta, ray);
	if (delta == 0) {
		double t = -b / (2 * a);
		return {ray.origin() + ray.direction().toPoint() * t};
	} else throw std::exception();
}

std::pair<Point, Point> Sphere::getTwoPointRayIntersection(Ray ray) const {
	double a, b, c, delta;
	getIntersectionVars(a, b, c, delta, ray);
	double t1 = (-b - sqrt(delta)) / (2 * a);
	double t2 = (-b + sqrt(delta)) / (2 * a);
	if (delta > 0) {
		return {
			ray.origin() + ray.direction().toPoint() * t1,
			ray.origin() + ray.direction().toPoint() * t2
		};
	} else throw std::exception();
}

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
