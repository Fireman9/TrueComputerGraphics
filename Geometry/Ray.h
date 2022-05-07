#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_RAY_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_RAY_H_

#include "Point.h"
#include "Vector.h"

class Ray {
public:
	Ray();

	Ray(Point origin, Vector direction);

	Point origin() const;

	void setOrigin(const Point &origin);

	Vector direction() const;

	void setDirection(const Vector &direction);

private:
	Point mOrigin;
	Vector mDirection;

};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_RAY_H_
