#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include <vector>
#include <iostream>

#include "../Color.h"
#include "../../Geometry/Point.h"
#include "../../Geometry/Ray.h"
#include "../../Geometry/Vector.h"
#include "../../Geometry/Shapes/Triangle.h"
#include "../Screen.h"
#include "../../File/PPMWriter.h"
#include "../../Tree/Node.h"

using std::cout;
using std::endl;

class RenderUtils {
public:
	static bool isFaced(Vector normal, Vector direction);

	static bool isForward(Point &intersectPoint, Ray ray, Point camera);

	static char getSymbol(Color x);

	static void showRenderToConsole(Screen mScreen);

	static void writeRenderToPPM(Screen mScreen, PPMWriter &ppmWriter);

	static vector<Triangle> findAllTriangle(Node *tree, Ray ray);
};

#endif //RENDER_UTILS_H
