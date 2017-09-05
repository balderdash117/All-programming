////////////////////////////////////////////////////////////////////////////////////////
////																				////
////				NAME:	Asteroids Project										////		
////																				////		
////				PURPOSE:	This be main yo										////
////																				////
////				AUTHOR: Ben Alder 3/14/17	
////							With help from Jack B
////																				////
////////////////////////////////////////////////////////////////////////////////////////
#include "AsteroidsApp.h"
#include <time.h>

int main() {
	srand((unsigned int)time(NULL));
	auto app = new AsteroidsApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}