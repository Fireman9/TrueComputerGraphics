#include <iostream>
#include "Render/Scene.h"
#include "Geometry/Shapes/Sphere.h"
#include "File/OBJReader.h"
#include "Matrix/Matrix4x4.h"

int main(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);
	OBJReader objReader(arguments);
	objReader.read();

	Scene myS = Scene();
	Vector v = Vector(0, 1, 0);
	v.normalize();
	const Sphere s = Sphere(20, 0, 0, 160);
	const Sphere s2 = Sphere(20, -15, 10, 170);
	const Plane p = Plane(v, -50);
	Triangle t = Triangle(Point(10, 0, 180), Point(-15, 10, 120), Point(-25, -30, 160));
	const Triangle t2 = Triangle(Point(17, -3, 180), Point(-7, 15, 120), Point(10, -20, 120));
	Matrix4x4 r = Matrix4x4::scale(3, 3, 3) * Matrix4x4::rotateZ(0.25) * Matrix4x4::rotateX(-1.2) * Matrix4x4::transpose(-10, 0, 50);
	Matrix4x4 r2 = Matrix4x4::transpose(-10, 0, 50);
	const Triangle t3 = t.transform(r,Point(-7.5,-10,150));
	myS.changeLight(Vector(2, -2, -3));
	myS.setSpheres({s, s2});
	myS.setPlanes({p});
	//myS.setTriangles({t, t3});
	myS.setTriangles({t});
	myS.renderScene();
	myS.showRender();
}
