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

	enum Material {
		Mirror,
		Lambert
	};

	Sphere(double radius, Point center, Material material = Lambert);

	Sphere(double radius, double x, double y, double z, Material material = Lambert);

	void getIntersectionVars(double &a, double &b, double &c, double &delta, Ray ray) const;

	Intersections isRayIntersection(Ray ray) const;

	Point getOnePointRayIntersection(Ray ray) const;

	std::pair<Point, Point> getTwoPointRayIntersection(Ray ray) const;

	double radius() const;

	Point center() const;

	void setRadius(double radius);

	void setCenter(Point center);

	Material material();

private:
	double mRadius;
	Point mCenter;
	Material mMaterial;
};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_SPHERE_H_
