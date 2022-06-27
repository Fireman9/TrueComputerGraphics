#include "Texture.h"

Texture::Texture() = default;

Texture::Texture(Color color) : mColor(color) {}

Texture::Texture(vector<vector<Color>> image) : mImage(std::move(image)) {}

Color Texture::getColorSphere(Point &localHitPoint) {
	if (mImage.empty()) return mColor;
	int row, column;
	SphereMapper::getCoordinates(localHitPoint, mImage[0].size(), mImage.size(), row, column);
	return mImage[row][column];
}

Color Texture::getColorPlane(Point &globalHitPoint, Vector normal) {
	if (mImage.empty()) return mColor;
	int row, column;
	PlaneMapper::getCoordinates(globalHitPoint, normal, mImage[0].size(), mImage.size(), row, column);
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
