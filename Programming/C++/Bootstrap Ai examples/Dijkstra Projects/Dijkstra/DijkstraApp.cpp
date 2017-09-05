#include "DijkstraApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

DijkstraApp::DijkstraApp() {

}

DijkstraApp::~DijkstraApp() {

}

bool DijkstraApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_background = new aie::Texture("./textures/travel.png");

	travelMap = new SkyrimMap();
	setupLinks();

	return true;
}

void DijkstraApp::shutdown() {

	delete m_background;
	delete m_font;
	delete m_2dRenderer;
}

void DijkstraApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		Point mouse;
		input->getMouseXY(&mouse.x, &mouse.y);
		startCity = travelMap->findScreenCity(mouse);
	}
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT)) {
		Point mouse;
		input->getMouseXY(&mouse.x, &mouse.y);
		// find the closest start node within 200 pixels
		stopCity = travelMap->findScreenCity(mouse);
	}
}

void DijkstraApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	drawCityPathway(m_2dRenderer);
	// draw your stuff here!
	m_2dRenderer->drawSprite(m_background, (float)getWindowWidth() / 2, (float)getWindowHeight()/2, 0, 0, 0, 5.f);
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

//void DijkstraApp::setupLinks(SkyrimMap * travelMap)
void DijkstraApp::setupLinks()
{
	// create the map we had on the board
	travelMap->addCityTop("A", Point(0, 0), Point(260, 600));
	travelMap->addCityTop("B", Point(0, 1), Point(292, 420));
	travelMap->addCityTop("C", Point(0, 2), Point(283, 245));
	travelMap->addCityTop("D", Point(1, 1), Point(460, 470));
	travelMap->addCityTop("E", Point(1, 2), Point(433, 321));
	travelMap->addCityTop("F", Point(2, 1), Point(618, 440));
	travelMap->addCityTop("G", Point(2, 2), Point(620, 325));
	travelMap->addCityTop("H", Point(2, 3), Point(560, 220));
	travelMap->addCityTop("I", Point(3, 1), Point(757, 532));
	travelMap->addCityTop("J", Point(3, 2), Point(742, 293));
	travelMap->addCityTop("K", Point(4, 3), Point(840, 142));
#if 1
	travelMap->addPath("A", "B", 1);
	travelMap->addPath("A", "D", 1);
	//travelMap->addPath("A", "I", 7);
	travelMap->addPath("A", "I", 3);
	travelMap->addPath("B", "C", 2);
	travelMap->addPath("B", "E", 3);
	travelMap->addPath("C", "K", 2);
	//travelMap->addPath("C", "K", 7);
	travelMap->addPath("D", "E", 1);
	travelMap->addPath("D", "F", 1);
	travelMap->addPath("E", "D", 1);
	travelMap->addPath("E", "G", 1);
	travelMap->addPath("E", "H", 1);
	travelMap->addPath("F", "G", 1);
	travelMap->addPath("F", "I", 1);
	travelMap->addPath("F", "D", 1);
	travelMap->addPath("G", "F", 1);
	travelMap->addPath("G", "H", 1);
	travelMap->addPath("G", "J", 2);
	travelMap->addPath("H", "G", 1);
	travelMap->addPath("H", "J", 2);
	travelMap->addPath("I", "F", 1);
	travelMap->addPath("I", "K", 2);
	travelMap->addPath("J", "K", 1);
#else
	// and some random values
	travelMap->addPath("A", "B", rand() % 20 + 1);
	travelMap->addPath("A", "D", rand() % 20 + 1);
	travelMap->addPath("A", "I", rand() % 20 + 50);	// this one a bit larger to make this trek a little tough
	travelMap->addPath("B", "C", rand() % 20 + 1);
	travelMap->addPath("B", "E", rand() % 20 + 1);
	travelMap->addPath("C", "K", rand() % 20 + 1);
	travelMap->addPath("D", "E", rand() % 20 + 1);
	travelMap->addPath("D", "F", rand() % 20 + 1);
	travelMap->addPath("E", "D", rand() % 20 + 1);
	travelMap->addPath("E", "G", rand() % 20 + 1);
	travelMap->addPath("E", "H", rand() % 20 + 1);
	travelMap->addPath("F", "G", rand() % 20 + 1);
	travelMap->addPath("F", "I", rand() % 20 + 1);
	travelMap->addPath("F", "D", rand() % 20 + 1);
	travelMap->addPath("G", "F", rand() % 20 + 1);
	travelMap->addPath("G", "H", rand() % 20 + 1);
	travelMap->addPath("G", "J", rand() % 20 + 1);
	travelMap->addPath("H", "G", rand() % 20 + 1);
	travelMap->addPath("H", "J", rand() % 20 + 1);
	travelMap->addPath("I", "F", rand() % 20 + 1);
	travelMap->addPath("I", "K", rand() % 20 + 1);
	travelMap->addPath("J", "K", rand() % 20 + 1);
#endif
}

