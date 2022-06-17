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

	Screen screen(400, 300);
	Scene scene(screen, Vector(0, -5, -20), Point(0, 0, -5), 2000);

	Matrix4x4 matrix = Matrix4x4::rotateX(-2.57) * Matrix4x4::rotateY(-1.735);
	vector<Triangle> triangles = objReader.getTriangles();
	for (auto& triangle : triangles) {
		triangle = triangle.transform(matrix, Point(0, 0, 0));
	}

	scene.setTriangles(triangles);
	
	Node* tree = new Node();

	std::cout << "Start tree" << endl;
	tree->setTriangles(triangles);
	std::cout << "End tree" << endl;

	scene.setTree(tree);
	scene.renderSceneTree();

	//scene.renderScene();
	scene.writeRenderToPPM(ppmWriter);
}
