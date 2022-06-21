#include "Color.h"
#include <iostream>

Color::Color():Color(255,255,255,255) {}
Color::Color(int rW, int gW, int bW, int aW) {
	setRed(rW);
	setGreen(gW);
	setBlue(bW);
	setAlpha(aW);
}
Color::Color(double rW, double gW, double bW, double aW) {
	setRed(rW);
	setGreen(gW);
	setBlue(bW);
	setAlpha(aW);
}

Color Color::white() { return Color(); }
Color Color::black() { return Color(0,0,0,255); }
Color Color::red() { return Color(255,0,0,255); }
Color Color::green() { return Color(0, 255, 0, 255); }
Color Color::blue() { return Color(0, 0, 255, 255); }

int Color::r()  const { return this->redW; }
int Color::g()  const { return this->greenW; }
int Color::b()  const { return this->blueW; }
int Color::a()  const { return this->alphaW; }

void Color::setRed(int rW) { this->redW = rW; }
void Color::setGreen(int gW) { this->greenW = gW; }
void Color::setBlue(int bW) { this->blueW = bW; }
void Color::setAlpha(int aW) { this->alphaW = aW; }
void Color::setRed(double rW) { rW = 255 * rW; this->redW = (rW < 0) ? 0 : (rW > 255) ? 255 : rW; }
void Color::setGreen(double gW) { gW = 255 * gW; this->greenW = (gW < 0) ? 0 : (gW > 255) ? 255 : gW; }
void Color::setBlue(double bW) { bW = 255 * bW; this->blueW = (bW < 0) ? 0 : (bW > 255) ? 255 : bW; }
void Color::setAlpha(double aW) { aW = 255 * aW; this->alphaW = (aW < 0) ? 0 : (aW > 255) ? 255 : aW; }

Color Color::operator* (double x) const { 
	return { (int)(r()*x),(int)(g() * x),(int)(b() * x),(int)(a() * x)};
}
Color Color::operator+ (Color c) const {
	return { r() + c.r(), g() + c.g(), b() + c.b(),a() + c.a() };
}
void Color::normalize() {
	setRed(r()<0 ? 0 : r()>255 ? 255 : r());
	setGreen(g()<0 ? 0 : g()>255 ? 255 : g());
	setBlue(b()<0 ? 0 : b()>255 ? 255 : b());
	setAlpha(a()<0 ? 0 : a()>255 ? 255 : a());
}
