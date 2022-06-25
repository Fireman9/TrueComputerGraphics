#include "Sphere.h"

Sphere::Sphere(double radius, Point center, Material m)
	: Shape(m), mRadius(radius), mCenter(center) {}

Sphere::Sphere(double radius, double x, double y, double z, Material m)
	: Shape(m), mRadius(radius), mCenter(Point(x, y, z)) {}

vector<Point> Sphere::getRayIntersection(Ray ray) const {
	vector<Point> result;
	double a = pow(ray.direction().x(), 2) +
		pow(ray.direction().y(), 2) +
		pow(ray.direction().z(), 2);
	Vector centerToOrigin(center(), ray.origin());
	double b = 2 * Vector::dotProduct(ray.direction(), centerToOrigin);
	double c = pow(centerToOrigin.x(), 2) + pow(centerToOrigin.y(), 2) +
		pow(centerToOrigin.z(), 2) - pow(radius(), 2);
	double delta = pow(b, 2) - 4 * a * c;

	if (delta < 0) return result;
	else if (delta == 0) {
		double t = -b / (2 * a);
		if (t < 0) return result;
		result.push_back(ray.origin() + ray.direction().toPoint() * t);
		return result;
	} else {
		double t1 = (-b - sqrt(delta)) / (2 * a);
		double t2 = (-b + sqrt(delta)) / (2 * a);
		if (t1 < 0 || t2 < 0) return result;
		result.push_back(ray.origin() + ray.direction().toPoint() * t1);
		result.push_back(ray.origin() + ray.direction().toPoint() * t2);
		return result;
	}
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
