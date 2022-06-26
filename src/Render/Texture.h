#ifndef TRUECOMPUTERGRAPHICS_SRC_RENDER_TEXTURE_H_
#define TRUECOMPUTERGRAPHICS_SRC_RENDER_TEXTURE_H_

#include <vector>
#include <utility>

#include "Color.h"
#include "Mappers/Mapper.h"

using std::vector;

class Texture {
public:
	Texture();
	Texture(Color color);
	Texture(vector<vector<Color>> image);

	Color getColor(Point &localHitPoint, Mapper *mapper);
	vector<vector<Color>> getImage();

	void setColor(Color color);
	void setImage(vector<vector<Color>> image);

private:
	Color mColor;
	vector<vector<Color>> mImage;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_RENDER_TEXTURE_H_
