#include "Scene.h"

Scene::Scene()
	: Scene(Screen(), { new DotLight(Color::white()) }, Point(0, 0, 0), 50) {}

Scene::Scene(Screen screen)
	: Scene(screen, { new DotLight(Color::white()) }, Point(0, 0, 0), 50) {}

Scene::Scene(Screen screen, vector<Light*> light, Point camera, double cameraToScreenDist) {
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
	if (x == -300) return '.';
	else if (x <= 0) return ' ';
	else if (x < 0.2 * 255) return '-';
	else if (x < 0.5 * 255) return '*';
	else if (x < 0.8 * 255) return 'O';
	else return '#';
}

Color Scene::intersectionsTree(double x, double y, Point& intersection, Node* tree) {
	Point intersectPoint;
	Color px(-300,-300,-300,-300);
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
	Vector norm;
	Vector normal;
	//find Node(s)
	tree->findAllNodes(ray, &leafs);
	//look in Nodes
	for (auto& leaf : leafs) {
		for (auto& triangle : leaf->triangles()) {
			Color h_px = triangleIntersection(triangle, ray, intersectPoint,norm);
			dist = intersectPoint.distanceTo(mCamera);
			if (h_px.a() > -256 && minDist > dist) {
				px = h_px;
				minDist = dist;
				normal = norm;
				intersection = intersectPoint;
			}
		}
	}
	// for not only triangles render
	for (auto& plane : mPlanes) {
		Color  h_px = planeIntersection(plane, ray, intersectPoint,norm);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = norm;
			intersection = intersectPoint;
		}
	}
	for (auto& sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, intersectPoint, mCamera, norm);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = norm;
			intersection = intersectPoint;
		}
	}
	Color tmp(0, 0, 0, 0);
	bool isShadow = shadowTree(intersection, mLight,tree, tmp, Color::white(), normal);
	if (px.a() > -256 && isShadow) { px = px - tmp; px.normalize(); }
	return px;
}

bool Scene::shadowTree(Point start, vector<Light*> lightDir, Node* tree, Color& c, Color startColor, Vector norm) {
	Color col(0, 0, 0, 0);
	bool isShadow = false;
	for (auto& l : lightDir) {
		Color c = firstIntersectionTree(start, l, startColor, norm, tree);
		if (c.a() > -256) {
			col = col + c;
			isShadow = true;
		}
	}
	c = col;
	c.normalize();
	return isShadow;
}

Color Scene::firstIntersectionTree(Point start, Light* l, Color startColor, Vector norm,Node* tree) {
	Ray ray = Ray(start, l->getDir(start));
	Point intersectPoint;
	Color col(-300, -300, -300, -300);
	Vector normal;
	for (auto& sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, intersectPoint, start, normal);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px.a() > -256 && l->isApropriate(intersectPoint, start)) {
			col = l->apply(startColor, norm, start);
			return col;
		}
	}
	for (auto& plane : mPlanes) {
		Color h_px = planeIntersection(plane, ray, intersectPoint, normal);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px.a() > -256 && l->isApropriate(intersectPoint, start)) {
			col = l->apply(startColor, norm, start);
			return col;
		}
	}
	vector<Node*> leafs;
	//find Node(s)
	tree->findAllNodes(ray, &leafs);
	//look in Nodes
	for (auto& leaf : leafs) {
		for (auto& triangle : leaf->triangles()) {
			Color h_px = triangleIntersection(triangle, ray, intersectPoint, normal);
			if (!intersectPoint.isEqual(start) && h_px.a() > -256 && l->isApropriate(intersectPoint, start)) {
				col = l->apply(startColor, norm, start);
				return col;
			}
		}
	}
	return col;
}

Color Scene::intersections(double x, double y, Point &intersection) {
	Point intersectPoint;
	Color px(-300,-300,-300,-300);
	double dist;
	Point screenTopLeft = getCamera() - Point(mScreen.getWidth() * mScreen.getCoordPerPixel() * 0.5,
											  mScreen.getHeight() * mScreen.getCoordPerPixel() * 0.5, 0);
	screenTopLeft.setZ(mCameraToScreenDist);
	Point curPoint = screenTopLeft + Point(x, y, 0);
	Vector dir = Vector(mCamera, curPoint);
	dir.normalize();
	Ray ray(mCamera, dir);
	double minDist = 999999;
	Vector norm;
	Vector normal;
	for (auto &sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, intersectPoint, mCamera, norm);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = norm;
			intersection = intersectPoint;
		}
	}
	for (auto &plane : mPlanes) {
		Color h_px = planeIntersection(plane, ray, intersectPoint, norm);
		dist = intersectPoint.distanceTo(mCamera);
		if (isForward(intersectPoint, ray, mCamera) && h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = norm;
			intersection = intersectPoint;
		}
	}
	for (auto &triangle : mTriangles) {
		Color h_px = triangleIntersection(triangle, ray, intersectPoint,norm);
		dist = intersectPoint.distanceTo(mCamera);
		if (h_px.a() > -256 && minDist > dist) {
			px = h_px;
			minDist = dist;
			normal = norm;
			intersection = intersectPoint;
		}
	}
	Color tmp(0,0,0,0);
	bool isShadow = shadow(intersection, mLight, tmp, Color::white(), normal);
	if (px.a() > -256 && isShadow) { px = px - tmp; px.normalize(); }
	return px;
}

