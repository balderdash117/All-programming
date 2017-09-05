#include "AI_ProjectApp.h"

int main() {
	
	auto app = new AI_ProjectApp();
	app->run("Game Project", 1600, 1268, false);
	delete app;

	return 0;
}