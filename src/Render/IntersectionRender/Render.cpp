#include "Render.h"

void Render::renderSceneRange(int yFrom, int yTo, vector<vector<Color>>& pixels) {
	for (int y = yFrom; y < yTo; y++) {
		for (int x = 0; x < pixels[y].size(); x++) {
			pixels[y][x] = intersectionOnScreenFromCamera(x * mScreen.getCoordPerPixel(),
				y * mScreen.getCoordPerPixel());
		}
	}
}