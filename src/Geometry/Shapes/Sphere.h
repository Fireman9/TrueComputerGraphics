#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_

#include "../Point.h"
#include "../Ray.h"

class Sphere {

public:
	enum Intersections {
		NoIntersection,
		OnePointIntersection,
		TwoPointIntersection
	};

	Sphere(double radius, Point center);

	Sphere(double radius, double x, double y, double z);

	void getIntersectionVars(double &a, double &b, double &c, double &delta, Ray ray) const;

	Intersections isRayIntersection(Ray ray) const;

	Point getOnePointRayIntersection(Ray ray) const;

	std::pair<Point, Point> getTwoPointRayIntersection(Ray ray) const;

	double radius() const;

	Point center() const;

	void setRadius(double radius);

	void setCenter(Point center);

private:
	double mRadius;
	Point mCenter;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_
