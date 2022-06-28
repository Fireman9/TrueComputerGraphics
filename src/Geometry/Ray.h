#ifndef TRUECOMPUTERGRAPHICS_GEOMETRY_RAY_H_
#define TRUECOMPUTERGRAPHICS_GEOMETRY_RAY_H_

#include "Point.h"
#include "Vector.h"

class Ray {
public:
	Ray();
	Ray(Point origin, Vector direction);

	Point origin() const;
	Vector direction() const;

	void setOrigin(Point origin);
	void setDirection(Vector direction);

private:
	Point mOrigin;
	Vector mDirection;
};

#endif //TRUECOMPUTERGRAPHICS_GEOMETRY_RAY_H_
