#include "player.h"
#include "keyboardBehaviour.h"
#include "seekBehaviour.h"
#include "followPathBehaviour.h"
#include "path.h"

#include <Input.h>

Player::Player() : GameObject(), force(1000.f)
{
	m_KeyboardBehaviour = new KeyboardBehaviour();
	m_KeyboardBehaviour->isOwnedByGameObject(false);

	m_seekBehaviour = new seekBehaviour();
	m_seekBehaviour->isOwnedByGameObject(false);
	m_seekBehaviour->setForceStrength(force);
	m_seekBehaviour->setInnerRadius(20);
	m_seekBehaviour->setOuterRadius(100);



	m_seekBehaviour->onOuterRadiusEnter([this]()
	{
		m_seekBehaviour->setForceStrength(force/4);
	}
	);

	m_seekBehaviour->onInnerRadiusEnter([this]()
	{
		setBehaviour(m_KeyboardBehaviour);
		m_seekBehaviour->setForceStrength(force);
	}
	);
	


	m_fleeBehaviour = new seekBehaviour();
	m_fleeBehaviour->isOwnedByGameObject(false);
	m_fleeBehaviour->setForceStrength(force*-1);
	m_fleeBehaviour->setInnerRadius(60);
	m_fleeBehaviour->setOuterRadius(200);



	m_fleeBehaviour->onOuterRadiusExit([this]() 
	{
		setBehaviour(m_KeyboardBehaviour);
		m_fleeBehaviour->setForceStrength(force);
	}
	);

	m_fleeBehaviour->onInnerRadiusExit([this]()
	{
		m_fleeBehaviour->setForceStrength(force*-1.5);
	}
	);



	setBehaviour(m_KeyboardBehaviour);
	setFriction(7.f);

	m_seekBehaviour->setKeyboard([this]()
	{
		setBehaviour(m_KeyboardBehaviour);
	}
	);

	m_fleeBehaviour->setHigherSpeed([this]()
	{
		m_fleeBehaviour->setForceStrength(force*-2.5);
	}
	);


	m_path = new path();

	m_followPathBehaviour = new followPathBehaviour();
	m_followPathBehaviour->isOwnedByGameObject(false);
	m_followPathBehaviour->setPath(m_path);

}

Player::~Player()
{
	setBehaviour(nullptr);

	delete m_path;
	delete m_followPathBehaviour;
	delete m_seekBehaviour;
	delete m_fleeBehaviour;
	delete m_KeyboardBehaviour;
}

void Player::update(float deltaTime)
{
	int mx, my;

	aie::Input * input = aie::Input::getInstance();

	input->getMouseXY(&mx, &my);

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
			m_seekBehaviour->setTarget(glm::vec2(mx,my));
			setBehaviour(m_seekBehaviour);
	}
	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
			m_fleeBehaviour->setTarget(glm::vec2(mx,my));
			setBehaviour(m_fleeBehaviour);
	}

	else if (input->wasKeyPressed(aie::INPUT_MOUSE_BUTTON_MIDDLE) || input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		if (getBehaviour() != m_followPathBehaviour)
			setBehaviour(m_followPathBehaviour);

		m_path->pushPathSegement(glm::vec2(mx, my));
	}

	if (   getBehaviour() != m_KeyboardBehaviour && 		input->getPressedKeys().empty() == false &&
		input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL))
	{
		setBehaviour(m_KeyboardBehaviour);
		m_seekBehaviour->setForceStrength(100);
	}

	GameObject::update(deltaTime);
}

void Player::draw(aie::Renderer2D * renderer)
{


	GameObject::draw(renderer);
}
