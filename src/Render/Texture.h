#ifndef TRUECOMPUTERGRAPHICS_SRC_RENDER_TEXTURE_H_
#define TRUECOMPUTERGRAPHICS_SRC_RENDER_TEXTURE_H_

#include "Color.h"

class Texture {
public:
	Texture(Color color);

	Color getColor();

	void setColor(Color color);

private:
	Color mColor;
//	Image mImage;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_RENDER_TEXTURE_H_
