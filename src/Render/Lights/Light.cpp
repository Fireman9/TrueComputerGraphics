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

Color Light::apply(Color startColor, Vector normal, Point dot) {
	int r = startColor.r() * (color().r() / 255.0) * intensity() * Vector::dotProduct(normal, getDir(dot));
	int g = startColor.g() * (color().g() / 255.0) * intensity() * Vector::dotProduct(normal, getDir(dot));
	int b = startColor.b() * (color().b() / 255.0) * intensity() * Vector::dotProduct(normal, getDir(dot));
	return { r,g,b,startColor.a() };
}
Vector Light::getDir(Point d) { 
	srand(time(0));
	double x = -20 + (double)rand() / ((double)(RAND_MAX / (20 - (-20))));
	double y = -20 + (double)rand() / ((double)(RAND_MAX / (20 - (-20))));
	double z = -20 + (double)rand() / ((double)(RAND_MAX / (20 - (-20))));
	Vector v(x,y,z);
	v.normalize();
	return v; }
Color Light::color() { return this->colorW; }
double Light::intensity() { return this->intens; }