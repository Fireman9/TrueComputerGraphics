#include "Render/Scene.h"
#include "Geometry/Shapes/Sphere.h"
#include "File/OBJReader.h"
#include "Matrix/Matrix4x4.h"
#include "File/PPMWriter.h"

int main(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);
	OBJReader objReader(arguments);
	objReader.read();

	PPMWriter ppmWriter(arguments);

	Screen screen(852, 480);
	Scene scene(screen, Vector(0, -5, -20), Point(0, 0, -5), 3000);

	Matrix4x4 matrix = Matrix4x4::rotateX(-1.57) * Matrix4x4::rotateY(-0.735);
	vector<Triangle> triangles = objReader.getTriangles();
	for (auto &triangle : triangles) {
		triangle = triangle.transform(matrix, Point(0, 0, 0));
	}
	scene.setTriangles(triangles);

	scene.renderScene();
	scene.writeRenderToPPM(ppmWriter);
}
