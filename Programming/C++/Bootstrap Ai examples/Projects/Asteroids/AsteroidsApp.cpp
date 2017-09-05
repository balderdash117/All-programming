////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									
////		Name:		Bootstrap asteroids															
////																									
////		Purpose:	Asteroids routines																	
////																									
////		Author:		Roger Keating 20170311 																	
////																									
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "AsteroidsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

// constructor
AsteroidsApp::AsteroidsApp() {
	mAst.clear();
	mGameIsOver = false;
	mTimeInterval = 3.0f;
	mScore = 0;
	mPlayer.mCurrentXPos = 0.f;
	mPlayer.mCurrentYPos = 0.f;
	mPlayer.mRadius = 25.f;
	mPlayer.mSpeed = 100.f;
	mBall.mBallXPos = mBall.mBallYPos = -1.f;
	mBall.mRadius = 10.0f;
	m_foo = 1;
	m_pfoo = &m_foo;

}

// on startup will be accessed once
bool AsteroidsApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	mPlayer.mCurrentXPos = (float)getWindowWidth() / 2;
	mPlayer.mCurrentYPos = (float)getWindowHeight() / 2;
	int num = 1;


	// set up ball
	placeBallInPlay();
	mTimer = 0;
	return true;
}

// on shutdown will be accessed once
void AsteroidsApp::shutdown() {
	//delete m_texture;
	//delete m_playerTexture;
	delete m_font;
	delete m_2dRenderer;
}

void AsteroidsApp::myFoo(int& num) {
	std::cout << num << std::endl;
	int value = num;
	std::cout << value << std::endl;
	system("pause");

}

// if the ball is not in play place it in play
void AsteroidsApp::placeBallInPlay()
{
	// initialize
	mBall.mBallXPos = mBall.mBallYPos = -1.f;
	// size

	while (true) {
		float x = (float) (rand() % (getWindowWidth()  - 40) + 20);
		float y = (float) (rand() % (getWindowHeight() - 40) + 20);

		// not on the player
		if (distance(mPlayer.mCurrentXPos, mPlayer.mCurrentYPos, x, y) < mPlayer.mRadius+20) continue;

		// not on the asteroids 
		bool areaOk = true;
		for (unsigned int k = 0; k < mAst.size(); ++k) {
			if ((distance(mAst[k].mX, mAst[k].mY, x, y) < mAst[k].mRadius+10)) areaOk = false;
		}

		// is this spot ok
		if (!areaOk) continue;

		mBall.mBallXPos = x;
		mBall.mBallYPos = y;
		break;
	}
}

// sort ... because a sort routine is required
void AsteroidsApp::sortAsteroids()
{
	// this ais a 'Lamda'  sort, the third parameter is a function
	std::sort(mAst.begin(), mAst.end(), [](Comet const& a, Comet const& b) { return a.mY < b.mY; });
}

// distance between (x1, y1) and (x2, y2)
float AsteroidsApp::distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

// called at 60 fps (aprrox)
void AsteroidsApp::update(float deltaTime) {

	aie::Input* input = aie::Input::getInstance();
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (mGameIsOver) return;

	mTimer += deltaTime;
	// input example

	if (mBall.mBallXPos == -1) {
		placeBallInPlay();
	}

	// do we create asteroids
	testCreateAsteroid(deltaTime);

	// required sort
	sortAsteroids();

	for (unsigned int i = 0; i < mAst.size(); ++i) {
		asteroidUpdate(&mAst[i], deltaTime);
	}
	// now erase all non active asteroids
	for (unsigned int k = mAst.size(); k--; ) {
		if (mAst[k].mAsteroidActive) continue;
		mAst.erase(mAst.begin() + k);
	}
	// player input instructions
	if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_LEFT))
		mPlayer.mCurrentXPos -= mPlayer.mSpeed*deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_D) || input->isKeyDown(aie::INPUT_KEY_RIGHT))
		mPlayer.mCurrentXPos += mPlayer.mSpeed*deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_UP))
		mPlayer.mCurrentYPos += mPlayer.mSpeed*deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_S) || input->isKeyDown(aie::INPUT_KEY_DOWN))
		mPlayer.mCurrentYPos -= mPlayer.mSpeed*deltaTime;
}

