#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>

using std::vector;

#define NULL_POINT { -1, -1 }

#define MAX_EDGES 8

struct Point
{
	Point() = default;
	Point(int p_x, int p_y) : x(p_x), y(p_y) {}
	int x, y;
	bool operator != (Point &rhs) {
		return !(x == rhs.x && y == rhs.y);
	}
	bool operator == (Point &rhs) {
		return (x == rhs.x && y == rhs.y);
	}
};

class LocData {
public:
	unsigned int m_color;
	float edges[MAX_EDGES];
	unsigned int costForEdit;

	bool visited;
	bool queued;
	float costFromStart;
	Point connectedTo;
};

class GridApp : public aie::Application {
public:
	enum editValues {EDIT_0, EDIT_1, EDIT_2, EDIT_3, EDIT_4, EDIT_5, EDIT_6, EDIT_7, EDIT_8, TRIAL_MOVEMENT};

	GridApp();
	virtual ~GridApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	virtual void setupLinks();
	virtual void drawCityPathway(aie::Renderer2D* p_2dRenderer);
	virtual void renderCircle(aie::Renderer2D* p_2dRenderer, Point p_centre, float radius, unsigned int p_color, unsigned int sides);
	virtual void saveMap();
	virtual void loadMap();
	virtual void setupEdges();

	virtual Point findScreenCity(Point a_map); 
	virtual void findShortestPath();
	virtual Point getEdgePoint(Point p_pt, int p_edge);
	virtual void makeCityPath();


protected:
	editValues m_currentEditNumber;
	Point m_mapTop;
	unsigned int m_mapWidth;
	unsigned int m_mapHeight;

	vector < vector < LocData>> m_travel;
	vector <Point> m_path;

	Point m_nullPoint;
	Point m_startPoint;
	Point m_stopPoint;
	Point m_lastStartPoint;
	Point m_lastStopPoint;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Font*			m_smallFont;
	aie::Texture*		m_background;
};