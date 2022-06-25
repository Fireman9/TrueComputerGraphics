#include "Light.h"

Light::Light(): Light(Color::white(), 1) {}
Light::Light(Color c): Light(c, 1) {}
Light::Light(double i): Light(Color::white(),i) {}
Light::Light(Color c, double i) {
	setColor(c);
	setIntensity(i<0 ? 0.001 : i>1 ? 1: i);
}

void Light::setColor(Color c) { this->colorW = c; }
void Light::setIntensity(double i) { this->intens = i;}

const Color Light::apply(Color startColor, Vector normal, Point dot) {
	int r = startColor.r() * (color().r() / 255.0) * intensity();
	int g = startColor.g() * (color().g() / 255.0) * intensity();
	int b = startColor.b() * (color().b() / 255.0) * intensity();
	return { r,g,b,startColor.a() };
}
const Vector Light::getDir(Point d) { 
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(-20, 20);

	double x = distr(eng);
	double y = distr(eng);
	double z = distr(eng);
	Vector v(x,y,z);
	v.normalize();
	return v; }
const Vector Light::getDirInner(Point d) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(-20, 20);

	double x = distr(eng);
	double y = distr(eng);
	double z = distr(eng);
	Vector v(x, y, z);
	v.normalize();
	return v;
}
Color Light::color() { return this->colorW; }
double Light::intensity() { return this->intens; }
const bool Light::isApropriate(Point dot, Point start) {
	return true;
}