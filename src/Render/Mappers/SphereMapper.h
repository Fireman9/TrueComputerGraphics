#ifndef TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_SPHEREMAPPER_H_
#define TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_SPHEREMAPPER_H_

#include <cmath>

#include "../../Geometry/Point.h"

class SphereMapper {
public:
	static void getCoordinates(Point &localHitPoint, int hRes, int vRes, int &row, int &column);
};

#endif //TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_SPHEREMAPPER_H_
