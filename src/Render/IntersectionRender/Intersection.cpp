#include "Intersection.h"

Intersection::Intersection(vector<Plane> &planes, vector<Sphere> &spheres,
						   vector<Triangle> &triangles,
						   vector<std::shared_ptr<Light>> &light, Node *tree) {
	mPlanes = planes;
	mSpheres = spheres;
	mTriangles = triangles;
	mLight = light;
	this->tree = tree;
}

Color Intersection::objectIntersection(Shape &s, Ray ray, Point &intersectPoint, Vector &normal,
									   int depth, Color startColor, bool shadow) {
	auto intersectionPoints = s.getRayIntersection(ray);
	if (intersectionPoints.size() == 1) {
		intersectPoint = intersectionPoints[0];
	} else if (intersectionPoints.size() == 2) {
		Point first = intersectionPoints[0];
		Point second = intersectionPoints[1];
		bool firstIsForward, secondIsForward;
		firstIsForward = RenderUtils::isForward(first, ray, ray.origin());
		secondIsForward = RenderUtils::isForward(second, ray, ray.origin());
		if (!firstIsForward) {
			if (!secondIsForward) return {-300, -300, -300, -300};
			intersectPoint = second;
		} else {
			if (!secondIsForward) intersectPoint = first;
			else {
				if (second.distanceTo(ray.origin()) > first.distanceTo(ray.origin()))
					intersectPoint = first;
				else intersectPoint = second;
			}
		}
	} else {
		return {-300, -300, -300, -300};
	}
	return doWithIntersection(ray, s, depth, startColor, normal, intersectPoint, shadow);
}

Color Intersection::doWithIntersection(Ray ray, Shape &s, int depth, Color &startColor,
									   Vector &normal, Point &intersectPoint, bool shadow) {
	normal = s.getNormal(intersectPoint);
	normal.normalize();
	if (!RenderUtils::isFaced(normal, ray.direction())) normal = normal * -1;
	Color px(0, 0, 0, 0);
	if (s.material() == Shape::Material::Mirror && !shadow) {
		Vector reflectionDir = ray.direction() -
			normal * Vector::dotProduct(ray.direction(), normal) * 2;
		px = px + castRay(Ray(intersectPoint, reflectionDir), depth + 1);
	} else {
		for (auto &l : mLight) {
			startColor = s.getStartColor(intersectPoint);
			Color tmp = l->apply(startColor, normal, intersectPoint);
			tmp.normalize();
			px = px + tmp;
		}
	}
	return px;
}

void Intersection::inRayHelper(Shape &s, Ray ray, int depth, Color &startColor,
							   double &minDist, Color &px, Vector &normal, Point &intersectPoint) {
	Point tempIntersectPoint;
	Vector tempNormal;
	Color startColorLocal;
	Color h_px = objectIntersection(s, ray, tempIntersectPoint, tempNormal, depth, startColorLocal);
	double dist = tempIntersectPoint.distanceTo(ray.origin());
	if (RenderUtils::isForward(tempIntersectPoint, ray, ray.origin()) && h_px.a() > -256 && minDist > dist) {
		px = h_px;
		minDist = dist;
		normal = tempNormal;
		intersectPoint = tempIntersectPoint;
		startColor = startColorLocal;
	}
}

Color Intersection::castRay(Ray ray, int depth) {
	Color px(-300, -300, -300, -300);
	if (depth > 5) {
		px.normalize();
		return px;
	}
	Point intersectPoint;
	double minDist = 999999;
	Vector normal;
	Color startColor;
	for (auto &sphere : mSpheres) {
		inRayHelper(sphere, ray, depth, startColor, minDist, px, normal, intersectPoint);
	}
	for (auto &plane : mPlanes) {
		inRayHelper(plane, ray, depth, startColor, minDist, px, normal, intersectPoint);
	}
	vector<Triangle> t = mTriangles;
	if (tree != nullptr) t = RenderUtils::findAllTriangle(tree, ray);
	for (auto &triangle : t) {
		inRayHelper(triangle, ray, depth, startColor, minDist, px, normal, intersectPoint);
	}
	Color temp(0, 0, 0, 0);
	if (px.a() > -256) {
		if (shadow(intersectPoint, temp, startColor, normal)) {
			px = px - temp;
		}
	}
	px.normalize();
	return px;
}

bool Intersection::shadow(Point start, Color &c, Color startColor, Vector norm) {
	Color col(0, 0, 0, 0);
	bool isShadow = false;
	for (auto &l : mLight) {
		double num = 1;
		bool lightType = false;
		if (l->isMain()) {
			num = 8;
			lightType = true;
		}
		for (int i = 0; i < num; i++) {
			Vector d;
			Ray ray;
			do {
				d = l->getDir(start);
			} while (RenderUtils::isFaced(norm, d) && lightType);
			ray = Ray(start, d);
			Color tempColor = castRayFirstIntersection(ray, l.get(), startColor, norm, 0, true);
			if (tempColor.a() > -256) {
				col = col + tempColor;
				isShadow = true;
			}
		}
		col = col * (1.0 / num);
		col.setAlpha(255);
	}
	c = col;
	c.normalizeMin();
	return isShadow;
}

bool Intersection::inShadowHelper(Shape &s, Ray ray, int depth, Color &startColor, bool forShadow,
								  Light *l, Vector &normal, Color &col) {
	Point tempIntersectPoint;
	Vector tempNormal;
	Color startColorLocal;
	Color h_px = objectIntersection(s, ray, tempIntersectPoint, tempNormal, depth, startColorLocal, forShadow);
	if (!tempIntersectPoint.isEqual(ray.origin()) &&
		RenderUtils::isForward(tempIntersectPoint, ray, ray.origin()) &&
		h_px.a() > -256 &&
		l->isApropriate(tempIntersectPoint, ray.origin())) {
		col = l->apply(startColor, normal, ray.origin());
		return true;
	}
	return false;
}

Color Intersection::castRayFirstIntersection(Ray ray, Light *l, Color startColor,
											 Vector normal, int depth, bool forShadow) {
	Color col(-300, -300, -300, -300);
	if (depth > 5) {
		col.normalize();
		return col;
	}
	for (auto &sphere : mSpheres) {
		if (inShadowHelper(sphere, ray, depth, startColor, forShadow, l, normal, col)) return col;
	}
	for (auto &plane : mPlanes) {
		if (inShadowHelper(plane, ray, depth, startColor, forShadow, l, normal, col)) return col;
	}
	vector<Triangle> t = mTriangles;
	if (tree != nullptr) t = RenderUtils::findAllTriangle(tree, ray);
	for (auto &triangle : t) {
		if (inShadowHelper(triangle, ray, depth, startColor, forShadow, l, normal, col)) return col;
	}
	return col;
}
