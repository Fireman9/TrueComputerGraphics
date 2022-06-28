#include "DirectLight.h"

DirectLight::DirectLight() : DirectLight(Color::white()) {}

DirectLight::DirectLight(Color c) : DirectLight(c, 1.0) {}

DirectLight::DirectLight(double i) : DirectLight(Color::white(), i) {}

DirectLight::DirectLight(Vector p) : DirectLight(p, Color::white(), 1.0) {}

DirectLight::DirectLight(Vector p, Color c) : DirectLight(p, c, 1.0) {}

DirectLight::DirectLight(Vector p, double i) : DirectLight(p, Color::white(), i) {}

DirectLight::DirectLight(Color c, double i) : DirectLight(Vector(0, 0, 5), c, 1.0) {}

DirectLight::DirectLight(Vector p, Color c, double i) : Light(c, i), directionV(p) {}

void DirectLight::setDirection(Vector p) {
	p.normalize();
	this->directionV = p;
}

Vector DirectLight::direction() { return this->directionV; }

Vector DirectLight::getDir(Point dot) { return direction() * (-1); }

Vector DirectLight::getDirInner(Point dot) { return direction(); }

bool DirectLight::isAppropriate(Point dot, Point start) { return true; }

Color DirectLight::apply(Color startColor, Vector normal, Point dot) {
	double d = intensity() * Vector::dotProduct(normal, getDirInner(dot)) * -1;
	int r = startColor.r() * (color().r() / 255.0) * d;
	int g = startColor.g() * (color().g() / 255.0) * d;
	int b = startColor.b() * (color().b() / 255.0) * d;
	return {r, g, b, startColor.a()};
}

bool DirectLight::isMain() { return false; }
