#include "DijkstraApp.h"

int main() {
	
	auto app = new DijkstraApp();
	app->run("AIE", 1024, 768, false);
	delete app;

	return 0;
}