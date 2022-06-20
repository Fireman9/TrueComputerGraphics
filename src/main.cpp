#include "Render/Scene.h"
#include "Geometry/Shapes/Sphere.h"
#include "File/OBJReader.h"
#include "Matrix/Matrix4x4.h"
#include "File/PPMWriter.h"
#include "Tree/Node.h"

int main(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);
	OBJReader objReader(arguments);
	objReader.read();

	PPMWriter ppmWriter(arguments);

	//Screen screen(720, 480);
	Screen screen(400, 240);
	Scene scene(screen, Vector(0, -5, -20), Point(0, 0, -5), 250);

	//Matrix4x4 matrix = Matrix4x4::rotateX(-1.57) * Matrix4x4::rotateY(-0.735);
	Matrix4x4 matrix = Matrix4x4::rotateX(-4.0) * Matrix4x4::rotateY(-1.235) * Matrix4x4::transpose(0,0.3,0);
	//Matrix4x4 matrix = Matrix4x4::rotateX(0) * Matrix4x4::rotateY(0);
	vector<Triangle> triangles = objReader.getTriangles();
	for (auto& triangle : triangles) {
		triangle = triangle.transform(matrix, Point(0, 0, 0));
	}

	scene.setTriangles(triangles);

	std::cout << "Start create tree" << endl;
	scene.setTree(Node::createNode(triangles));
	std::cout << "End create tree" << endl;

	std::cout << "Start render tree" << endl;
	scene.renderSceneTree();
	std::cout << "End render tree" << endl;

	//scene.renderScene();
	scene.writeRenderToPPM(ppmWriter);
}
