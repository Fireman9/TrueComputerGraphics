#ifndef SCENE_H
#define SCENE_H

using namespace std;

#include <vector>
#include <iostream>

#include "Screen.h"
#include "../Geometry/Vector.h"
#include "../Geometry/Ray.h"
#include "../Geometry/Point.h"
#include "../Geometry/Shapes/Plane.h"
#include "../Geometry/Shapes/Sphere.h"
#include "../Geometry/Shapes/Triangle.h"

class Scene {
public:
	Scene();
	Scene(Screen s);
	Scene(Screen s, Vector l);
	void changeLight(Vector l);
	void renderScene();
	void setScreen(Screen s);
	void showRender();

	void setSpheres(vector<Sphere> s);
	void addNewSphere(Sphere s);
	void addNewSphere(vector<Sphere> s);

	void setTriangles(vector<Triangle> t);
	void addNewTriangle(Triangle t);
	void addNewTriangle(vector<Triangle> t);

	void setPlanes(vector<Plane> p);
	void addNewPlane(Plane p);
	void addNewPlane(vector<Plane> p);

	double intersections(double x, double y, Point& intersection);

private:
	Screen screen;
	Vector light;
	vector <Sphere> spheres;
	vector <Triangle> triangles;
	vector <Plane> planes;

	//String outputFileName;
	//String inputFileName;

	void setLight(Vector L);

	double sphereIntersec(Sphere sphere, Ray ray, Point& intersectPoint, Point start);
	double planeIntersec(Plane plane, Ray ray, Point& intersectPoint);
	double triangleIntersec(Triangle triangle, Ray ray, Point& intersectPoint);
	bool isFaced(Vector normal, Vector direction);

	bool static isForward(Point& intersectPoint, Ray ray, Point camera);
	char getSymbool(double x);

	bool shadow(Point start, Vector lightDir);
};

#endif //SCENE_H