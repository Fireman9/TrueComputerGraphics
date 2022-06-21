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

Color DotLight::apply(Color startColor, Vector normal, Point dot) {
	int r = startColor.r() * (color().r() / 255.0) * intensity() * Vector::dotProduct(normal, getDir(dot));
	int g = startColor.g() * (color().g() / 255.0) * intensity() * Vector::dotProduct(normal, getDir(dot));
	int b = startColor.b() * (color().b() / 255.0) * intensity() * Vector::dotProduct(normal, getDir(dot));
	return { r,g,b,startColor.a() };
}
Vector DotLight::getDir(Point dot) { 
	Vector v = Vector(position(), dot);
	v.normalize();
	return v; }