#include "RenderUtils.h"

bool RenderUtils::isFaced(Vector normal, Vector direction) {
	if (Vector::dotProduct(normal, direction) <= 0) return true;
	else return false;
}

bool RenderUtils::isForward(Point& intersectPoint, Ray ray, Point camera) {
	Vector intersectDir = Vector(camera, intersectPoint);
	intersectDir.normalize();
	return Vector::dotProduct(intersectDir, ray.direction()) > 0;
}

char RenderUtils::getSymbol(Color c) {
	//if we want colored background
	int x = (c.r() +  c.g() + c.b()) / 3;
	if (x == -300) return '.';
	else if (x <= 0) return ' ';
	else if (x < 0.2 * 255) return '-';
	else if (x < 0.5 * 255) return '*';
	else if (x < 0.8 * 255) return 'O';
	else return '#';
}

void RenderUtils::showRenderToConsole(Screen mScreen) {
	int height = mScreen.getHeight();
	int width = mScreen.getWidth();
	vector<vector<Color>> pixels = mScreen.getPixels();
	for (int y = 0; y < width + 1; y++) cout << "--";
	cout << std::endl;

	for (int y = 0; y < height; y++) {
		cout << '|';
		for (int x = 0; x < width; x++) {
			cout << getSymbol(pixels[y][x]) << ' ';
		}
		cout << '|' << std::endl;
	}

	for (int y = 0; y < width + 1; y++) cout << "--";
	cout << std::endl;
}

void RenderUtils::writeRenderToPPM(Screen mScreen, PPMWriter& ppmWriter) {
	ppmWriter.setPixels(mScreen.getPixels());
	ppmWriter.convert();
	ppmWriter.write();
}