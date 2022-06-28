#ifndef RENDER_H
#define RENDER_H

#include "RenderUtils.h"
#include "../../Tree/Node.h"
#include "../Lights/Light.h"

class Render {
	void renderSceneRange(int yFrom, int yTo, vector<vector<Color>>& pixels);
};

#endif //RENDER_H
