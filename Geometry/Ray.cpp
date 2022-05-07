#include "Ray.h"

Ray::Ray() : mOrigin({0, 0, 0}), mDirection({0, 0, 1}) {}

Ray::Ray(Point origin, Vector direction) : mOrigin(origin), mDirection(direction) {
	this->mDirection.normalize();
}

Point Ray::origin() const {
	return mOrigin;
}

Vector Ray::direction() const {
	return mDirection;
}

void Ray::setOrigin(const Point &origin) {
	mOrigin = origin;
}

void Ray::setDirection(const Vector &direction) {
	mDirection = direction;
}
