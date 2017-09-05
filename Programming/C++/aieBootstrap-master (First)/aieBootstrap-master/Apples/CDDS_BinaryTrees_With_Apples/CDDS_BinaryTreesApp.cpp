#include "CDDS_BinaryTreesApp.h"
#include "Font.h"
#include "Input.h"
#include <imgui.h>
#include <algorithm>

namespace aie {
	class Texture;
}

aie::Font* g_systemFont = nullptr;
aie::Font* g_systemFont2 = nullptr;

CDDS_BinaryTreesApp::CDDS_BinaryTreesApp() {

}

CDDS_BinaryTreesApp::~CDDS_BinaryTreesApp() {

}


bool CDDS_BinaryTreesApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	g_systemFont = new aie::Font("./font/consolas.ttf", 32);
	g_systemFont2 = new aie::Font("./font/consolas.ttf", 20);
	m_appleTex = new aie::Texture("./textures/Apple.png");
	m_explosionTex = new aie::Texture("./textures/explosion.png");
	// interval for the apples to arrive
	mTimeInterval = 3.0f;

	return true;
}

void CDDS_BinaryTreesApp::shutdown() {

	delete m_explosionTex;
	delete m_appleTex;
	delete g_systemFont;
	delete g_systemFont2;
	delete m_2dRenderer;
}

void CDDS_BinaryTreesApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
#if 0
	static int value = 0;
	ImGui::InputInt("Value", &value);

	if (ImGui::Button("Insert", ImVec2(50, 0)) )
	{
		m_binaryTree.insert(value);
		m_selectedNode = m_binaryTree.find(value);
	}

	if (ImGui::Button("Remove", ImVec2(50, 0)))
	{
		m_binaryTree.remove(value);
	}
	 
	if (ImGui::Button("Find", ImVec2(50, 0)))
	{
		m_selectedNode = m_binaryTree.find(value);
	}
