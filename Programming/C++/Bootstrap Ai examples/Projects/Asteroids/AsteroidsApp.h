#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
using std::vector;

enum Colors {
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff, GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff, GREEN = 0x00ff00ff,
	DK_GREEN = 0x008000ff, CYAN = 0x00ffffff, DK_CYAN = 0x008080ff, BLUE = 0x0000ffff, DK_BLUE = 0x000080ff, WHITE = 0xffffffff, PURPLE = 0x8034f2
};

struct Comet
{
	bool	mAsteroidActive;	// has it been created
	float	mX;					// where is it x coord
	float	mY;					// where is it y coord
	float	mRadius;			// where is it y coord
	float	mSpeed;				// speed of asteroid 0 - 4 ( 0 is fastest )
	Colors	mColor;				// of comet
};

struct Player
{
	float	mCurrentXPos;		// where is it x coord
	float	mCurrentYPos;		// where is it y coord
	float	mSpeed;				// not used at moment
	float	mRadius;			// for the size
};

struct Ball
{
	float	mBallXPos;		// where is it x coord
	float	mBallYPos;		// where is it y coord
	float	mRadius;		// for the size
};


class AsteroidsApp : public aie::Application {
public:
	AsteroidsApp();
	virtual ~AsteroidsApp() = default;

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void  sortAsteroids();
	void  testCreateAsteroid(float deltaTime);
	void  asteroidUpdate(Comet *a_ast, float deltaTime);
	void  placeBallInPlay();
	void myFoo(int& num);
	float distance(float x1, float y1, float x2, float y2);
protected:
	bool	mGameIsOver;
	float	mTimeInterval;
	float	mTimer;
	int		mScore;
	vector <Comet> mAst;
	Player	mPlayer;
	Ball	mBall;
	int m_foo;
	int* m_pfoo;
	aie::Texture*		m_texture;
	aie::Texture*		m_playerTexture;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};

#if 0

class Asteroids
{
public:
	void setUpAsteroid();
	void thisAsteroidUpdate(int p_count);
	bool attemptToHitAsteroid(int p_x, int p_y);

	bool getAsteroidFalling() { return mAsteroidFalling; };
	int  getAsteroidX() { return mX; };
	int  getAsteroidY() { return mY; };
private:
	bool	mAsteroidFalling;	// has it been created
	int		mX;					// where is it x coord
	int		mY;					// where is it y coord
	int		mSpeedDelay;		// speed of asteroid 0 - 4 ( 0 is fastest )
};


extern Asteroids ast[];
#endif