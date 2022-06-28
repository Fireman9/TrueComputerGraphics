#include "Enviroment.h"

Enviroment::Enviroment(vector<string> mArg) {
	string tmp;
	bool find = false;
	setArg(mArg);
	tmp = findKey("--source=", &find);
	if (find) setInput(tmp);
	find = false;
	tmp = findKey("--output=", &find);
	if (find) setOut(tmp);
	find = false;
	tmp = findKey("--test", &find);
	if (find) setIsTesting(true);
	else setIsTesting(false);
	find = false;
	tmp = findKey("--h=", &find);
	if (find) setHeight(stoi(tmp));
	else setHeight(100);
	find = false;
	tmp = findKey("--w=", &find);
	if (find) setWidth(stoi(tmp));
	else setWidth(100);
}

OBJReader Enviroment::readTriangles() {
	OBJReader objReader(input());
	objReader.read();
	return objReader;
}

vector<Triangle> Enviroment::transformTriangles(Matrix4x4 matrix, vector<Triangle> triangles, Point start) {
	for (auto &triangle : triangles) {
		triangle = triangle.transform(matrix, start);
	}
	return triangles;
}

Scene Enviroment::prepare() {
	Screen screen (width(), height());
	auto l1 = std::make_shared<DirectLight>(Vector(2, -4, -3), Color::white(), 0.4);
	auto l3 = std::make_shared<DotLight>(Point(-2, -4, -3), Color::white(), 0.7);
	auto l4 = std::make_shared<Light>(Color(255, 255, 255, 255), 1.0);
	auto l2 = std::make_shared<DotLight>(Point(4, -8, -4), Color::white(), 0.4);
	vector<std::shared_ptr<Light>> light;
	//light.push_back(l2);
	light.push_back(l3);
	//light.push_back(l4);
	Scene scene(screen, light, Point(0, 0, -10), 100);
	
	Plane plane1({0, 1, 0}, 9);
	Plane plane2({0, 1, 0}, -3);
	Plane plane3({1, 0, 0}, -10);
	Plane plane4({1, 0, 0}, 10);
	Plane plane5({0, 0, 1}, -10);
	Sphere sphere1(2, {0, 0, 0});
	Triangle t1(Point(1,1,1),Point(2,2,1),Point(4,2,2));

	PPMReader ppmReader("earth.ppm");
	Texture earthTexture(ppmReader.read());
	sphere1.setTexture(earthTexture);
	Texture greenTexture(Color::green());
	Texture blueTexture(Color::blue());

	scene.setPlanes({plane1, plane2, plane3, plane4, plane5});
	//scene.setPlanes({plane2});
	scene.setTriangles({t1});
	scene.setSpheres({sphere1});

	return scene;
}

void Enviroment::writeTofile(Scene scene) {
	PPMWriter ppmWriter(arg);
	Clock clock;
	if (isTesting()) {
		clock.start();
		scene.renderScene();
		clock.stop();
		clock.printResultS("Time taken for simple rendering");
		ppmWriter.setFilepath("TEST_RENDER.ppm");
		RenderUtils::writeRenderToPPM(scene.getScreen(), ppmWriter);
	}
	ppmWriter.setFilepath(output());
	clock.start();
	scene.setTree(Node::createNode(triangles));
	clock.stop();
	clock.printResultMs("Time taken for tree creating");
	clock.start();
	scene.renderScene(scene.getTree());
	clock.stop();
	clock.printResultS("Time taken for tree rendering");

	RenderUtils::writeRenderToPPM(scene.getScreen(),ppmWriter);
}

void Enviroment::setArg(vector<string> mArg) { this->arg = mArg; }

void Enviroment::setInput(string inp) { this->inputfileName = inp; }

void Enviroment::setOut(string out) { this->outPutFileName = out; }

void Enviroment::setHeight(int px) { this->heightS = px; }

void Enviroment::setWidth(int px) { this->widthS = px; }

void Enviroment::setIsTesting(bool b) { this->isTestImg = b; }

string Enviroment::input() { return this->inputfileName; }

string Enviroment::output() { return this->outPutFileName; }

int Enviroment::height() { return this->heightS; }

int Enviroment::width() { return this->widthS; }

bool Enviroment::isTesting() { return this->isTestImg; }

string Enviroment::findKey(string ex, bool *find) {
	string tmp;
	for (auto argument : arg) {
		if (argument.find(ex) != std::string::npos) {
			*find = true;
			tmp = argument.erase(0, ex.length());
			break;
		}
	}
	return tmp;
}
