#include "DotLight.h"

DotLight::DotLight():DotLight(1) {}
DotLight::DotLight(Color c):DotLight(c, 1) {}
DotLight::DotLight(double i): DotLight(Color::white(),i) {}
DotLight::DotLight(Point p):DotLight(p, Color::white(),1) {}
DotLight::DotLight(Point p, Color c): DotLight(p, c, 1) {}
DotLight::DotLight(Point p, double i): DotLight(p, Color::white(), i) {}
DotLight::DotLight(Color c, double i): DotLight(Point(2,2,2), Color::white(), 1) {}
DotLight::DotLight(Point p, Color c, double i) {
	setColor(c);
	setIntensity(i);
	setPosition(p);
}

void DotLight::setPosition(Point p) { this->positionL = p; }
Point DotLight::position() { return this->positionL; }

Vector DotLight::getDir(Point dot) { 
	Vector v = Vector(position(), dot);
	v.normalize();
	return v; }