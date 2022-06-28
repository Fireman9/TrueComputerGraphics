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
#include "IntersectionRender/Intersection.h"

using std::vector;
using std::cout;
using std::endl;
using std::thread;

class Scene {
public:
	Scene();
	Scene(Screen screen);
	Scene(Screen screen, vector<std::shared_ptr<Light>> light, Point camera, double cameraToScreenDist);

	void renderScene(Node *tree = nullptr);

	Color intersectionOnScreenFromCamera(double x, double y, Node *tree = nullptr);

	void setScreen(Screen screen);
	void setLight(vector<std::shared_ptr<Light>> light);
	void setCameraToScreenDist(double cameraToScreenDist);
	void setCamera(Point camera);
	void setTree(Node *t);

	double getCameraToScreenDist();
	Point getCamera();
	Screen getScreen();
	Node *getTree();

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

	void renderSceneRange(int yFrom, int yTo, vector<vector<Color>> &pixels, Node *tree = nullptr);
};

#endif //SCENE_H