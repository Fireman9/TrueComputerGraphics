#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include <vector>
#include <iostream>

#include "../Color.h"
#include "../../Geometry/Point.h"
#include "../../Geometry/Ray.h"
#include "../../Geometry/Vector.h"
#include "../Screen.h"
#include "../../File/PPMWriter.h"

using std::cout;

class RenderUtils {
public:
	static bool isFaced(Vector normal, Vector direction);

	static bool isForward(Point& intersectPoint, Ray ray, Point camera);

	static char getSymbol(Color x);

	static void showRenderToConsole(Screen mScreen);

	static void writeRenderToPPM(Screen mScreen, PPMWriter& ppmWriter);
private:
	RenderUtils();
};

#endif //RENDER_UTILS_H
