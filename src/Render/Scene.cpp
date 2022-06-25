#include "Scene.h"

Scene::Scene()
	: Scene(Screen(), {std::make_shared<DotLight>(Color::white())},
			Point(0, 0, 0), 50) {}

Scene::Scene(Screen screen)
	: Scene(screen, {std::make_shared<DotLight>(Color::white())},
			Point(0, 0, 0), 50) {}

Scene::Scene(Screen screen, vector<std::shared_ptr<Light>> light, Point camera, double cameraToScreenDist)
	: mScreen(screen), mLight(light), mCamera(camera), mCameraToScreenDist(cameraToScreenDist) {}

void Scene::setTree(Node* t) { mTree = t; }

void Scene::renderSceneTree() {
	// TODO: OpenMP
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

void Scene::renderSceneRangeTree(int yFrom, int yTo, vector<vector<Color>> &pixels) {
	for (int y = yFrom; y < yTo; y++) {
		for (int x = 0; x < pixels[y].size(); x++) {
			pixels[y][x] = intersectionOnScreenFromCameraTree(
				x * mScreen.getCoordPerPixel(),
				y * mScreen.getCoordPerPixel(),
				mTree);
		}
	}
}

void Scene::renderScene() {
	// TODO: OpenMP
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
	for (int y = yFrom; y < yTo; y++) {
		for (int x = 0; x < pixels[y].size(); x++) {
			pixels[y][x] = intersectionOnScreenFromCamera(x * mScreen.getCoordPerPixel(),
														  y * mScreen.getCoordPerPixel());
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
	if (x == -300) return '.';
	else if (x <= 0) return ' ';
	else if (x < 0.2 * 255) return '-';
	else if (x < 0.5 * 255) return '*';
	else if (x < 0.8 * 255) return 'O';
	else return '#';
}

Color Scene::intersectionOnScreenFromCamera(double x, double y) {
	Point screenTopLeft = getCamera() -
		Point(mScreen.getWidth() * mScreen.getCoordPerPixel() * 0.5,
			  mScreen.getHeight() * mScreen.getCoordPerPixel() * 0.5,
			  0);
	screenTopLeft.setZ(mCameraToScreenDist);
	Point curPoint = screenTopLeft + Point(x, y, 0);
	Vector dir = Vector(mCamera, curPoint);
	dir.normalize();
	return castRay(Ray(mCamera, dir), 0);
}

Color Scene::intersectionOnScreenFromCameraTree(double x, double y, Node *tree) {
	Point screenTopLeft = getCamera() -
		Point(mScreen.getWidth() * mScreen.getCoordPerPixel() * 0.5,
			  mScreen.getHeight() * mScreen.getCoordPerPixel() * 0.5,
			  0);
	screenTopLeft.setZ(mCameraToScreenDist);
	Point curPoint = screenTopLeft + Point(x, y, 0);
	Vector dir = Vector(mCamera, curPoint);
	dir.normalize();
	return castRayTree(Ray(mCamera, dir), tree, 0);
}

Color Scene::castRay(Ray ray, int depth) {
	Color px(-300, -300, -300, -300);
	if (depth > 5) {
		px.normalize();
		return px;
	}
	Point intersectPoint;
	double minDist = 999999;
	Vector normal;
	for (auto &sphere : mSpheres) {
		Point tempIntersectPoint;
		Vector tempNormal;
		Color h_px = sphereIntersection(sphere, ray, tempIntersectPoint, ray.origin(), tempNormal, depth);
		double dist = tempIntersectPoint.distanceTo(ray.origin());
		if (isForward(tempIntersectPoint, ray, ray.origin()) && h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = tempNormal;
			intersectPoint = tempIntersectPoint;
		}
	}
	for (auto &plane : mPlanes) {
		Point tempIntersectPoint;
		Vector tempNormal;
		Color h_px = planeIntersection(plane, ray, tempIntersectPoint, tempNormal, depth);
		double dist = tempIntersectPoint.distanceTo(mCamera);
		if (isForward(tempIntersectPoint, ray, ray.origin()) && h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = tempNormal;
			intersectPoint = tempIntersectPoint;
		}
	}
	for (auto &triangle : mTriangles) {
		Point tempIntersectPoint;
		Vector tempNormal;
		Color h_px = triangleIntersection(triangle, ray, tempIntersectPoint, tempNormal, depth);
		double dist = tempIntersectPoint.distanceTo(mCamera);
		if (h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = tempNormal;
			intersectPoint = tempIntersectPoint;
		}
	}
	Color temp(0, 0, 0, 0);
	bool isShadow = shadow(intersectPoint, mLight, temp, Color::white(), normal);
	if (px.a() > -256 && isShadow) {
		px = px - temp;
		px.normalize();
	}
	return px;
}

Color Scene::castRayTree(Ray ray, Node *tree, int depth) {
	Color px(-300, -300, -300, -300);
	if (depth > 5) {
		px.normalize();
		return px;
	}
	Point intersectPoint;
	double minDist = 999999;
	Vector normal;

	vector<Node *> leafs;
	tree->findAllNodes(ray, &leafs);
	for (auto &leaf : leafs) {
		for (auto &triangle : leaf->triangles()) {
			Point tempIntersectPoint;
			Vector tempNormal;
			Color h_px = triangleIntersection(triangle, ray, tempIntersectPoint, tempNormal, depth);
			double dist = tempIntersectPoint.distanceTo(mCamera);
			if (h_px.a() > -256 && minDist > dist) {
				px = h_px;
				minDist = dist;
				normal = tempNormal;
				intersectPoint = tempIntersectPoint;
			}
		}
	}

	for (auto &sphere : mSpheres) {
		Point tempIntersectPoint;
		Vector tempNormal;
		Color h_px = sphereIntersection(sphere, ray, tempIntersectPoint, ray.origin(), tempNormal, depth);
		double dist = tempIntersectPoint.distanceTo(ray.origin());
		if (isForward(tempIntersectPoint, ray, ray.origin()) && h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = tempNormal;
			intersectPoint = tempIntersectPoint;
		}
	}
	for (auto &plane : mPlanes) {
		Point tempIntersectPoint;
		Vector tempNormal;
		Color h_px = planeIntersection(plane, ray, tempIntersectPoint, tempNormal, depth);
		double dist = tempIntersectPoint.distanceTo(mCamera);
		if (isForward(tempIntersectPoint, ray, ray.origin()) && h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = tempNormal;
			intersectPoint = tempIntersectPoint;
		}
	}

	Color temp(0, 0, 0, 0);
	bool isShadow = shadow(intersectPoint, mLight, temp, Color::white(), normal);
	if (px.a() > -256 && isShadow) {
		px = px - temp;
		px.normalize();
	}
	return px;
}

bool Scene::shadow(Point start, vector<std::shared_ptr<Light>> lightDir, Color &c, Color startColor, Vector norm) {
	Color col(0, 0, 0, 0);
	bool isShadow = false;
	for (auto &l : lightDir) {
		Ray ray = Ray(start, l->getDir(start));
		Color tempColor = castRayFirstIntersection(ray, l.get(), startColor, norm, 0, true);
		if (tempColor.a() > -256) {
			col = col + tempColor;
			isShadow = true;
		}
	}
	c = col;
	c.normalizeMin();
	return isShadow;
}

bool Scene::shadowTree(Point start,
					   vector<std::shared_ptr<Light>> lightDir,
					   Node *tree,
					   Color &c,
					   Color startColor,
					   Vector norm) {
	Color col(0, 0, 0, 0);
	bool isShadow = false;
	for (auto &l : lightDir) {
		Ray ray = Ray(start, l->getDir(start));
		Color tempColor = castRayFirstIntersectionTree(ray, l.get(), startColor, norm, tree, 0, true);
		if (tempColor.a() > -256) {
			col = col + tempColor;
			isShadow = true;
		}
	}
	c = col;
	c.normalizeMin();
	return isShadow;
}

Color Scene::castRayFirstIntersection(Ray ray, Light *l, Color startColor, Vector normal, int depth, bool forShadow) {
	Color col(-300, -300, -300, -300);
	if (depth > 5) {
		col.normalize();
		return col;
	}
	Point tempIntersectPoint;
	Vector tempNormal;
	for (auto &sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, tempIntersectPoint, ray.origin(), tempNormal, depth, forShadow);
		if (!tempIntersectPoint.isEqual(ray.origin()) &&
			Scene::isForward(tempIntersectPoint, ray, ray.origin()) &&
			h_px.a() > -256 &&
			l->isApropriate(tempIntersectPoint, ray.origin())) {
			col = l->apply(startColor, normal, ray.origin());
			return col;
		}
	}
	for (auto &plane : mPlanes) {
		Color h_px = planeIntersection(plane, ray, tempIntersectPoint, tempNormal, depth, forShadow);
		if (!tempIntersectPoint.isEqual(ray.origin()) &&
			Scene::isForward(tempIntersectPoint, ray, ray.origin()) &&
			h_px.a() > -256 && l->isApropriate(tempIntersectPoint, ray.origin())) {
			col = l->apply(startColor, normal, ray.origin());
			return col;
		}
	}
	for (auto &triangle : mTriangles) {
		Color h_px = triangleIntersection(triangle, ray, tempIntersectPoint, tempNormal, depth, forShadow);
		if (!tempIntersectPoint.isEqual(ray.origin()) && h_px.a() > -256
			&& l->isApropriate(tempIntersectPoint, ray.origin())) {
			col = l->apply(startColor, normal, ray.origin());
			return col;
		}
	}
	return col;
}

Color Scene::castRayFirstIntersectionTree(Ray ray,
										  Light *l,
										  Color startColor,
										  Vector normal,
										  Node *tree,
										  int depth,
										  bool forShadow) {
	Color col(-300, -300, -300, -300);
	if (depth > 5) {
		col.normalize();
		return col;
	}
	Point tempIntersectPoint;
	Vector tempNormal;
	for (auto &sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, tempIntersectPoint, ray.origin(), tempNormal, depth, forShadow);
		if (!tempIntersectPoint.isEqual(ray.origin()) &&
			Scene::isForward(tempIntersectPoint, ray, ray.origin()) &&
			h_px.a() > -256 &&
			l->isApropriate(tempIntersectPoint, ray.origin())) {
			col = l->apply(startColor, normal, ray.origin());
			return col;
		}
	}
	for (auto &plane : mPlanes) {
		Color h_px = planeIntersection(plane, ray, tempIntersectPoint, tempNormal, depth, forShadow);
		if (!tempIntersectPoint.isEqual(ray.origin()) &&
			Scene::isForward(tempIntersectPoint, ray, ray.origin()) &&
			h_px.a() > -256 && l->isApropriate(tempIntersectPoint, ray.origin())) {
			col = l->apply(startColor, normal, ray.origin());
			return col;
		}
	}
	vector<Node *> leafs;
	//find Node(s)
	tree->findAllNodes(ray, &leafs);
	//look in Nodes
	for (auto &leaf : leafs) {
		for (auto &triangle : leaf->triangles()) {
			Color h_px = triangleIntersection(triangle, ray, tempIntersectPoint, tempNormal, depth, forShadow);
			if (!tempIntersectPoint.isEqual(ray.origin()) && h_px.a() > -256
				&& l->isApropriate(tempIntersectPoint, ray.origin())) {
				col = l->apply(startColor, normal, ray.origin());
				return col;
			}
		}
	}
	return col;
}

bool Scene::isForward(Point &intersectPoint, Ray ray, Point camera) {
	Vector intersectDir = Vector(camera, intersectPoint);
	intersectDir.normalize();
	return Vector::dotProduct(intersectDir, ray.direction()) > 0;
}

Color Scene::sphereIntersection(Sphere sphere,
								Ray ray,
								Point &intersectPoint,
								Point start,
								Vector &normal,
								int depth,
								bool shadow) {
	auto intersectionPoints = sphere.getRayIntersection(ray);
	if (intersectionPoints.size() == 1) {
		intersectPoint = intersectionPoints[0];
	} else if (intersectionPoints.size() == 2) {
		Point first = intersectionPoints[0];
		Point second = intersectionPoints[1];
		bool firstIsForward, secondIsForward;
		firstIsForward = isForward(first, ray, start);
		secondIsForward = isForward(second, ray, start);
		if (!firstIsForward) {
			if (!secondIsForward) return {-300, -300, -300, -300};
			intersectPoint = second;
		} else {
			if (!secondIsForward) intersectPoint = first;
			else {
				if (second.distanceTo(start) > first.distanceTo(start))
					intersectPoint = first;
				else intersectPoint = second;
			}
		}
	} else {
		return {-300, -300, -300, -300};
	}
	normal = Vector(sphere.center(), intersectPoint);
	normal.normalize();
	return materialCheck(sphere, ray, normal, intersectPoint, depth, shadow);
}

Color Scene::planeIntersection(Plane plane, Ray ray, Point &intersectPoint, Vector &normal, int depth, bool shadow) {
	Color px(-300, -300, -300, -300);
	if (plane.getRayIntersection(ray, intersectPoint)) {
		normal = plane.getNormal();
		normal.normalize();
		if (!isFaced(normal, ray.direction())) normal = normal * -1;
		px = materialCheck(plane, ray, normal, intersectPoint, depth, shadow);
	}
	return px;
}

Color Scene::triangleIntersection(Triangle triangle,
								  Ray ray,
								  Point &intersectPoint,
								  Vector &normal,
								  int depth,
								  bool shadow) {
	Color px(-300, -300, -300, -300);
	if (triangle.getRayIntersection(ray, intersectPoint)) {
		Vector v0v1 = Vector(triangle.v0(), triangle.v1());
		Vector v0v2 = Vector(triangle.v0(), triangle.v2());
		normal = Vector::crossProduct(v0v1, v0v2);
		normal.normalize();
		if (!isFaced(normal, ray.direction())) normal = normal * -1;
		px = materialCheck(triangle, ray, normal, intersectPoint, depth, shadow);
	}
	return px;
}

Color Scene::materialCheck(Shape shape, Ray ray, Vector normal, Point intersectPoint, int depth, bool shadow) {
	Color pxl(0, 0, 0, 0);
	if (shape.material() == Shape::Material::Mirror && !shadow) {
		Vector reflectionDir = ray.direction() -
			normal * Vector::dotProduct(ray.direction(), normal) * 2;
		pxl = pxl + castRay(Ray(intersectPoint, reflectionDir), depth + 1);
	} else {
		for (auto &l : mLight) {
			Color tmp = l->apply(Color::white(), normal, intersectPoint);
			tmp.normalize();
			pxl = pxl + tmp;
		}
	}
	return pxl;
}

bool Scene::isFaced(Vector normal, Vector direction) {
	if (Vector::dotProduct(normal, direction) <= 0) return true;
	else return false;
}

void Scene::setScreen(Screen screen) { mScreen = screen; }

Point Scene::getCamera() { return mCamera; }

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
