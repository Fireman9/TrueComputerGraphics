#ifndef RENDER_H
#define RENDER_H

#include "RenderUtils.h"
#include "../../Tree/Node.h"
#include "../Lights/Light.h"

class Render {
	
	Color intersectionOnScreenFromCamera(double x, double y, Node* tree=NULL);
};

#endif //RENDER_H
