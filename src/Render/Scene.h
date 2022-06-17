#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

#include "Screen.h"
#include "../Geometry/Vector.h"
#include "../Geometry/Ray.h"
#include "../Geometry/Point.h"
#include "../Geometry/Shapes/Plane.h"
#include "../Geometry/Shapes/Sphere.h"
#include "../Geometry/Shapes/Triangle.h"
#include "../File/PPMWriter.h"
#include "../Tree/Node.h"

using std::vector;
using std::cout;
using std::endl;
using std::thread;

class Scene {
public:
	Scene();

	Scene(Screen screen);

	Scene(Screen screen, Vector light, Point camera, double cameraToScreenDist);

	void renderScene();

	void renderSceneTree();

	void writeRenderToPPM(PPMWriter &ppmWriter);

	void showRenderToConsole();

	double intersections(double x, double y, Point &intersection);

	double intersectionsTree(double x, double y, Point& intersection, Node* tree);

	void setScreen(Screen screen);

	void setLight(Vector light);

	double getCameraToScreenDist();

	void setCameraToScreenDist(double cameraToScreenDist);

	void setCamera(Point camera);

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

	void setTree(Node* t);

private:

	double mCameraToScreenDist;
	Point mCamera;
	Vector mLight;
	Screen mScreen;
	vector<Plane> mPlanes;
	vector<Sphere> mSpheres;
	vector<Triangle> mTriangles;
	Node* tree;

	double sphereIntersection(Sphere sphere, Ray ray, Point &intersectPoint, Point start);

	double planeIntersection(Plane plane, Ray ray, Point &intersectPoint);

	double triangleIntersection(Triangle triangle, Ray ray, Point &intersectPoint);

	static bool isFaced(Vector normal, Vector direction);

	bool static isForward(Point &intersectPoint, Ray ray, Point camera);

	static char getSymbol(double x);

	bool shadow(Point start, Vector lightDir);

	bool shadowTree(Point start, Vector lightDir, Node* tree);

	void renderSceneRange(int yFrom, int yTo, vector<vector<double>> &pixels);

	void renderSceneRangeTree(int yFrom, int yTo, vector<vector<double>> &pixels);
};

#endif //SCENE_H