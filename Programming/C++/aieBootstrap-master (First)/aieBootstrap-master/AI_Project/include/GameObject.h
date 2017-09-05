#pragma once

#include <glm/vec2.hpp>

class behaviour;

namespace aie
{
	class Renderer2D;
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D *renderer);

	const glm::vec2 & getPosition();
	const glm::vec2 & getVelocity();
	
	void setPosition(const glm::vec2 & pos);
	void setVelocity(const glm::vec2 & vel);

	void applyForce(const glm::vec2 & force);

	float getFriction();
	void setFriction(float frict);

	void simulatePhysics(float deltaTime);

	void setBehaviour(behaviour * Behaviour);
	behaviour *getBehaviour();

protected:

	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;

	float friction;

	behaviour *Behaviour;

private:
};