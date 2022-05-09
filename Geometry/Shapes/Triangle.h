#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_

#include "../Point.h"
#include "../Ray.h"

class Triangle {
public:
	Triangle(Point first, Point second, Point third);

	bool getRayIntersection(Ray ray, Point &intersectionPoint, double epsilon = 0.01) ;

	Point v0();

	Point v1();

	Point v2();

	void setFirst(Point first);

	void setSecond(Point second);

	void setThird(Point third);

private:
	Point mV0, mV1, mV2;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_
