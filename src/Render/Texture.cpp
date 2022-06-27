#include "Texture.h"

Texture::Texture() = default;

Texture::Texture(Color color) : mColor(color) {}

Texture::Texture(vector<vector<Color>> image) : mImage(std::move(image)) {}

Color Texture::getColorSphere(Point &localHitPoint) {
	if (mImage.empty()) return mColor;

	double theta = acos(localHitPoint.y());
	double phi = atan2(localHitPoint.x(), localHitPoint.z());
	if (phi < 0.0) phi += 2 * M_PI;

	double u = phi / (2 * M_PI);
	double v = (M_PI - theta) / M_PI;

	int column = (int) ((mImage[0].size() - 1) * u);
	int row = (int) ((mImage.size() - 1) * v);
	return mImage[row][column];
}

Color Texture::getColorPlane(Point &globalHitPoint, Vector normal) {
	if (mImage.empty()) return mColor;
	int row, column;
//	PlaneMapper::getCoordinates(globalHitPoint, normal, mImage[0].size(), mImage.size(), row, column);
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
