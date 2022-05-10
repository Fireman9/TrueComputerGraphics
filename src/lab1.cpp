#include <iostream>
#include "Render/Scene.h"
#include "Geometry/Shapes/Sphere.h"

int main()
{
    Scene myS = Scene();
    const Sphere s = Sphere(20, 0, 0, 160);
    const Sphere s2 = Sphere(20, -15, 10, 170);
    myS.ChangeLight(Vector(2, -4, -3));
    myS.SetSpheres({ s,s2 });
    myS.RenderScene();
    myS.ShowRender();
}
