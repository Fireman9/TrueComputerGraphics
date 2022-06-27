#include "SphereMapper.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void SphereMapper::getCoordinates(Point &localHitPoint, int hRes, int vRes, int &row, int &column) {
	double theta = acos(localHitPoint.y());
	double phi = atan2(localHitPoint.x(), localHitPoint.z());
	if (phi < 0.0) phi += 2 * M_PI;

	double u = phi / (2 * M_PI);
	double v = (M_PI - theta) / M_PI;

	column = (int) ((hRes - 1) * u);
	row = (int) ((vRes - 1) * v);
}
