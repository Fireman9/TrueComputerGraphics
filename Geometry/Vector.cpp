#include <cmath>
#include "Vector.h"

Vector::Vector() : mX(0), mY(0), mZ(0) {}

Vector::Vector(Point start, Point end) {
	this->mX = end.x() - start.x();
	this->mY = end.y() - start.y();
	this->mZ = end.z() - start.z();
}

Vector::Vector(double startX, double startY, double startZ, double endX, double endY, double endZ) {
	this->mX = startX - endX;
	this->mY = startY - endY;
	this->mZ = startZ - endZ;
}

Vector::Vector(double x, double y, double z) : mX(x), mY(y), mZ(z) {}

Vector::Vector(Point p) : mX(p.x()), mY(p.y()), mZ(p.z()) {}

void Vector::setCoordinates(double x, double y, double z) {
	setX(x), setY(y), setZ(z);
}

double Vector::length() const {
	return sqrt(x() * x() + y() * y() + z() * z());
}

void Vector::normalize() {
	if (length() != 1) {
		double lengthInversion = 1 / length();
		setCoordinates(x() * lengthInversion, y() * lengthInversion, z() * lengthInversion);
	}
}

Point Vector::toPoint() const {
	return {x(), y(), z()};
}

Vector Vector::operator+(Vector v) const {
	return {x() + v.x(), y() + v.y(), z() + v.z()};
}

Vector Vector::operator-(Vector v) const {
	return {x() - v.x(), y() - v.y(), z() - v.z()};
}

Vector Vector::operator*(double number) const {
	return {x() * number, y() * number, z() * number};
}

double Vector::x() const {
	return mX;
}

double Vector::y() const {
	return mY;
}

double Vector::z() const {
	return mZ;
}

void Vector::setX(double x) {
	this->mX = x;
}

void Vector::setY(double y) {
	this->mY = y;
}

void Vector::setZ(double z) {
	this->mZ = z;
}

double Vector::dotProduct(Vector v1, Vector v2) {
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

Vector Vector::crossProduct(Vector v1, Vector v2) {
	return {v1.y() * v2.z() - v1.z() * v2.y(),
			v1.z() * v2.x() - v1.x() * v2.z(),
			v1.x() * v2.y() - v1.y() * v2.x()};
}

Vector Vector::normalize(Vector v1) {
	if (v1.length() != 1) {
		double lengthInversion = 1 / v1.length();
		v1.setCoordinates(v1.x() * lengthInversion,
						  v1.y() * lengthInversion,
						  v1.z() * lengthInversion);
	} else return v1;
}
