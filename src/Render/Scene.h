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

	Scene(Screen screen, vector<Light*> light, Point camera, double cameraToScreenDist);

	void renderScene();

	void renderSceneTree();

	void writeRenderToPPM(PPMWriter &ppmWriter);

	void showRenderToConsole();

	Color intersections(double x, double y, Point &intersection);

	Color intersectionsTree(double x, double y, Point& intersection, Node* tree);

	void setScreen(Screen screen);

	void setLight(vector<Light*> light);

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
	vector<Light*> mLight;
	Screen mScreen;
	vector<Plane> mPlanes;
	vector<Sphere> mSpheres;
	vector<Triangle> mTriangles;
	Node* tree;

	Color sphereIntersection(Sphere sphere, Ray ray, Point &intersectPoint, Point start, Vector& normal);

	Color planeIntersection(Plane plane, Ray ray, Point &intersectPoint, Vector& normal);

	Color triangleIntersection(Triangle triangle, Ray ray, Point &intersectPoint, Vector& normal);

	static bool isFaced(Vector normal, Vector direction);

	bool static isForward(Point &intersectPoint, Ray ray, Point camera);

	static char getSymbol(Color x);

	bool shadow(Point start, vector<Light*> lightDir, Color &c, Color startColor, Vector norm);

	bool shadowTree(Point start, vector<Light*> lightDir, Node *tree, Color& c, Color startColor, Vector norm);

	void renderSceneRange(int yFrom, int yTo, vector<vector<Color>> &pixels);

	void renderSceneRangeTree(int yFrom, int yTo, vector<vector<Color>> &pixels);

	Color firstIntersection(Point start, Light* l, Color startColor, Vector norm);

	Color firstIntersectionTree(Point start, Light* l, Color startColor, Vector norm, Node* tree);
};

#endif //SCENE_H