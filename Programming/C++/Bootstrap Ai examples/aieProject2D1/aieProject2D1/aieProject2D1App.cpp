#include "aieProject2D1App.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <stdio.h>

aieProject2D1App::aieProject2D1App() {

}

aieProject2D1App::~aieProject2D1App() {

}

bool aieProject2D1App::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	return true;
}

void aieProject2D1App::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void aieProject2D1App::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void aieProject2D1App::draw() {
	static double oldValue = 0;
	aie::Input* input = aie::Input::getInstance();

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	m_2dRenderer->setRenderColour(1.f, 0.f, 0.f, 0.5f);
	double scroll = input->getMouseScroll();
	char tempStr[256];
	sprintf_s(tempStr, "Scroll value = %.2f", oldValue);
	m_2dRenderer->drawText(m_font, tempStr, 100, 100);

	if (scroll != oldValue) {
		oldValue = scroll;
	}
	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, 1.0f);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}