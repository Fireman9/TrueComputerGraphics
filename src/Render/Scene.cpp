#include "Scene.h"

Scene::Scene() {
	SetScreen(Screen());
	SetLight(Vector(0,0,-1));
    spheres = {};
};
Scene::Scene(Screen S) {
	SetScreen(S);
	SetLight(Vector(0, 0, -1));
    spheres = {};
};
Scene::Scene(Screen S, Vector L) {
	SetScreen(S);
	SetLight(L);
    spheres = {};
};

void Scene::SetScreen(Screen S) { this->screen = S; };

void Scene::SetLight(Vector L) { this->light = L; }
void Scene::ChangeLight(Vector L) {
	SetLight(L);
	RenderScene();
};

void Scene::SetSpheres(vector<Sphere> s) { this->spheres = s; };
void Scene::AddNewSphere(Sphere s) { this->spheres.push_back(s); };
void Scene::AddNewSphere(vector<Sphere> s) { this->spheres.insert(spheres.end(), s.begin(), s.end()); };

void Scene::RenderScene() {
    double t;
    double** pxls = this -> screen.GetPixels();
    for (int y = 0; y < this->screen.GetHeight(); ++y) {
        for (int x = 0; x < this->screen.GetWidth(); ++x) {
            pxls[y][x] = Intersections(t, x, y);
        }
    }
};

void Scene::ShowRender() {
    int H = this->screen.GetHeight();
    int W = this->screen.GetWidth();
    double** pixels = this->screen.GetPixels();
    for (int y = 0; y < W + 1; y++) cout << "--";
    cout << endl;
    for (int y = 0; y < H; y++) {
        cout << '|';
        for (int x = 0; x < W; x++) {
            cout << GetSymbool(pixels[y][x]) << ' ';
        }
        cout << '|' << endl;
    }
    for (int y = 0; y < W + 1; y++) cout << "--";
    cout << endl;
}

char Scene::GetSymbool(double x) {
    return '#' ? x == 1 : ' ';
}

double Scene::Intersections(double& t, int x, int y) {
    double px = 0;
    Point o = this->screen.GetStartPoint() + Point(x, y, 0);
    Vector d = Vector(this->screen.GetCamera(), o);
    d.normalize();
    const Ray ray(o, d);
    for (int n = 0; n < spheres.size(); n++) {
        if (spheres[n].isRayIntersection(ray)!=spheres[n].NoIntersection) {
            px = 1;
        }
    }
    return px;
}