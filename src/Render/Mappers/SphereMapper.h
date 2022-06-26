#ifndef TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_SPHEREMAPPER_H_
#define TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_SPHEREMAPPER_H_

#include <cmath>

#include "../../Geometry/Point.h"
#include "IMapper.h"

class SphereMapper : public IMapper {
public:
	void getCoordinates(Point &localHitPoint, int hRes, int vRes, int &row, int &column) override;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_RENDER_MAPPERS_SPHEREMAPPER_H_
