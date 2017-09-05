#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>

struct Vector2 {
	float x, y;
};

class GameObject;

enum eBehaviourResult { SUCCESS, FAILURE, RUNNING };

// abstract class
class Behaviour {
public:

	// empty constructors and destructors for base class
	Behaviour() {}
	virtual ~Behaviour() {}

	// pure virtual function for executing the behaviour
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime) = 0;
};

class KeyboardBehaviour : public Behaviour {
public:

	KeyboardBehaviour() : m_speed(1) { }
	virtual ~KeyboardBehaviour() = default;

	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

	void setSpeed(float speed) { m_speed = speed; }
private:

	float m_speed;
};

class FollowBehaviour : public Behaviour {
public:

	FollowBehaviour() : m_speed(1), m_target(nullptr) { }
	virtual ~FollowBehaviour() = default;

	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

	void setSpeed(float speed) { m_speed = speed; }

	void setTarget(GameObject* gameObject) { m_target = gameObject; }
private:
	float		m_speed;
	GameObject*	m_target;
};

class GameObject {
public:

	GameObject() : m_x(0), m_y(0) { }
	virtual ~GameObject() = default;

	// movement functions
	void setPosition(float x, float y) { m_x = x; m_y = y; }
	void getPosition(float* x, float* y) const { *x = m_x; *y = m_y; }
	void translate(float x, float y) { m_x += x; m_y += y; }

	// add a behaviour
	void addBehaviour(Behaviour* behaviour) { m_behaviours.push_back(behaviour); }

	// update game object and execute behaviours
	virtual void update(float deltaTime) {
		// execute all behaviours
		for (auto behaviour : m_behaviours)
			behaviour->execute(this, deltaTime);
	}

protected:
	float m_x, m_y;

	std::vector<Behaviour*>	m_behaviours;
};


class IntroductionApp : public aie::Application {
public:
	IntroductionApp();
	virtual ~IntroductionApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	GameObject			m_player;
	KeyboardBehaviour	m_keyboardBehaviour;

	GameObject			m_enemy;
	FollowBehaviour		m_followBehaviour;
};