#include "GridApp.h"

int main() {
	
	auto app = new GridApp();
	app->run("AIE", 1376, 960, false);
	delete app;

	return 0;
}