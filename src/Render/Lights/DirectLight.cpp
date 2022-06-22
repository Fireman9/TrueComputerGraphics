#include "DirectLight.h"

DirectLight::DirectLight(): DirectLight(Color::white()) {}
DirectLight::DirectLight(Color c): DirectLight(c,1.0) {}
DirectLight::DirectLight(double i):DirectLight(Color::white(),i) {}
DirectLight::DirectLight(Vector p): DirectLight(p,Color::white(), 1.0) {}
DirectLight::DirectLight(Vector p, Color c) : DirectLight(p, c, 1.0) {}
DirectLight::DirectLight(Vector p, double i) : DirectLight(p, Color::white(), i) {}
DirectLight::DirectLight(Color c, double i) : DirectLight(Vector(0,0,5), c, 1.0) {}
DirectLight::DirectLight(Vector p, Color c, double i) {
	setColor(c);
	setIntensity(i);
	setDirection(p);
}

void DirectLight::setDirection(Vector p) { p.normalize(); this->directionV = p; }
Vector DirectLight::direction() { return this->directionV; }

const Vector DirectLight::getDir(Point dot) {
	return direction();
}