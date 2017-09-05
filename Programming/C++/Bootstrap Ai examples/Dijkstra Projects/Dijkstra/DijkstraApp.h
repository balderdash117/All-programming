#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "travelRoutines.h"

class DijkstraApp : public aie::Application {
public:

	DijkstraApp();
	virtual ~DijkstraApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	virtual void setupLinks();

	void drawCityPathway(aie::Renderer2D* p_2dRenderer);
	void renderCircle(aie::Renderer2D* p_2dRenderer, Point p_centre, float radius, unsigned int p_color, unsigned int sides);

protected:
	SkyrimMap * travelMap = nullptr;

	City* startCity = nullptr;
	City* stopCity = nullptr;
	City* lastStartCity = nullptr;
	City* lastStopCity = nullptr;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_background;
};