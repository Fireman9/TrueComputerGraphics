#include "Texture.h"

Texture::Texture(Color color) : mColor(color) {}

Color Texture::getColor() {
	// image processing here
	return mColor;
}

void Texture::setColor(Color color) {
	mColor = color;
}
