#include "Texture.h"

Texture::Texture() = default;

Texture::Texture(Color color) : mColor(color) {}

Texture::Texture(vector<vector<Color>> image) : mImage(std::move(image)) {}

Color Texture::getColor(Point &localHitPoint, IMapper &mapper) {
	if (mImage.empty()) return mColor;
	int row, column;
	mapper.getCoordinates(localHitPoint, mImage[0].size(), mImage.size(), row, column);
	return mImage[row][column];
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
