#include <iostream>
#include "Render/Scene.h"
#include "Geometry/Shapes/Sphere.h"

int main()
{
    Scene myS = Scene();
    Vector v = Vector(0, 1, 0);
    v.normalize();
    const Sphere s = Sphere(20, 0, 0, 160);
    const Sphere s2 = Sphere(20, -15, 10, 170);
    const Plane p = Plane(v, -20);
    const Triangle t = Triangle(Point(10, 0, 180), Point(-15, 10, 120), Point(-25, -30, 160));
    const Triangle t2 = Triangle(Point(17, -3, 180), Point(-7, 15, 120), Point(10, -20, 120));
    //myS.ChangeLight(Vector(0, -1, 0));
    myS.SetSpheres({ s,s2 });
    myS.SetPlanes({ p });
    myS.SetTriangles({ t, t2 });
    myS.RenderScene();
    myS.ShowRender();
}
