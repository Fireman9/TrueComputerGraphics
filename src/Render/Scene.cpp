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

void Scene::setTree(Node* t) { this->tree = t; }

void Scene::renderSceneTree() {
	vector<vector<Color>> pixels(mScreen.getHeight(), vector<Color>(mScreen.getWidth()));
	unsigned int numOfThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	int i, itemsPerThread = pixels.size() / numOfThreads;
	for (i = 0; i < numOfThreads - 1; i++) {
		threads.emplace_back([this, &pixels](int yFrom, int yTo) {
			renderSceneRangeTree(yFrom, yTo, pixels);
			}, i * itemsPerThread, i * itemsPerThread + itemsPerThread);
	}
	renderSceneRangeTree(i * itemsPerThread, pixels.size(), pixels);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	mScreen.setPixels(pixels);
}

void Scene::renderSceneRangeTree(int yFrom, int yTo, vector<vector<Color>>& pixels) {
	Point intersectionPoint;
	for (int y = yFrom; y < yTo; y++) {
		for (int x = 0; x < pixels[y].size(); x++) {
			pixels[y][x] = intersectionsTree(x * mScreen.getCoordPerPixel(),
				y * mScreen.getCoordPerPixel(),
				intersectionPoint,tree);
		}
	}
}

void Scene::renderScene() {
	vector<vector<Color>> pixels(mScreen.getHeight(), vector<Color>(mScreen.getWidth()));
	unsigned int numOfThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	int i, itemsPerThread = pixels.size() / numOfThreads;
	for (i = 0; i < numOfThreads - 1; i++) {
		threads.emplace_back([this, &pixels](int yFrom, int yTo) {
			renderSceneRange(yFrom, yTo, pixels);
		}, i * itemsPerThread, i * itemsPerThread + itemsPerThread);
	}
	renderSceneRange(i * itemsPerThread, pixels.size(), pixels);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	mScreen.setPixels(pixels);
}

void Scene::renderSceneRange(int yFrom, int yTo, vector<vector<Color>> &pixels) {
	Point intersectionPoint;
	for (int y = yFrom; y < yTo; y++) {
		for (int x = 0; x < pixels[y].size(); x++) {
			pixels[y][x] = intersections(x * mScreen.getCoordPerPixel(),
										 y * mScreen.getCoordPerPixel(),
										 intersectionPoint);
		}
	}
}

void Scene::writeRenderToPPM(PPMWriter &ppmWriter) {
	ppmWriter.setPixels(mScreen.getPixels());
	ppmWriter.convert();
	ppmWriter.write();
}

void Scene::showRenderToConsole() {
	int height = mScreen.getHeight();
	int width = mScreen.getWidth();
	vector<vector<Color>> pixels = mScreen.getPixels();
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

char Scene::getSymbol(Color c) {
	//if we want colored background
	int x = (c.r() + c.g() + c.b())/3;
	if (x == -2) return '.';
	else if (x <= 0) return ' ';
	else if (x < 0.2 * 255) return '-';
	else if (x < 0.5 * 255) return '*';
	else if (x < 0.8 * 255) return 'O';
	else return '#';
}

Color Scene::intersectionsTree(double x, double y, Point& intersection, Node* tree) {
	Point intersectPoint;
	Color px(-2,-2,-2,-2);
	double dist;
	Point screenTopLeft = getCamera() - Point(mScreen.getWidth() * mScreen.getCoordPerPixel() * 0.5,
		mScreen.getHeight() * mScreen.getCoordPerPixel()  * 0.5, 0);
	screenTopLeft.setZ(mCameraToScreenDist);
	Point curPoint = screenTopLeft + Point(x, y, 0);
	Vector dir = Vector(mCamera, curPoint);
	dir.normalize();
	Ray ray(mCamera, dir);
	double minDist = 999999;
	vector<Node*> leafs;
	//find Node(s)
	tree->findAllNodes(ray, &leafs);
	//look in Nodes
	for (auto& leaf : leafs) {
		for (auto& triangle : leaf->triangles()) {
			Color h_px = triangleIntersection(triangle, ray, intersectPoint);
			dist = intersectPoint.distanceTo(mCamera);
			if (h_px.a() != -2 && minDist > dist) {
				px = h_px;
				minDist = dist;
				intersection = intersectPoint;
			}
		}
	}
	// for not only triangles render
	for (auto& plane : mPlanes) {
		Color  h_px = planeIntersection(plane, ray, intersectPoint);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px.a() != -2 && minDist > dist) {
			px = h_px;
			minDist = dist;
			intersection = intersectPoint;
		}
	}
	for (auto& sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, intersectPoint, mCamera);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px.a() != -2 && minDist > dist) {
			px = h_px;
			minDist = dist;
			intersection = intersectPoint;
		}
	}
	if (px.a() != -2 && shadowTree(intersection, mLight, tree)) px = Color(std::min(0, px.r()), std::min(0, px.g()), std::min(0, px.b()), std::min(0, px.a()));
	return px;
}

