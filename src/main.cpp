#include "Render/Scene.h"
#include "Geometry/Shapes/Sphere.h"
#include "File/OBJReader.h"
#include "Matrix/Matrix4x4.h"
#include "File/PPMWriter.h"
#include "Tree/Node.h"
#include "Enviroment/Enviroment.h"

int main(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);
	Enviroment env(arguments);
	Scene s = env.prepare();
	env.writeTofile(s);
}
