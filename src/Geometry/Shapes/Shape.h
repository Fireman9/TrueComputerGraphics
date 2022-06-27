#ifndef TRUECOMPUTERGRAPHICS_SRC_GEOMETRY_SHAPES_SHAPE_H_
#define TRUECOMPUTERGRAPHICS_SRC_GEOMETRY_SHAPES_SHAPE_H_

#include "../../Render/Texture.h"
#include "../Ray.h"

class Shape {
public:
	enum Material {
		Mirror,
		Lambert
	};

	Shape(Material m);
	Shape(Material m, Texture texture);

	Material material();
	void setMaterial(Material m);

	void setTexture(Texture texture);
	Texture getTexture();

	virtual Vector getNormal(Point dot);
	virtual Point center();
	virtual vector<Point> getRayIntersection(Ray ray, double epsilon = 0.01);
	virtual Color getStartColor(Point inter);

private:
	Material mMaterial;
	Texture mTexture;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_GEOMETRY_SHAPES_SHAPE_H_
