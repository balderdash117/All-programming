#include "IntroductionApp.h"
#include "Font.h"
#include "Input.h"

IntroductionApp::IntroductionApp() {

}

IntroductionApp::~IntroductionApp() {

}

bool IntroductionApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_keyboardBehaviour.setSpeed(400);

	m_followBehaviour.setSpeed(100);
	m_followBehaviour.setTarget(&m_player);

	m_player.setPosition(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f);

	m_player.addBehaviour(&m_keyboardBehaviour);
	m_enemy.addBehaviour(&m_followBehaviour);

	return true;
}

void IntroductionApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void IntroductionApp::update(float deltaTime) {

	m_player.update(deltaTime);
	m_enemy.update(deltaTime);

	// exit the application
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void IntroductionApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	float x = 0, y = 0;

	// draw player as a green circle
	m_player.getPosition(&x, &y);
	m_2dRenderer->setRenderColour(0, 1, 0);
	m_2dRenderer->drawCircle(x, y, 10);

	// draw enemy as a red circle
	m_enemy.getPosition(&x, &y);
	m_2dRenderer->setRenderColour(1, 0, 0);
	m_2dRenderer->drawCircle(x, y, 10);

	// draw some text
	m_2dRenderer->setRenderColour(1, 1, 0);
	m_2dRenderer->drawText(m_font, "Use arrows for movement", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

// keyboard behaviour
eBehaviourResult KeyboardBehaviour::execute(GameObject* gameObject, float deltaTime) {

	float x = 0, y = 0;

	// get access to input
	aie::Input* input = aie::Input::getInstance();

	// determine direction to move
	if (input->isKeyDown(aie::INPUT_KEY_UP))
		y += 1;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		y -= 1;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		x -= 1;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		x += 1;

	// we need to adjust the direction when heading diagonally
	float magnitude = sqrt(x * x + y * y);
	if (magnitude > 0) {
		x /= magnitude;
		y /= magnitude;
	}

	// apply the movement based on speed and delta time
	gameObject->translate(x * m_speed * deltaTime, y * m_speed * deltaTime);

	return eBehaviourResult::SUCCESS;
}

// execute follow behaviour
eBehaviourResult FollowBehaviour::execute(GameObject* gameObject, float deltaTime) {

	if (m_target == nullptr)
		return eBehaviourResult::FAILURE;

	// get target position
	float tx = 0, ty = 0;
	m_target->getPosition(&tx, &ty);

	// get my position
	float x = 0, y = 0;
	gameObject->getPosition(&x, &y);

	// compare the two and get the distance between them
	float xDiff = tx - x;
	float yDiff = ty - y;
	float distance = sqrtf(xDiff * xDiff + yDiff * yDiff);

	// if not at the target then move towards them
	if (distance > 0) {

		// need to make the difference the length of 1
		// this is so movement can be "pixels per second"
		xDiff /= distance;
		yDiff /= distance;

		// move to target (can overshoot!)
		gameObject->translate(xDiff * m_speed * deltaTime, yDiff * m_speed * deltaTime);
	}

	return eBehaviourResult::SUCCESS;
}