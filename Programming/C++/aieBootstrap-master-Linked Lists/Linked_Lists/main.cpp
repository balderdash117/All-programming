#include "Linked_ListsApp.h"

int main() {
	
	auto app = new Linked_ListsApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}