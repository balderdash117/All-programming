#pragma once

#include "GameObject.h"

class KeyboardBehaviour;
class seekBehaviour;
class followPathBehaviour;
class path;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D *renderer);

protected:

	KeyboardBehaviour		*m_KeyboardBehaviour;
	seekBehaviour			*m_seekBehaviour;
	seekBehaviour			*m_fleeBehaviour;
	followPathBehaviour		*m_followPathBehaviour;

	path					*m_path;

	float					force;

private:
};
