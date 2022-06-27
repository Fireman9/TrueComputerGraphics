#ifndef TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_PLANEMAPPER_H_
#define TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_PLANEMAPPER_H_

#include <complex>

#include "../../Geometry/Point.h"
#include "../../Geometry/Vector.h"

class PlaneMapper {
public:
	static void getCoordinates(Point &globalHitPoint, Vector normal, int hRes, int vRes, int &row, int &column);
};

#endif //TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_PLANEMAPPER_H_
