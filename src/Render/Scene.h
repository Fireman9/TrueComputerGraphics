#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <memory>

#include "Screen.h"
#include "../Geometry/Vector.h"
#include "../Geometry/Ray.h"
#include "../Geometry/Point.h"
#include "../Geometry/Shapes/Plane.h"
#include "../Geometry/Shapes/Sphere.h"
#include "../Geometry/Shapes/Triangle.h"
#include "../File/PPMWriter.h"
#include "../Tree/Node.h"
#include "Lights/Light.h"
#include "Lights/DotLight.h"
#include "Lights/DirectLight.h"

using std::vector;
using std::cout;
using std::endl;
using std::thread;

class Scene {
public:
	Scene();
	Scene(Screen screen);
	Scene(Screen screen, vector<std::shared_ptr<Light>> light, Point camera, double cameraToScreenDist);

	void renderScene();
	void renderSceneTree();

	void writeRenderToPPM(PPMWriter &ppmWriter);
	void showRenderToConsole();

	Color intersectionOnScreenFromCamera(double x, double y);
	Color intersectionOnScreenFromCameraTree(double x, double y, Node *tree);
	Color castRay(Ray ray, int depth);
	Color castRayTree(Ray ray, Node *tree, int depth);
	Color castRayFirstIntersection(Ray ray, Light *l, Color startColor, Vector normal, int depth, bool forShadow = false);
	Color castRayFirstIntersectionTree(Ray ray,
									   Light *l,
									   Color startColor,
									   Vector normal,
									   Node *tree,
									   int depth,
									   bool forShadow = false);

	void setScreen(Screen screen);
	void setLight(vector<std::shared_ptr<Light>> light);
	void setCameraToScreenDist(double cameraToScreenDist);
	void setCamera(Point camera);
	void setTree(Node *t);

	double getCameraToScreenDist();
	Point getCamera();

	void addNewSphere(Sphere sphere);
	void addNewSpheres(vector<Sphere> spheres);
	void setSpheres(vector<Sphere> spheres);

	void addNewTriangle(Triangle triangle);
	void addNewTriangles(vector<Triangle> triangles);
	void setTriangles(vector<Triangle> triangles);

	void addNewPlane(Plane plane);
	void addNewPlanes(vector<Plane> planes);
	void setPlanes(vector<Plane> planes);

private:
	double mCameraToScreenDist;
	Point mCamera;
	vector<std::shared_ptr<Light>> mLight;
	Screen mScreen;
	vector<Plane> mPlanes;
	vector<Sphere> mSpheres;
	vector<Triangle> mTriangles;
	Node *mTree;
	Color objectIntersection(std::shared_ptr<Shape> s,
		Ray ray,
		Point& intersectPoint,
		Vector& normal,
		int depth,
		Color startColor,
		bool shadow=false);

	static bool isFaced(Vector normal, Vector direction);
	bool static isForward(Point &intersectPoint, Ray ray, Point camera);

	static char getSymbol(Color x);

	bool shadow(Point start, vector<std::shared_ptr<Light>> lightDir, Color &c, Color startColor, Vector norm);
	bool shadowTree(Point start,
					vector<std::shared_ptr<Light>> lightDir,
					Node *tree,
					Color &c,
					Color startColor,
					Vector norm);

	void renderSceneRange(int yFrom, int yTo, vector<vector<Color>> &pixels);
	void renderSceneRangeTree(int yFrom, int yTo, vector<vector<Color>> &pixels);
};

#endif //SCENE_H