// draw the screen
void AsteroidsApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	getWindowWidth();
	
	// begin drawing sprites
	m_2dRenderer->begin();

	// the ball
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, 1.f);
	m_2dRenderer->drawCircle(mBall.mBallXPos, mBall.mBallYPos, mBall.mRadius, 0.0f);

	// the asteroids
	for (unsigned int k = 0; k < mAst.size(); ++k) {
		m_2dRenderer->setRenderColour(mAst[k].mColor);
		m_2dRenderer->drawCircle(mAst[k].mX, mAst[k].mY, mAst[k].mRadius, 0.0f);
	}

	// the player
	m_2dRenderer->setRenderColour(0.f, 1.f, 1.f, 1.f);
	m_2dRenderer->drawCircle(mPlayer.mCurrentXPos, mPlayer.mCurrentYPos, mPlayer.mRadius, 0.0f);

	//mScore = mTimeInterval;
	if (mGameIsOver) {
		// output some text, uses the last used colour
		m_2dRenderer->setRenderColour(1.f, 1.f, 0.f, 1.f);
		std::ostringstream os;
		os << "Game Over :: Press ESC to quit";
		if (mScore) os << " [ " << mScore << " ]";
		m_2dRenderer->drawText(m_font, os.str().c_str(), 10, 10);
	} else {
		// output some text, uses the last used colour
		m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, 0.4f);
		std::ostringstream os;
		os << "Press ESC to quit";
		if (mScore) os << " [ " << mScore << " ]";
		m_2dRenderer->drawText(m_font, os.str().c_str(), 10, 10);
	}

	// done drawing sprites
	m_2dRenderer->end();
}

// do we create asteroids (and do we hit the ball and claim a score)
void AsteroidsApp::testCreateAsteroid(float a_deltaTime)
{
	static float currentTime, stopCreateTime;
	currentTime += a_deltaTime;
	const float decreaseInterval = 2.0f;
	static float addTime;

	addTime += a_deltaTime;
	if (addTime > decreaseInterval) {
		addTime = 0;
		// and lower the time till the next asteroid by 0.5f
		mTimeInterval = std::max(0.2f, mTimeInterval - 0.2f);
	}
	// have we hit the ball
	if (distance(mPlayer.mCurrentXPos, mPlayer.mCurrentYPos, mBall.mBallXPos, mBall.mBallYPos) <= mPlayer.mRadius + mBall.mRadius) {
		// players radius drops a bit
		mPlayer.mRadius = std::max(mBall.mRadius, mPlayer.mRadius - 1.0f);
		// and speeds up
		mPlayer.mSpeed += 12.f;
		if (mPlayer.mRadius != mBall.mRadius) {
			// asteroids can come in slightly delayed
			//mTimeInterval += 0.6f;
		}
		// ball is flagged as out of play
		mBall.mBallXPos = mBall.mBallYPos = -1.0f;
		mScore += 1;
		stopCreateTime = 1.0f;
	}

	stopCreateTime = std::max(0.f, stopCreateTime - a_deltaTime);
	if (stopCreateTime) return;

	if (currentTime >= mTimeInterval) {
		Comet cmt;
		cmt.mX = (float)(rand() % (getWindowWidth() - 50) + 25);
		cmt.mY = (float)getWindowHeight();
		cmt.mAsteroidActive = true;
		cmt.mSpeed = (float) (rand() % 400 + 50);
		int colorForSpeed = (int)(cmt.mSpeed / 100);
		switch (colorForSpeed) {
		case 4:	cmt.mColor = PURPLE; break;
		case 3:	cmt.mColor = YELLOW; break;
		case 2:	cmt.mColor = ORANGE; break;
		case 1:	cmt.mColor = RED; break;
		default:	cmt.mColor = DK_RED; break;
		}

		//if (cmt.mSpeed > 350)		cmt.mColor = YELLOW;
		//else if (cmt.mSpeed > 275)	cmt.mColor = ORANGE;
		//else if (cmt.mSpeed > 175)	cmt.mColor = RED;
		//else						cmt.mColor = DK_RED;
		// size
		cmt.mRadius = 5.0f;
		// and another asteroid to the vector
		mAst.push_back(cmt);
		currentTime = 0;
	}
}

// update one asteroid and check if we hit the player
void AsteroidsApp::asteroidUpdate(Comet *a_ast, float a_deltaTime)
{
	float oldx = a_ast->mX, oldy = a_ast->mY;

	// coming down
	a_ast->mY -= a_ast->mSpeed*a_deltaTime;

	// have we hit the player
	if (distance(mPlayer.mCurrentXPos, mPlayer.mCurrentYPos, a_ast->mX, a_ast->mY) <= mPlayer.mRadius+a_ast->mRadius) 
		mGameIsOver = true;

	// asteroid has come to the ground (bottom)
	if (a_ast->mY <= 0) {
		a_ast->mAsteroidActive = false;
		return;
	}
}

