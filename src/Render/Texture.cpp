#include "Texture.h"

Texture::Texture() = default;

Texture::Texture(Color color) : mColor(color) {}

Texture::Texture(vector<vector<Color>> image) : mImage(std::move(image)) {}

Color Texture::getColor(Point &localHitPoint, IMapper *mapper) {
	if (mImage.empty()) return mColor;

	// pass mapper as parameter
	// call mapper
	// image processing here

}

vector<vector<Color>> Texture::getImage() {
	return mImage;
}

void Texture::setColor(Color color) {
	mColor = color;
}

void Texture::setImage(vector<vector<Color>> image) {
	mImage = std::move(image);
}
