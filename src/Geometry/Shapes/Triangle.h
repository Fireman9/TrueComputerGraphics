#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_

#include <cmath>

#include "../Point.h"
#include "../Ray.h"
#include "../Shapes/Shape.h"
#include "../../Matrix/Matrix4x4.h"

class Triangle : public Shape {
public:
	Triangle(Point v0, Point v1, Point v2, Material m = Lambert);
	Triangle(Point v0, Point v1, Point v2,
			 Vector v0Normal, Vector v1Normal, Vector v2Normal,
			 Material m = Lambert);

	Vector getNormal(Point dot) override;

	vector<Point> getRayIntersection(Ray ray, double epsilon = 0.0000001) override;

	Triangle transform(Matrix4x4 matrix, Point transPoint);

	Point v0();
	Point v1();
	Point v2();

	Vector v0Normal();
	Vector v1Normal();
	Vector v2Normal();

	Point center() override;

	void setV0(Point v0);
	void setV1(Point v1);
	void setV2(Point v2);

	void setV0Normal(Vector v0Normal);
	void setV1Normal(Vector v1Normal);
	void setV2Normal(Vector v2Normal);

private:
	Point mV0, mV1, mV2;
	Vector mV0Normal, mV1Normal, mV2Normal;
};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_SHAPES_TRIANGLE_H_