bool Scene::shadowTree(Point start, Vector lightDir, Node* tree) {
	Point intersectPoint;
	Ray ray = Ray(start, lightDir);
	vector<Node*> leafs;
	//find Node(s)
	tree->findAllNodes(ray, &leafs);
	//look in Nodes
	for (auto& leaf : leafs) {
		for (auto& triangle : leaf->triangles()) {
			Color h_px = triangleIntersection(triangle, ray, intersectPoint);
			if (!intersectPoint.isEqual(start) && h_px.a() != -2) return true;
		}
	}
	// for not only triangles render
	for (auto & sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, intersectPoint, start);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px.a() != -2) {
			return true;
		}
	}
	for (auto& plane : mPlanes) {
		Color h_px = planeIntersection(plane, ray, intersectPoint);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px.a() != -2) {
			return true;
		}
	}
	return false;
}

Color Scene::intersections(double x, double y, Point &intersection) {
	Point intersectPoint;
	Color px(-2,-2,-2,-2);
	double dist;
	Point screenTopLeft = getCamera() - Point(mScreen.getWidth() * mScreen.getCoordPerPixel() * 0.5,
											  mScreen.getHeight() * mScreen.getCoordPerPixel() * 0.5, 0);
	screenTopLeft.setZ(mCameraToScreenDist);
	Point curPoint = screenTopLeft + Point(x, y, 0);
	Vector dir = Vector(mCamera, curPoint);
	dir.normalize();
	Ray ray(mCamera, dir);
	double minDist = 999999;
	for (auto &sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, intersectPoint, mCamera);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px.a() != -2 && minDist > dist) {
			px = h_px;
			minDist = dist;
			intersection = intersectPoint;
		}
	}
	for (auto &plane : mPlanes) {
		Color h_px = planeIntersection(plane, ray, intersectPoint);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px.a() != -2 && minDist > dist) {
			px = h_px;
			minDist = dist;
			intersection = intersectPoint;
		}
	}
	for (auto &triangle : mTriangles) {
		Color h_px = triangleIntersection(triangle, ray, intersectPoint);
		dist = intersectPoint.distanceTo(mCamera);
		if (h_px.a() != -2 && minDist > dist) {
			px = h_px;
			minDist = dist;
			intersection = intersectPoint;
		}
	}
	if (px.a() != -2 && shadow(intersection, mLight)) px = Color(std::min(0, px.r()), std::min(0, px.g()), std::min(0, px.b()), std::min(0, px.a()));
	return px;
}

bool Scene::shadow(Point start, Vector lightDir) {
	Point intersectPoint;
	Ray ray = Ray(start, lightDir);
	for (auto &sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, intersectPoint, start);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px.a() != -2) {
			return true;
		}
	}
	for (auto &plane : mPlanes) {
		Color h_px = planeIntersection(plane, ray, intersectPoint);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px.a() != -2) {
			return true;
		}
	}
	for (auto &triangle : mTriangles) {
		Color h_px = triangleIntersection(triangle, ray, intersectPoint);
		if (!intersectPoint.isEqual(start) && h_px.a() != -2) return true;
	}
	return false;
}

bool Scene::isForward(Point &intersectPoint, Ray ray, Point camera) {
	Vector intersectDir = Vector(camera, intersectPoint);
	intersectDir.normalize();
	return Vector::dotProduct(intersectDir, ray.direction()) > 0;
}

Color Scene::sphereIntersection(Sphere sphere, Ray ray, Point &intersectPoint, Point start) {
	Sphere::Intersections ans = sphere.isRayIntersection(ray);
	Point first, sec;
	bool firstIsForward, secondIsForward;
	switch (ans) {
		case Sphere::NoIntersection: return Color(-2,-2,-2,-2);
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
				if (!secondIsForward) return Color(-2,-2,-2,-2);
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
		default: return Color(-2,-2,-2,-2);
	}
	Vector norm = Vector(sphere.center(), intersectPoint);
	norm.normalize();
	return Color::white() * Vector::dotProduct(norm, mLight);
}

Color Scene::planeIntersection(Plane plane, Ray ray, Point &intersectPoint) {
	Color px(-2,-2,-2,-2);
	if (plane.getRayIntersection(ray, intersectPoint)) {
		Vector norm = plane.getNormal();
		norm.normalize();
		if (!isFaced(norm, ray.direction())) norm = norm * -1;
		px = Color::white() * Vector::dotProduct(norm, mLight);
	}
	return px;
}

Color Scene::triangleIntersection(Triangle triangle, Ray ray, Point &intersectPoint) {
	Color px(-2,-2,-2,-2);
	if (triangle.getRayIntersection(ray, intersectPoint)) {
		Vector v0v1 = Vector(triangle.v0(), triangle.v1());
		Vector v0v2 = Vector(triangle.v0(), triangle.v2());
		Vector norm = Vector::crossProduct(v0v1, v0v2);
		norm.normalize();
		if (!isFaced(norm, ray.direction())) norm = norm * -1;
		std::cout << Vector::dotProduct(norm, mLight)<<" | "<<(Color::white() * Vector::dotProduct(norm, mLight)).r() << " \n ";
		px = Color::white() * Vector::dotProduct(norm, mLight);
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
