#include "Scene.h"

Scene::Scene() : Scene(Screen(), {std::make_shared<DotLight>(Color::white())},
					   Point(0, 0, 0), 50) {}

Scene::Scene(Screen screen) : Scene(screen, {std::make_shared<DotLight>(Color::white())},
									Point(0, 0, 0), 50) {}

Scene::Scene(Screen screen, vector<std::shared_ptr<Light>> light, Point camera, double cameraToScreenDist)
	: mScreen(screen), mLight(light), mCamera(camera), mCameraToScreenDist(cameraToScreenDist), mTree(nullptr) {}

Screen Scene::getScreen() {
	return mScreen;
}

void Scene::setTree(Node *t) { mTree = t; }

void Scene::renderScene(Node *tree) {
	vector<vector<Color>> pixels(mScreen.getHeight(), vector<Color>(mScreen.getWidth()));
	unsigned int numOfThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	int i, itemsPerThread = pixels.size() / numOfThreads;
	for (i = 0; i < numOfThreads - 1; i++) {
		threads.emplace_back([this, &pixels](int yFrom, int yTo) {
			renderSceneRange(yFrom, yTo, pixels);
		}, i * itemsPerThread, i * itemsPerThread + itemsPerThread);
	}
	renderSceneRange(i * itemsPerThread, pixels.size(), pixels, tree);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	mScreen.setPixels(pixels);
}

void Scene::renderSceneRange(int yFrom, int yTo, vector<vector<Color>> &pixels, Node *tree) {
	for (int y = yFrom; y < yTo; y++) {
		for (int x = 0; x < pixels[y].size(); x++) {
			pixels[y][x] = intersectionOnScreenFromCamera(x * mScreen.getCoordPerPixel(),
														  y * mScreen.getCoordPerPixel(), tree);
		}
	}
}

Color Scene::intersectionOnScreenFromCamera(double x, double y, Node *tree) {
	Point screenTopLeft = getCamera() -
		Point(mScreen.getWidth() * mScreen.getCoordPerPixel() * 0.5,
			  mScreen.getHeight() * mScreen.getCoordPerPixel() * 0.5,
			  0);
	screenTopLeft.setZ(mCameraToScreenDist);
	Point curPoint = screenTopLeft + Point(x, y, 0);
	Vector dir = Vector(mCamera, curPoint);
	dir.normalize();
	Intersection i(mPlanes, mSpheres, mTriangles, mLight, getTree());
	return i.castRay(Ray(mCamera, dir), 0);
}

void Scene::setScreen(Screen screen) { mScreen = screen; }

Point Scene::getCamera() { return mCamera; }

Node *Scene::getTree() { return mTree; }

void Scene::setCamera(Point camera) { mCamera = camera; }

void Scene::setLight(vector<std::shared_ptr<Light>> light) {
	mLight = light;
}

double Scene::getCameraToScreenDist() { return mCameraToScreenDist; }

void Scene::setCameraToScreenDist(double cameraToScreenDist) {
	mCameraToScreenDist = cameraToScreenDist;
}

void Scene::addNewSphere(Sphere sphere) { mSpheres.push_back(sphere); }

void Scene::addNewSpheres(vector<Sphere> spheres) {
	mSpheres.insert(mSpheres.end(), spheres.begin(), spheres.end());
}

void Scene::setSpheres(vector<Sphere> spheres) { mSpheres = spheres; }

void Scene::addNewTriangle(Triangle triangle) { mTriangles.push_back(triangle); }

void Scene::addNewTriangles(vector<Triangle> triangles) {
	mTriangles.insert(mTriangles.end(), triangles.begin(), triangles.end());
}

void Scene::setTriangles(vector<Triangle> triangles) { mTriangles = triangles; }

void Scene::addNewPlane(Plane plane) { mPlanes.push_back(plane); }

void Scene::addNewPlanes(vector<Plane> planes) {
	mPlanes.insert(mPlanes.end(), planes.begin(), planes.end());
}

void Scene::setPlanes(vector<Plane> planes) { mPlanes = planes; }
