#include <iostream>
#include "Render/Scene.h"
#include "Geometry/Shapes/Sphere.h"

int main()
{
    std::cout << "Hello World!\n";
    Scene myS = Scene();
    const Sphere s = Sphere(20, 0,0, 160);
    myS.SetSpheres({ s });
    myS.RenderScene();
    myS.ShowRender();
}
