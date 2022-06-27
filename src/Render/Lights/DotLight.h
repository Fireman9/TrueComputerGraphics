#ifndef DOTLIGHT_H
#define DOTLIGHT_H

#include "Light.h"

class DotLight :public Light {
public:
	DotLight();
	DotLight(Color c);
	DotLight(double i);
	DotLight(Point p);
	DotLight(Point p, Color c);
	DotLight(Point p, double i);
	DotLight(Color c, double i);
	DotLight(Point p, Color c, double i);
	
	void setPosition(Point p);
	Point position();

	const Vector getDir(Point dot) override;
	const Vector getDirInner(Point dot) override;
	const bool isApropriate(Point dot, Point start) override;
	const Color apply(Color startColor, Vector normal, Point dot) override;
	const bool isMain() override;
private:
	Point positionL;
};

#endif //DOTLIGHT_H