void DijkstraApp::renderCircle(aie::Renderer2D* p_2dRenderer, Point p_centre, float radius, unsigned int p_color, unsigned int sides)
{
	if (sides == 0)
	{
		sides = (unsigned int)(3.14*radius);
	}
	m_2dRenderer->setRenderColour(p_color);

	float d_a = (float)(3.14 * 2 / (float)sides),
		angle = d_a;

	float startX, startY, endX, endY;
	endX = radius;
	endY = 0.0f;
	endX = endX + p_centre.x;
	endY = endY + p_centre.y;
	for (int i = 0; i != sides; i++)
	{
		startX = endX;
		startY = endY;
		endX = cos(angle) * radius;
		endY = sin(angle) * radius;
		endX = endX + p_centre.x;
		endY = endY + p_centre.y;
		angle += d_a;
		m_2dRenderer->drawLine((float)startX, (float)startY, (float)endX, (float)endY, 2.f, 2.f);
	}
}

void DijkstraApp::drawCityPathway(aie::Renderer2D* p_2dRenderer)
{
	// draw the cities on the map
	if (startCity != nullptr) {
		Point pt = startCity->getPositionOnMap();

		renderCircle(p_2dRenderer, { pt.x + 2, pt.y - 2 }, 15, 0x000000ff, 30);
		renderCircle(p_2dRenderer, pt, 15, 0x00ff00ff, 30);
	}
	if (stopCity != nullptr) {
		Point pt = stopCity->getPositionOnMap();
		renderCircle(p_2dRenderer, { pt.x + 2, pt.y - 2 }, 15, 0x000000ff, 30);
		renderCircle(p_2dRenderer, pt, 15, 0xff0000ff, 30);
	}
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, 1.0f);

	if (startCity == nullptr || stopCity == nullptr) return;
	if (startCity == stopCity) return;

	// calculate only if this is a different path
	if (startCity != lastStartCity || stopCity != lastStopCity) {
		travelMap->reachableCities = travelMap->shortestPath(startCity->getName(), stopCity->getName());
		lastStartCity = startCity;
		lastStopCity = stopCity;
	}
	// and draw if needed
	if (travelMap->reachableCities == nullptr) return;

	// set color
	int pathCount = 0;
	Point bc(0, 0);
	for (auto cty : *travelMap->reachableCities) {
		Point ac = cty->getPositionOnMap();
		if (pathCount) {
			m_2dRenderer->setRenderColour(0.f, 0.f, 0.f, 1.0f);
			m_2dRenderer->drawLine((float)ac.x+2, (float)ac.y-2, (float)bc.x+2, (float)bc.y-2, 3.f);
			m_2dRenderer->setRenderColour(1.f, 1.f, 0.f, 1.0f);
			m_2dRenderer->drawLine((float)ac.x, (float)ac.y, (float)bc.x, (float)bc.y, 3.f);
		}
		bc = ac;
		pathCount++;
	}
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, 1.0f);
}
