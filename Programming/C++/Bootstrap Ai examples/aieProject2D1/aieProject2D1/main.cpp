#include "aieProject2D1App.h"

int main() {
	
	auto app = new aieProject2D1App();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}