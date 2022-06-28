#include "Render/Scene.h"
#include "File/OBJReader.h"
#include "Matrix/Matrix4x4.h"
#include "Enviroment/Environment.h"

int main(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);
	Environment env(arguments);
//	env.setIsTesting(true);
	Scene s = env.prepare();
	env.writeTofile(s);
}