#endif

	for (vector <explosion>::iterator it = m_explosions.begin(); it != m_explosions.end(); ) {
		it->mTimer += deltaTime;
		if (it->mTimer >= EXPLOSION_SWITCH) {
			it->mIndex++;
			it->mTimer = 0;
			if (it->mIndex >= MAX_EXPLOSION_COUNT) {
				it = m_explosions.erase(it);
				continue;
			} 
		}
		++it;
	}

	// do we create apples
	testCreateAnotherApple(deltaTime);

	// update all our apples
	for (auto it = m_apple.begin(); it != m_apple.end(); ++it) {
		appleUpdate(it, deltaTime);
	}

	// if the apples are below the screen then erase them
	for (auto it = m_apple.begin(); it != m_apple.end(); ) {
		if (it->mPos.y <= 0) {
			it = m_apple.erase(it);
		} else {
			++it;
		}
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void CDDS_BinaryTreesApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_binaryTree.draw(m_2dRenderer, m_selectedNode);

	// draw all the apples on the screen
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	for (auto it = m_apple.begin(); it != m_apple.end(); ++it) {
		std::string str = std::to_string(it->mNumber);
		float width = m_2dRenderer->measureTextWidth(g_systemFont2, str.c_str());

		// centre the text total width is 100 at the moment or mScale*2
		float startX = it->mPos.x - width/2 - 4;
		m_2dRenderer->setRenderColour(it->mColor);
		m_2dRenderer->drawSprite(m_appleTex, it->mPos.x, it->mPos.y, it->mScale, it->mScale, 0, 5.f);
		m_2dRenderer->setRenderColour(0, 0, 0, 1);
		m_2dRenderer->drawText(g_systemFont2, str.c_str(), startX, it->mPos.y - 10, 5.f);
		m_2dRenderer->setRenderColour(1, 0, 0, 1);
		m_2dRenderer->drawText(g_systemFont2, str.c_str(), startX+2, it->mPos.y - 8, 5.f);
	}

	// are there explosions
	m_2dRenderer->setRenderColour(WHITE);
	for (auto it = m_explosions.begin(); it != m_explosions.end(); ++it) {
		if (it->mIndex >= MAX_EXPLOSION_COUNT) continue;
		float scale = 0.4f;
		m_2dRenderer->setUVRect(it->mArray[it->mIndex].x / it->mWidth, it->mArray[it->mIndex].y / it->mHeight, it->mArray[it->mIndex].w / it->mWidth, it->mArray[it->mIndex].h / it->mHeight);
		m_2dRenderer->drawSprite(m_explosionTex, it->mPos.x, it->mPos.y, it->mArray[it->mIndex].w*scale, it->mArray[it->mIndex].h*scale, 0, 6.f);
	}
	// reset UV mask
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	// output some text
	//std::string str = std::to_string(m_explosions.size());
	//m_2dRenderer->drawText(g_systemFont, str.c_str(), 0, 0);

	m_2dRenderer->drawText(g_systemFont, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void CDDS_BinaryTreesApp::testCreateAnotherApple(float a_deltaTime)
{
	static float currentTime, stopCreateTime;
	currentTime += a_deltaTime;
	const float decreaseInterval = 2.0f;
	static float addTime;

	addTime += a_deltaTime;
	if (addTime > decreaseInterval) {
		addTime = 0;
		// left over from the asteroid days!!
		// and lower the time till the next asteroid by 0.5f
		////mTimeInterval = std::max(0.2f, mTimeInterval - 0.2f);
	}

	// left over from the asteroid days!!
	//// have we hit the ball
	//if (distance(mPlayer.mCurrentXPos, mPlayer.mCurrentYPos, mBall.mBallXPos, mBall.mBallYPos) <= mPlayer.mRadius + mBall.mRadius) {
	//	// players radius drops a bit
	//	mPlayer.mRadius = std::max(mBall.mRadius, mPlayer.mRadius - 1.0f);
	//	// and speeds up
	//	mPlayer.mSpeed += 12.f;
	//	if (mPlayer.mRadius != mBall.mRadius) {
	//		// asteroids can come in slightly delayed
	//		//mTimeInterval += 0.6f;
	//	}
	//	// ball is flagged as out of play
	//	mBall.mBallXPos = mBall.mBallYPos = -1.0f;
	//	mScore += 1;
	//	stopCreateTime = 1.0f;
	//}

	stopCreateTime = std::max(0.f, stopCreateTime - a_deltaTime);
	if (stopCreateTime) return;

	if (currentTime >= mTimeInterval) {
		Apples cmt;
		cmt.mPos.x = (float)(rand() % (getWindowWidth() - 50) + 25);
		cmt.mPos.y = (float)getWindowHeight();
		cmt.mAsteroidActive = true;
		cmt.mSpeed = (float)(rand() % 400 + 50);
		cmt.mScale = 50.0f;
		cmt.mNumber = rand() % (30) + 1;
		int colorForSpeed = (int)(cmt.mSpeed / 100);
		switch (colorForSpeed) {
		case 4:	cmt.mColor = WHITE; break;
		case 3:	cmt.mColor = YELLOW; break;
		case 2:	cmt.mColor = ORANGE; break;
		case 1:	cmt.mColor = RED; break;
		default:	cmt.mColor = WHITE; break;
		}
		// and another apple to the vector
		m_apple.push_back(cmt);
		currentTime = 0;
	}
}

float CDDS_BinaryTreesApp::distance(Vector3 a_posOne, Vector3 a_posTwo)
{
	return sqrtf((a_posOne.x - a_posTwo.x)*(a_posOne.x - a_posTwo.x) + (a_posOne.y - a_posTwo.y)*(a_posOne.y - a_posTwo.y));
}

void CDDS_BinaryTreesApp::appleUpdate(std::vector<Apples>::iterator a_apple, float a_deltaTime)
{
	float oldx = a_apple->mPos.x, oldy = a_apple->mPos.y;

	// coming down
	a_apple->mPos.y -= a_apple->mSpeed*a_deltaTime;

	// left over from the asteroid days!!
	// have we hit the player
	//if (distance(mPlayer.mCurrentXPos, mPlayer.mCurrentYPos, a_apple->mPos.x, a_apple->mPos.y) <= mPlayer.mRadius + a_ast->mRadius)
	//	mGameIsOver = true;

	// asteroid has come to the ground (bottom)
	if (a_apple->mPos.y <= 0) {
		a_apple->mAsteroidActive = false;
		if (m_binaryTree.find(a_apple->mNumber) == nullptr) {
			m_binaryTree.insert(a_apple->mNumber);
			return;
		}
		m_binaryTree.remove(a_apple->mNumber);

		// and signal that the removal has taken place
		explosion exp;
		exp.mPos.x = a_apple->mPos.x;
		exp.mPos.y = a_apple->mPos.y +12;
		exp.mIndex = 0;
		exp.mTimer = 0;
		// and another apple to the vector
		m_explosions.push_back(exp);
	}
}

