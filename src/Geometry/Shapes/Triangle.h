#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_

#include "../Point.h"
#include "../Ray.h"

class Triangle {
public:
	Triangle(Point v0, Point v1, Point v2);

	Triangle(Point v0, Point v1, Point v2, Vector v0Normal, Vector v1Normal, Vector v2Normal);

	bool getRayIntersection(Ray ray, Point &intersectionPoint, double epsilon = 0.01);

	Point v0();

	Point v1();

	Point v2();

	void setV0(Point v0);

	void setV1(Point v1);

	void setV2(Point v2);

	Vector v0Normal();

	Vector v1Normal();

	Vector v2Normal();

	void setV0Normal(Vector v0Normal);

	void setV1Normal(Vector v1Normal);

	void setV2Normal(Vector v2Normal);

private:
	Point mV0, mV1, mV2;
	Vector mV0Normal, mV1Normal, mV2Normal;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_
