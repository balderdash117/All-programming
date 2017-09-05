#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "BinaryTree.h"
#include "Texture.h"
#include <vector>
#include <Vector3.h>
using std::vector;

enum Colors {
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff, GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff, GREEN = 0x00ff00ff,
	DK_GREEN = 0x008000ff, CYAN = 0x00ffffff, DK_CYAN = 0x008080ff, BLUE = 0x0000ffff, DK_BLUE = 0x000080ff, WHITE = 0xffffffff, PURPLE = 0x8034f2
};

struct Rectf { float x; float y; float w; float h; };

#define MAX_EXPLOSION_COUNT  11
#define EXPLOSION_SWITCH  0.15f
//const float mSwitch = .09f;

struct explosion {
	Vector3	mPos;		// where is it x coord

	float mWidth = 848.f;
	float mHeight = 464.f;
	Rectf mArray[MAX_EXPLOSION_COUNT] = {
		{ 13.f, 72.f, 90.f, 69.f }, { 112.f, 56.f, 123.f, 86.f }, { 241.f, 34.f, 164.f, 108.f }, { 419.f, 26.f, 191.f, 116.f }, { 620.f, 0.f, 226.f, 143.f },
		{ 0.f, 151.f, 228.f, 149.f },{ 233.f, 153.f, 228.f, 149.f }, { 473.f, 147.f, 228.f, 154.f },{ 0.f, 312.f, 228.f, 151.f },{ 234.f, 312.f, 228.f, 148.f }, { 472.f, 307.f, 229.f, 154.f}
	};
	int mIndex;
	float mTimer;
};

struct Apples
{
	bool	mAsteroidActive;	// has it been created
	Vector3	mPos;				// where is it x coord
	float	mSpeed;				// speed of asteroid 0 - 4 ( 0 is fastest )
	float	mScale;				// number of pixels for the radius
	int		mNumber;			// the number attached to this apple
	Colors	mColor;				// of comet
};

class CDDS_BinaryTreesApp : public aie::Application {
public:

	CDDS_BinaryTreesApp();
	virtual ~CDDS_BinaryTreesApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void  testCreateAnotherApple(float deltaTime);
	float distance(Vector3 a_posOne, Vector3 a_posTwo);
	void appleUpdate(std::vector<Apples>::iterator a_apple, float a_deltaTime);

protected:
	float	mTimeInterval;

	aie::Renderer2D*	m_2dRenderer;

	BinaryTree			m_binaryTree;
	TreeNode*			m_selectedNode;
	aie::Texture*		m_appleTex;
	aie::Texture*		m_explosionTex;
	vector <Apples>		m_apple;
	vector <explosion>  m_explosions;
};