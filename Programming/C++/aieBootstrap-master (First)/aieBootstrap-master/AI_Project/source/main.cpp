#include "AI_ProjectApp.h"

int main() {
	
	auto app = new AI_ProjectApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}