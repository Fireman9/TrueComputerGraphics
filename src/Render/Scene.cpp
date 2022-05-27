#include "Scene.h"

Scene::Scene() {
	setScreen(Screen());
	setLight(Vector(2,-4,-3));
    spheres = {};
    triangles = {};
    planes = {};
};
Scene::Scene(Screen s) {
	setScreen(s);
	setLight(Vector(2, -4, -3));
    spheres = {};
    triangles = {};
    planes = {};
};
Scene::Scene(Screen s, Vector l) {
	setScreen(s);
	setLight(l);
    spheres = {};
    triangles = {};
    planes = {};
};

void Scene::setScreen(Screen s) { this->screen = s; };

void Scene::setLight(Vector l) { l.normalize(); this->light = l; }
void Scene::changeLight(Vector l) {
	setLight(l);
	renderScene();
};

void Scene::setSpheres(vector<Sphere> s) { this->spheres = s; };
void Scene::addNewSphere(Sphere s) { this->spheres.push_back(s); };
void Scene::addNewSphere(vector<Sphere> s) { this->spheres.insert(spheres.end(), s.begin(), s.end()); };

void Scene::setTriangles(vector<Triangle> t) { this->triangles = t; };
void Scene::addNewTriangle(Triangle t) { this->triangles.push_back(t); };
void Scene::addNewTriangle(vector<Triangle> t) { this->triangles.insert(triangles.end(), t.begin(), t.end()); };

void Scene::setPlanes(vector<Plane> p) { this->planes = p; };
void Scene::addNewPlane(Plane p) { this->planes.push_back(p); };
void Scene::addNewPlane(vector<Plane> p) { this->planes.insert(planes.end(), p.begin(), p.end()); };

void Scene::renderScene() {
    vector<vector<double>> pxls = {};
    Point intersectPoint;
    for (int y = 0; y < this->screen.getHeight(); y++) {
        vector<double> h = {};
        for (int x = 0; x < this->screen.getWidth(); x++) {
            // or for 1d vector
            // pxls.pupush_back(intersections(x*this->screen.getCoordPerPixel(), y * this->screen.getCoordPerPixel(), intersectPoint));
            // x,y coordinate than pxlr[y*screen.getWeight()+x]
            h.push_back(intersections(x*this->screen.getCoordPerPixel(), y * this->screen.getCoordPerPixel(), intersectPoint));
        }
        pxls.push_back(h);
    }
    screen.setPixels(pxls);
};

void Scene::showRender() {
    int H = this->screen.getHeight();
    int W = this->screen.getWidth();
    vector<vector<double>> pixels = this->screen.getPixels();
    for (int y = 0; y < W + 1; y++) cout << "--";
    cout << endl;

    for (int y = 0; y < H; y++) {
        cout << '|';
        for (int x = 0; x < W; x++) {
            cout << getSymbool(pixels[y][x]) << ' ';
        }
        cout << '|' << endl;
    }
    for (int y = 0; y < W + 1; y++) cout << "--";
    cout << endl;
}

char Scene::getSymbool(double x) {
    //if we want colored background
    if (x == -2) return '.';
    else 
        if (x < 0) return ' ';
    else if (x < 0.2) return '-';
    else if (x < 0.5) return '*';
    else if (x < 0.8) return 'O';
    else return '#';
}

double Scene::intersections(double x, double y, Point& intersection) {
    Point intersectPoint;
    double px = -2, t = 0;
    Point o = this->screen.getStartPoint() + Point(x, y, 0);
    Vector d = Vector(this->screen.getCamera(), o);
    d.normalize();
    const Ray ray(o, d);
    double min_t = 999999;
    for (int n = 0; n < spheres.size(); n++) {
        double h_px = sphereIntersec(spheres[n], ray, intersectPoint);
        t = intersectPoint.distanceTo(this->screen.getCamera());
        if (Scene::isForward(intersectPoint, ray, this->screen.getCamera()) && h_px != -2 && min_t > t) {
            px = h_px; min_t = t; intersection = intersectPoint;
        }
    }
    for (int n = 0; n < planes.size(); n++) {
        double h_px = planeIntersec(planes[n], ray, intersectPoint);
        t = intersectPoint.distanceTo(this->screen.getCamera());
        if (Scene::isForward(intersectPoint, ray, this->screen.getCamera()) && h_px != -2 && min_t > t) {
            px = h_px; min_t = t; intersection = intersectPoint;
        }
    }
    for (int n = 0; n < triangles.size(); n++) {
        double h_px = triangleIntersec(triangles[n], ray, intersectPoint);
        t = intersectPoint.distanceTo(this->screen.getCamera());
        if (h_px != -2 && min_t > t) {
            px = h_px; min_t = t; intersection = intersectPoint;
        }
    }
    return px;
}

bool Scene::isForward(Point& intersectPoint, Ray ray, Point camera) {
    Vector intersectDirection = Vector(camera, intersectPoint);
    intersectDirection.normalize();
    return Vector::dotProduct(intersectDirection, ray.direction()) > 0;
}

double Scene::sphereIntersec(Sphere sphere, Ray ray, Point& intersectPoint) {
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
        _f = Scene::isForward(first, ray, this->screen.getCamera());
        _s = Scene::isForward(sec, ray, this->screen.getCamera());
        if (!_f) {
            if (!_s) { return -2; }
            intersectPoint = sec;
        }
        else {
            if (!_s) intersectPoint = first;
            else {
                if (sec.distanceTo(this->screen.getCamera()) > first.distanceTo(this->screen.getCamera()))
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

double Scene::planeIntersec(Plane plane, Ray ray, Point& intersectPoint) {
    double px = -2;
    if (plane.getRayIntersection(ray, intersectPoint)) {
        Vector norm = plane.getNormal();
        norm.normalize();
            if (!isFaced(norm, ray.direction())) { norm = norm * -1; }
        px = Vector::dotProduct(norm, this->light);
    };
    return px;
}

double Scene::triangleIntersec(Triangle triangle, Ray ray, Point& intersectPoint) {
    double px = -2;
    if (triangle.getRayIntersection(ray, intersectPoint)) {
        Vector v0v1 = Vector(triangle.v0(), triangle.v1());
        Vector v0v2 = Vector(triangle.v0(), triangle.v2());
        Vector norm = Vector::crossProduct(v0v1, v0v2);
        norm.normalize();
            if (!isFaced(norm, ray.direction())) { norm = norm * -1; }
        px = Vector::dotProduct(norm, this->light);
    };
    return px;
}

bool Scene::isFaced(Vector normal, Vector direction) {
    if (Vector::dotProduct(normal, direction) < 0) return true;
    else return false;
}