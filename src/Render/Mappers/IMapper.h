#ifndef TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_IMAPPER_H_
#define TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_IMAPPER_H_

#include "../../Geometry/Point.h"

class IMapper {
public:
	virtual void getCoordinates(Point &localHitPoint, int hRes, int vRes, int &row, int &column) = 0;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_IMAPPER_H_
