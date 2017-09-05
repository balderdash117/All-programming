#include "theFirstProjApp.h"

int main() {
	
	auto app = new theFirstProjApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}