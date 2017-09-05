#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include <glm\vec2.hpp>

class GameObject;
class Graph2DRenderer;
class Graph2D;

class AI_ProjectApp : public aie::Application {
public:

						 AI_ProjectApp();
	virtual				~AI_ProjectApp();

	virtual bool		 startup();
	virtual void		 shutdown();
						 
	virtual void		 update(float deltaTime);
	virtual void		 draw();

	void				 setUpGraph();
	void				 drawGraph();
	void				 updateGraph();

protected:
	float				 graphToMouseDist;

	aie::Renderer2D*	 m_2dRenderer;
	aie::Font*			 m_font;

	glm::vec2			 m_mousePos;
						 
	Graph2D				*m_graph;
	Graph2DRenderer		*m_graphrenderer;
						 
	GameObject			*player = nullptr;
};