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
    double** pxls = this -> screen.GetPixels();
    for (int y = 0; y < this->screen.GetHeight(); y++) {
        for (int x = 0; x < this->screen.GetWidth(); x++) {
            pxls[y][x] = Intersections(x, y);
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
    //if we want colored background
    if (x == -2) return '-';
    else 
        if (x < 0) return ' ';
    else if (x < 0.2) return '.';
    else if (x < 0.5) return '*';
    else if (x < 0.8) return 'O';
    else return '#';
}

double Scene::Intersections(int x, int y) {
    double px = -2, t = 0;
    Point intersectPoint;
    Point o = this->screen.GetStartPoint() + Point(x, y, 0);
    Vector d = Vector(this->screen.GetCamera(), o);
    d.normalize();
    const Ray ray(o, d);
    double min_t = 999999;
    for (int n = 0; n < spheres.size(); n++) {
        double h_px = SphereIntersec(spheres[n], ray, intersectPoint);
        t = intersectPoint.distanceTo(this->screen.GetCamera());
        if (Scene::isForward(intersectPoint, ray, this->screen.GetCamera()) && h_px != -2 && min_t > t) {
            px = h_px; min_t = t;
        }
    }
    return px;
}

bool Scene::isForward(Point& intersectPoint, Ray ray, Point camera) {
    Vector intersectDirection = Vector(camera, intersectPoint);
    intersectDirection.normalize();
    return Vector::dotProduct(intersectDirection, ray.direction()) > 0;
}

double Scene::SphereIntersec(Sphere sphere, Ray ray, Point& intersectPoint) {
    Sphere::Intersections ans = sphere.isRayIntersection(ray);
    double px = 0;
    Point first, sec;
    bool _f,_s;
    switch (ans)
    {
    case Sphere::NoIntersection:
        return -2;
        break;
    case Sphere::OnePointIntersection:
        intersectPoint = sphere.getOnePointRayIntersection(ray);
        break;
    case Sphere::TwoPointIntersection:
        first = sphere.getTwoPointRayIntersection(ray).first;
        sec = sphere.getTwoPointRayIntersection(ray).second;
        _f = Scene::isForward(first, ray, this->screen.GetCamera());
        _s = Scene::isForward(sec, ray, this->screen.GetCamera());
        if (!_f) {
            if (!_s) { return -2; }
            intersectPoint = sec;
        }
        else {
            if (!_s) intersectPoint = first;
            else {
                if (sec.distanceTo(this->screen.GetCamera()) > first.distanceTo(this->screen.GetCamera()))
                    intersectPoint = first;
                else intersectPoint = sec;
            }
        }
        break;
    default:
        return -2;
        break;
    }
    Vector norm = Vector(sphere.center(), intersectPoint);
    norm.normalize();
    px = Vector::dotProduct(norm, this->light);

}