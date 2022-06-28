#include "Render/Scene.h"
#include "File/OBJReader.h"
#include "Matrix/Matrix4x4.h"
#include "Enviroment/Enviroment.h"

int main(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);
	Enviroment env(arguments);
//	env.setIsTesting(true);
	Scene s = env.prepare();
	env.writeTofile(s);
}
