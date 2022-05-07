#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_VECTOR_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_VECTOR_H_

#include "Point.h"

class Vector {
public:
	Vector();

	Vector(Point &start, Point &end);

	Vector(double startX, double startY, double startZ, double endX, double endY, double endZ);

	Vector(double x, double y, double z);

	void setCoordinates(double x, double y, double z);

	double length() const;

	void normalize();

	Vector operator+(Vector &v) const;

	Vector operator-(Vector &v) const;

	double x() const;

	double y() const;

	double z() const;

	void setX(double x);

	void setY(double y);

	void setZ(double z);

	static double dotProduct(Vector &v1, Vector &v2);

	static Vector crossProduct(Vector &v1, Vector &v2);

private:
	double mX, mY, mZ;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_VECTOR_H_
