#include "Scene.h"

Scene::Scene()
	: Scene(Screen(), Vector(2, -4, -3), Point(0, 0, 0), 50) {}

Scene::Scene(Screen screen)
	: Scene(screen, Vector(2, -4, -3), Point(0, 0, 0), 50) {}

Scene::Scene(Screen screen, Vector light, Point camera, double cameraToScreenDist) {
	setScreen(screen);
	setLight(light);
	setCamera(camera);
	mCameraToScreenDist = cameraToScreenDist;
}

void Scene::renderScene() {
	vector<vector<double>> pixels(mScreen.getHeight(), vector<double>(mScreen.getWidth()));
	Point intersectionPoint;
	for (int y = 0; y < mScreen.getHeight(); y++) {
		for (int x = 0; x < mScreen.getWidth(); x++) {
			pixels[y][x] = intersections(x * mScreen.getCoordPerPixel(),
										 y * mScreen.getCoordPerPixel(),
										 intersectionPoint);
		}
	}
	mScreen.setPixels(pixels);
}

void Scene::writeRenderToPPM(PPMWriter &ppmWriter) {
	ppmWriter.setPixels(mScreen.getPixels());
	ppmWriter.convert();
	ppmWriter.write();
}

void Scene::showRenderToConsole() {
	int height = mScreen.getHeight();
	int width = mScreen.getWidth();
	vector<vector<double>> pixels = mScreen.getPixels();
	for (int y = 0; y < width + 1; y++) cout << "--";
	cout << endl;

	for (int y = 0; y < height; y++) {
		cout << '|';
		for (int x = 0; x < width; x++) {
			cout << getSymbol(pixels[y][x]) << ' ';
		}
		cout << '|' << endl;
	}

	for (int y = 0; y < width + 1; y++) cout << "--";
	cout << endl;
}

char Scene::getSymbol(double x) {
	//if we want colored background
	if (x == -2) return '.';
	else if (x <= 0) return ' ';
	else if (x < 0.2) return '-';
	else if (x < 0.5) return '*';
	else if (x < 0.8) return 'O';
	else return '#';
}

double Scene::intersections(double x, double y, Point &intersection) {
	Point intersectPoint;
	double px = -2, dist;
	Point screenTopLeft = getCamera() - Point(mScreen.getWidth() * mScreen.getCoordPerPixel() * 0.5,
											  mScreen.getHeight() * 0.5, 0);
	screenTopLeft.setZ(mCameraToScreenDist);
	Point curPoint = screenTopLeft + Point(x, y, 0);
	Vector dir = Vector(mCamera, curPoint);
	dir.normalize();
	Ray ray(mCamera, dir);
	double minDist = 999999;
	for (auto &sphere : mSpheres) {
		double h_px = sphereIntersection(sphere, ray, intersectPoint, mCamera);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px != -2 && minDist > dist) {
			px = h_px;
			minDist = dist;
			intersection = intersectPoint;
		}
	}
	for (auto &plane : mPlanes) {
		double h_px = planeIntersection(plane, ray, intersectPoint);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px != -2 && minDist > dist) {
			px = h_px;
			minDist = dist;
			intersection = intersectPoint;
		}
	}
	for (auto &triangle : mTriangles) {
		double h_px = triangleIntersection(triangle, ray, intersectPoint);
		dist = intersectPoint.distanceTo(mCamera);
		if (h_px != -2 && minDist > dist) {
			px = h_px;
			minDist = dist;
			intersection = intersectPoint;
		}
	}
	if (px != -2 && shadow(intersection, mLight)) px = std::min(0.0, px);
	return px;
}

bool Scene::shadow(Point start, Vector lightDir) {
	Point intersectPoint;
	Ray ray = Ray(start, lightDir);
	for (auto &sphere : mSpheres) {
		double h_px = sphereIntersection(sphere, ray, intersectPoint, start);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px != -2) {
			return true;
		}
	}
	for (auto &plane : mPlanes) {
		double h_px = planeIntersection(plane, ray, intersectPoint);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px != -2) {
			return true;
		}
	}
	for (auto &triangle : mTriangles) {
		double h_px = triangleIntersection(triangle, ray, intersectPoint);
		if (!intersectPoint.isEqual(start) && h_px != -2) return true;
	}
	return false;
}

bool Scene::isForward(Point &intersectPoint, Ray ray, Point camera) {
	Vector intersectDir = Vector(camera, intersectPoint);
	intersectDir.normalize();
	return Vector::dotProduct(intersectDir, ray.direction()) > 0;
}

double Scene::sphereIntersection(Sphere sphere, Ray ray, Point &intersectPoint, Point start) {
	Sphere::Intersections ans = sphere.isRayIntersection(ray);
	Point first, sec;
	bool firstIsForward, secondIsForward;
	switch (ans) {
		case Sphere::NoIntersection: return -2;
		case Sphere::OnePointIntersection: {
			intersectPoint = sphere.getOnePointRayIntersection(ray);
			break;
		}
		case Sphere::TwoPointIntersection: {
			first = sphere.getTwoPointRayIntersection(ray).first;
			sec = sphere.getTwoPointRayIntersection(ray).second;
			firstIsForward = isForward(first, ray, start);
			secondIsForward = isForward(sec, ray, start);
			if (!firstIsForward) {
				if (!secondIsForward) return -2;
				intersectPoint = sec;
			} else {
				if (!secondIsForward) intersectPoint = first;
				else {
					if (sec.distanceTo(start) > first.distanceTo(start))
						intersectPoint = first;
					else intersectPoint = sec;
				}
			}
			break;
		}
		default: return -2;
	}
	Vector norm = Vector(sphere.center(), intersectPoint);
	norm.normalize();
	return Vector::dotProduct(norm, mLight);
}

double Scene::planeIntersection(Plane plane, Ray ray, Point &intersectPoint) {
	double px = -2;
	if (plane.getRayIntersection(ray, intersectPoint)) {
		Vector norm = plane.getNormal();
		norm.normalize();
		if (!isFaced(norm, ray.direction())) norm = norm * -1;
		px = Vector::dotProduct(norm, mLight);
	}
	return px;
}

double Scene::triangleIntersection(Triangle triangle, Ray ray, Point &intersectPoint) {
	double px = -2;
	if (triangle.getRayIntersection(ray, intersectPoint)) {
		Vector v0v1 = Vector(triangle.v0(), triangle.v1());
		Vector v0v2 = Vector(triangle.v0(), triangle.v2());
		Vector norm = Vector::crossProduct(v0v1, v0v2);
		norm.normalize();
		if (!isFaced(norm, ray.direction())) norm = norm * -1;
		px = Vector::dotProduct(norm, mLight);
	}
	return px;
}

bool Scene::isFaced(Vector normal, Vector direction) {
	if (Vector::dotProduct(normal, direction) < 0) return true;
	else return false;
}

void Scene::setScreen(Screen screen) { mScreen = screen; }

Point Scene::getCamera() { return mCamera; }

void Scene::setCamera(Point camera) { mCamera = camera; }

void Scene::setLight(Vector light) {
	light.normalize();
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
