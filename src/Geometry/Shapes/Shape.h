#ifndef TRUECOMPUTERGRAPHICS_SRC_GEOMETRY_SHAPES_SHAPE_H_
#define TRUECOMPUTERGRAPHICS_SRC_GEOMETRY_SHAPES_SHAPE_H_

class Shape {
public:
	enum Material {
		Mirror,
		Lambert
	};

	Shape(Material m);

	Material material();
	void setMaterial(Material m);

private:
	Material mMaterial;
};

#endif //TRUECOMPUTERGRAPHICS_SRC_GEOMETRY_SHAPES_SHAPE_H_
