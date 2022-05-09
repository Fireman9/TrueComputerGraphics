#include <cmath>
#include "Point.h"

Point::Point() : mX(0), mY(0), mZ(0) {}

Point::Point(double x, double y, double z) : mX(x), mY(y), mZ(z) {}

void Point::setCoordinates(double x, double y, double z) {
	setX(x), setY(y), setZ(z);
}

double Point::distanceTo(Point p) const {
	double dx, dy, dz;

	dx = this->x() - p.x();
	dy = this->y() - p.y();
	dz = this->z() - p.z();

	return sqrt(dx * dx + dy * dy + dz * dz);
}

double Point::distanceTo(double x, double y, double z) const {
	double dx, dy, dz;

	dx = this->x() - x;
	dy = this->y() - y;
	dz = this->z() - z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

bool Point::isEqual(Point p, double epsilon) const {
	return std::abs(this->x() - p.x()) < epsilon &&
		std::abs(this->y() - p.y()) < epsilon &&
		std::abs(this->z() - p.z()) < epsilon;
}

Point Point::operator+(Point p) const {
	return {x() + p.x(), y() + p.y(), z() + p.z()};
}

Point Point::operator-(Point p) const {
	return {x() - p.x(), y() - p.y(), z() - p.z()};
}

Point Point::operator*(double number) const {
	return {x() * number, y() * number, z() * number};
}

double Point::x() const {
	return mX;
}

double Point::y() const {
	return mY;
}

double Point::z() const {
	return mZ;
}

void Point::setX(double x) {
	this->mX = x;
}

void Point::setY(double y) {
	this->mY = y;
}

void Point::setZ(double z) {
	this->mZ = z;
}
