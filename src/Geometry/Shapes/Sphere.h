#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_

#include <vector>
#include <cmath>

#include "../Point.h"
#include "../Ray.h"
#include "../Shapes/Shape.h"

using std::vector;

class Sphere : public Shape {
public:
	Sphere(double radius, Point center, Material m = Lambert);
	Sphere(double radius, double x, double y, double z, Material m = Lambert);

	vector<Point> getRayIntersection(Ray ray, double epsilon = 0.01) override;

	double radius() const;
	Point center() override;

	void setRadius(double radius);
	void setCenter(Point center);

	Vector getNormal(Point dot) override;
	Color getStartColor(Point inter) override;

private:
	double mRadius;
	Point mCenter;
};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_
