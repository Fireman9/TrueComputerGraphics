#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <memory>

#include "RenderUtils.h"
#include "../../Geometry/Shapes/Shape.h"
#include "../../Geometry/Shapes/Plane.h"
#include "../../Geometry/Shapes/Sphere.h"
#include "../Lights/Light.h"
#include "../../Tree/Node.h"

class Intersection {
public:

	Intersection(vector<Plane> &planes,
				 vector<Sphere> &spheres,
				 vector<Triangle> &triangles,
				 vector<std::shared_ptr<Light>> &light,
				 Node *tree = nullptr);

	Color objectIntersection(Shape &s, Ray ray, Point &intersectPoint, Vector &normal,
							 int depth, Color startColor, bool shadow = false);

	Color doWithIntersection(Ray ray, Shape &s, int depth, Color &startColor,
							 Vector &normal, Point &intersectPoint, bool shadow);

	Color castRay(Ray ray, int depth);

	bool shadow(Point start, Color &c, Color startColor, Vector norm);

	void inRayHelper(Shape &s, Ray ray, int depth, Color &startColor, double &minDist,
					 Color &px, Vector &normal, Point &intersectPoint);

	bool inShadowHelper(Shape &s, Ray ray, int depth, Color &startColor,
						bool forShadow, Light *l, Vector &normal, Color &col);

	Color castRayFirstIntersection(Ray ray, Light *l, Color startColor, Vector normal,
								   int depth, bool forShadow = false);

private:
	vector<Plane> mPlanes;
	vector<Sphere> mSpheres;
	vector<Triangle> mTriangles;
	vector<std::shared_ptr<Light>> mLight;
	Node *tree;
};

#endif //INTERSECTION_H