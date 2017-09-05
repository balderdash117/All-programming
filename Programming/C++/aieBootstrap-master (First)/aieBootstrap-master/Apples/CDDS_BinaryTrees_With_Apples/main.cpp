#include "CDDS_BinaryTreesApp.h"
#include <time.h>

int main() {
	
	srand((unsigned int) time(NULL));

	auto app = new CDDS_BinaryTreesApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}