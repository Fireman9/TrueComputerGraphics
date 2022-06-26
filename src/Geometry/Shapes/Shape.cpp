#include "Shape.h"

#include <utility>

Shape::Shape(Shape::Material m) : mMaterial(m), mTexture(Color::white()) {}

Shape::Shape(Shape::Material m, Texture texture) : mMaterial(m), mTexture(std::move(texture)) {}

Shape::Material Shape::material() {
	return mMaterial;
}

void Shape::setMaterial(Shape::Material m) {
	mMaterial = m;
}

void Shape::setTexture(Texture texture) {
	mTexture = std::move(texture);
}

Texture Shape::getTexture() {
	return mTexture;
}
