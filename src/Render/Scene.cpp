#include "Scene.h"

Scene::Scene() {
	SetScreen(Screen());
	SetLight(Vector(2,-4,-3));
    spheres = {};
};
Scene::Scene(Screen S) {
	SetScreen(S);
	SetLight(Vector(2, -4, -3));
    spheres = {};
};
Scene::Scene(Screen S, Vector L) {
	SetScreen(S);
	SetLight(L);
    spheres = {};
};

void Scene::SetScreen(Screen S) { this->screen = S; };

void Scene::SetLight(Vector L) { L.normalize(); this->light = L; }
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
    for (int y = 0; y < this->screen.GetHeight(); y++) {
        for (int x = 0; x < this->screen.GetWidth(); x++) {
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
    if (x < 0) return ' ';
    else if (x < 0.2) return '.';
    else if (x < 0.5) return '*';
    else if (x < 0.8) return 'O';
    else return '#';
}

double Scene::Intersections(double& t, int x, int y) {
    double px = 0;
    Point intersectPoint;
    Point o = this->screen.GetStartPoint() + Point(x, y, 0);
    Vector d = Vector(this->screen.GetCamera(), o);
    d.normalize();
    const Ray ray(o, d);
    double min_t = 99999;
    for (int n = 0; n < spheres.size(); n++) {
        double h_px = SphereIntersec(spheres[n], ray, intersectPoint);
        t = intersectPoint.distanceTo(this->screen.GetCamera());
        if (min_t > t) { px = h_px; }
    }
    return px;
}

double Scene::SphereIntersec(Sphere sphere, Ray ray, Point& intersectPoint) {
    Sphere::Intersections ans = sphere.isRayIntersection(ray);
    double px = 0;
    Point first;
    Point sec;
    switch (ans)
    {
    case Sphere::NoIntersection:
        px = -1;
        return px;
        break;
    case Sphere::OnePointIntersection:
        intersectPoint = sphere.getOnePointRayIntersection(ray);
        break;
    case Sphere::TwoPointIntersection:
        first = sphere.getTwoPointRayIntersection(ray).first;
        sec = sphere.getTwoPointRayIntersection(ray).second;
        if (sec.distanceTo(this->screen.GetCamera()) > first.distanceTo(this->screen.GetCamera())) 
            intersectPoint = first;
        else intersectPoint = sec;
        break;
    }
    Vector norm = Vector(sphere.center(), intersectPoint);
    norm.normalize();
    px = norm.dotProduct(norm, this->light);

}