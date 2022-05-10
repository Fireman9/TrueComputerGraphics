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

private:
	Screen screen;
	Vector light;
	vector <Sphere> spheres;
	//vector <Triangle>;
	//vector <Plane>;

	//String outputFileName;
	//String inputFileName;

	void SetLight(Vector L);
	char GetSymbool(double x);

private:
	double Intersections(int x, int y);
	double SphereIntersec(Sphere sphere, Ray ray, Point& intersectPoint);
	bool static isForward(Point& intersectPoint, Ray ray, Point camera);
};

#endif //SCENE_H