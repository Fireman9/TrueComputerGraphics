#include "Light.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Light::Light() : Light(Color::white(), 1) {}

Light::Light(Color c) : Light(c, 1) {}

Light::Light(double i) : Light(Color::white(), i) {}

Light::Light(Color c, double i) : mColorW(c), mIntens(i < 0 ? 0.001 : i > 1 ? 1 : i) {}

void Light::setColor(Color c) { this->mColorW = c; }

void Light::setIntensity(double i) { this->mIntens = i; }

Color Light::apply(Color startColor, Vector normal, Point dot) {
	int r = startColor.r() * (color().r() / 255.0) * intensity();
	int g = startColor.g() * (color().g() / 255.0) * intensity();
	int b = startColor.b() * (color().b() / 255.0) * intensity();
	return {r, g, b, startColor.a()};
}

Vector Light::getDir(Point d) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(0, 0.99999999999);

	double u = distr(eng);
	double v = distr(eng);
	double t = 2 * M_PI * u;
	double p = acos(1 - 2 * v);

	double x = sin(p) * cos(t);
	double y = sin(p) * sin(t);
	double z = cos(p);
	Vector vec(x, y, z);
	vec.normalize();
	return vec;
}

Vector Light::getDirInner(Point d) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(0, 1);

	double u = distr(eng);
	double v = distr(eng);
	double t = 2 * M_PI * u;
	double p = acos(1 - 2 * v);

	double x = sin(p) * cos(t);
	double y = sin(p) * sin(t);
	double z = cos(p);
	Vector vec(x, y, z);
	vec.normalize();
	return vec;
}

Color Light::color() { return this->mColorW; }

double Light::intensity() const { return this->mIntens; }

bool Light::isAppropriate(Point dot, Point start) { return true; }

bool Light::isMain() { return true; }