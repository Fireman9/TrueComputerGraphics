#include "Shape.h"

Shape::Shape(Shape::Material m) : mMaterial(m) {}

Shape::Material Shape::material() {
	return mMaterial;
}

void Shape::setMaterial(Shape::Material m) {
	mMaterial = m;
}
