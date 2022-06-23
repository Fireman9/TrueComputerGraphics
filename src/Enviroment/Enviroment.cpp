#include "Enviroment.h"

Enviroment::Enviroment(vector<string> mArg) {
	string tmp;
	bool find = false;
	setArg(mArg);
	tmp = findKey("--source=",&find);
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
	else setHeight(120);
	find = false;
	tmp = findKey("--w=", &find);
	if (find) setWidth(stoi(tmp));
	else setWidth(200);
}

OBJReader  Enviroment::readTriangles() {
	OBJReader objReader(input());
	objReader.read();
	return objReader;
}

Scene Enviroment::prepare() {

	//  OBJReader objReader = readTriangles();

	Screen screen(width(), height());
	//vector<Light*> light = { new DotLight(Point(2,2,2),Color::red()),new DotLight(Point(-2,-2,2),Color::green()), new DotLight(Point(0,3,0), Color::blue())};
	//vector<Light*> light = { new Light(Color::green(),0.005), new Light(Color::red(),0.01),new DotLight(Point(2,2,2),Color(255,0,255,255), 0.5) };
	//vector<Light*> light = { new DotLight(Point(2,2,2),Color(255,0,255,255), 0.7) };

	auto l1 = std::make_shared<DirectLight>(Vector(2, -4, -3), Color::white(), 0.4);
	auto l3 = std::make_shared<DotLight>(Point(-2, -4, -3), Color::white(), 0.7);
	auto l4 = std::make_shared<Light>(Color(255, 0, 255, 255), 0.03);
	auto l2 = std::make_shared<DotLight>(Point(4, -8, -4), Color::white(), 0.4);
	vector<std::shared_ptr<Light>> light;
	light.push_back(l2);
	light.push_back(l3);
	light.push_back(l4);
	Scene scene(screen, light, Point(0, 0, -10), 100);
	//Scene scene(screen, light, Point(0, 0, -5), 250);

	//  Matrix4x4 matrix = Matrix4x4::rotateX(-1.57) * Matrix4x4::rotateY(-0.735);
	//Matrix4x4 matrix = Matrix4x4::rotateX(-4.0) * Matrix4x4::rotateY(-1.235) * Matrix4x4::transpose(0, 0.3, 0);
	//Matrix4x4 matrix = Matrix4x4::rotateX(0) * Matrix4x4::rotateY(0);

	//  triangles = transformTriangles(matrix, objReader, Point(0,0,0));

	//  scene.setTriangles(triangles);
	Plane plane1({0, 1, 0}, 9);
	Plane plane2({0, 1, 0}, -3);
	Plane plane3({1, 0, 0}, -10);
	Plane plane4({1, 0, 0}, 10);
	Plane plane5({0, 0, 1}, -10);
	Sphere sphere1(1, {0, 2, 0});
	Sphere sphere2(2, {1, -10, 10}, Sphere::Mirror);

	scene.setSpheres({sphere1, sphere2});
	scene.setPlanes({plane1, plane2, plane3, plane4, plane5});

	return scene;
}

void Enviroment::writeTofile(Scene scene) {
	PPMWriter ppmWriter(arg);
	if (isTesting()) {
		this->tStart = clock();
		scene.renderScene();
		printf("Time taken for simple rendering: %.5fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
		const string out = "TEST_RENDER.ppm";
		ppmWriter.setFilepath(out);
		scene.writeRenderToPPM(ppmWriter);
	}
	ppmWriter.setFilepath(output());
	this->tStart = clock();
	Node* n = Node::createNode(triangles);
	scene.setTree(Node::createNode(triangles));
	printf("Time taken for tree creating: %.5fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	this->tStart = clock();
	scene.renderSceneTree();
	printf("Time taken for tree rendering: %.5fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	scene.writeRenderToPPM(ppmWriter);
}

void Enviroment::setArg(vector<string> mArg) {this->arg = mArg;}
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

string Enviroment::findKey(string ex, bool* find) {
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