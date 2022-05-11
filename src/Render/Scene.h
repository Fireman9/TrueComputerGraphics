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
	Scene(Screen S);
	Scene(Screen S, Vector L);
	void ChangeLight(Vector L);
	void RenderScene();
	void SetScreen(Screen S);
	void ShowRender();

	void SetSpheres(vector<Sphere> s);
	void AddNewSphere(Sphere s);
	void AddNewSphere(vector<Sphere> s);

	void SetTriangles(vector<Triangle> t);
	void AddNewTriangle(Triangle t);
	void AddNewTriangle(vector<Triangle> t);

	void SetPlanes(vector<Plane> p);
	void AddNewPlane(Plane p);
	void AddNewPlane(vector<Plane> p);

private:
	Screen screen;
	Vector light;
	vector <Sphere> spheres;
	vector <Triangle> triangles;
	vector <Plane> planes;

	//String outputFileName;
	//String inputFileName;

	void SetLight(Vector L);

	double Intersections(double x, double y);
	double SphereIntersec(Sphere sphere, Ray ray, Point& intersectPoint);
	double PlaneIntersec(Plane plane, Ray ray, Point& intersectPoint);
	double TriangleIntersec(Triangle triangle, Ray ray, Point& intersectPoint);
	bool IsFaced(Vector normal, Vector direction);

	bool static isForward(Point& intersectPoint, Ray ray, Point camera);
	char GetSymbool(double x);

};

#endif //SCENE_H