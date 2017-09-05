#pragma once
#include "followPathBehaviour.h"

#include <glm\vec2.hpp>

class wanderBehaviour :
	public followPathBehaviour
{
public:
	wanderBehaviour();
	virtual ~wanderBehaviour();

	virtual void	update(GameObject *obj, float deltaTime);
	virtual void	draw(GameObject *obj, aie::Renderer2D *renderer);

	glm::vec2		findRandomPoint();

protected:

	glm::vec2		m_randomPoint;

private:
};