bool Scene::shadow(Point start, vector<Light*> lightDir, Color& c, Color startColor, Vector norm) {
	Color col(0, 0, 0, 0);
	bool isShadow = false;
	for (auto& l : lightDir) {
		Color c = firstIntersection(start, l, startColor, norm);
		if (c.a() > -256) {
			col = col + c;
			isShadow = true;
		}
	}
	c = col;
	c.normalize();
	return isShadow;
}

Color Scene::firstIntersection(Point start, Light* l, Color startColor, Vector norm) {
	Ray ray = Ray(start, l->getDir(start));
	Point intersectPoint;
	Color col(-300, -300, -300, -300);
	Vector normal;
	for (auto& sphere : mSpheres) {
		Color h_px = sphereIntersection(sphere, ray, intersectPoint, start, normal);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px.a() > -256 && l->isApropriate(intersectPoint, start)) {
			col = l->apply(startColor, norm, start);
			return col;
		}
	}
	for (auto& plane : mPlanes) {
		Color h_px = planeIntersection(plane, ray, intersectPoint, normal);
		if (!intersectPoint.isEqual(start) &&
			Scene::isForward(intersectPoint, ray, start) &&
			h_px.a() > -256 && l->isApropriate(intersectPoint, start)) {
			col = l->apply(startColor, norm, start);
			return col;
		}
	}
	for (auto& triangle : mTriangles) {
		Color h_px = triangleIntersection(triangle, ray, intersectPoint, normal);
		if (!intersectPoint.isEqual(start) && h_px.a() > -256 && l->isApropriate(intersectPoint, start)) {
			col = l->apply(startColor, norm, start);
			return col; 
		}
	}
	return col;
}

bool Scene::isForward(Point &intersectPoint, Ray ray, Point camera) {
	Vector intersectDir = Vector(camera, intersectPoint);
	intersectDir.normalize();
	return Vector::dotProduct(intersectDir, ray.direction()) > 0;
}

Color Scene::sphereIntersection(Sphere sphere, Ray ray, Point &intersectPoint, Point start, Vector &normal) {
	Sphere::Intersections ans = sphere.isRayIntersection(ray);
	Point first, sec;
	bool firstIsForward, secondIsForward;
	switch (ans) {
		case Sphere::NoIntersection: return Color(-300,-300,-300,-300);
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
				if (!secondIsForward) return Color(-300,-300,-300,-300);
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
		default: return Color(-300,-300,-300,-300);
	}
	normal = Vector(sphere.center(), intersectPoint);
	normal.normalize();
	Color pxl(0,0,0,0);
	for (auto& l : mLight) {
		Color tmp = l->apply(Color::white(), normal, intersectPoint);
		tmp.normalize();
		pxl = pxl + tmp;
	}
	pxl.normalize();
	return pxl;
	//return Color::white() * Vector::dotProduct(norm, mLight);
}

Color Scene::planeIntersection(Plane plane, Ray ray, Point &intersectPoint, Vector& normal) {
	Color px(-300,-300,-300,-300);
	if (plane.getRayIntersection(ray, intersectPoint)) {
		normal = plane.getNormal();
		normal.normalize();
		if (!isFaced(normal, ray.direction())) normal = normal * -1;
		Color pxl(0, 0, 0, 0);
		for (auto& l : mLight) {
			Color tmp = l->apply(Color::white(), normal, intersectPoint);
			tmp.normalize();
			pxl = pxl + tmp;
		}
		pxl.normalize();
		px = pxl;
	}
	return px;
}

Color Scene::triangleIntersection(Triangle triangle, Ray ray, Point &intersectPoint, Vector& normal) {
	Color px(-300, -300, -300, -300);
	if (triangle.getRayIntersection(ray, intersectPoint)) {
		Vector v0v1 = Vector(triangle.v0(), triangle.v1());
		Vector v0v2 = Vector(triangle.v0(), triangle.v2());
		normal = Vector::crossProduct(v0v1, v0v2);
		normal.normalize();
		if (!isFaced(normal, ray.direction())) normal = normal * -1;
		Color pxl(0, 0, 0, 0);
		for (auto& l : mLight) {
			Color tmp = l->apply(Color::white(), normal, intersectPoint);
			tmp.normalize();
			pxl = pxl + tmp;
		}
		pxl.normalize();
		px = pxl;
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

void Scene::setLight(vector<Light*> light) {
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
