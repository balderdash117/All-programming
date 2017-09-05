#include "theFirstProjApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

theFirstProjApp::theFirstProjApp() {

}

theFirstProjApp::~theFirstProjApp() {

}

bool theFirstProjApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	return true;
}

void theFirstProjApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void theFirstProjApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void theFirstProjApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", (float)getWindowWidth() - 18*18 + 10, 10);

	// done drawing sprites
	m_2dRenderer->end();
}