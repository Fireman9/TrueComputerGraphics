#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_

#include "../Point.h"

class Triangle {
public:
	Triangle(Point first, Point second, Point third);

	Point first();

	Point second();

	Point third();

	void setFirst(Point first);

	void setSecond(Point second);

	void setThird(Point third);

private:
	Point mFirst, mSecond, mThird;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_
