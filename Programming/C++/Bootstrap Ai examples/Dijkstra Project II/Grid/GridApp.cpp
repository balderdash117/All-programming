#include "GridApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <assert.h>

using std::cout;
using std::endl;
using std::string;

GridApp::GridApp() {

}

GridApp::~GridApp() {

}

bool GridApp::startup() {
	m_currentEditNumber = EDIT_0;

	// top of the map
	m_mapTop.x = 0;
	m_mapTop.y = 0;
	// size of grid
	m_mapWidth = 43;
	m_mapHeight = 45;

	m_lastStartPoint = m_lastStopPoint = m_startPoint = m_stopPoint = m_nullPoint = NULL_POINT;

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_smallFont = new aie::Font("./font/consolas.ttf", 14);
	m_background = new aie::Texture("./textures/maze.png");

	setupLinks();
	// and load data if there is any
	loadMap();

	return true;
}

void GridApp::shutdown() {

	delete m_background;
	delete m_smallFont;
	delete m_font;
	delete m_2dRenderer;
}


void GridApp::update(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		Point mouse;
		input->getMouseXY(&mouse.x, &mouse.y);

		int xm = mouse.x / 32;
		int ym = mouse.y / 32;

		// transfer this into a co-ordinate system
		Point onMap;
		onMap.x = xm;
		onMap.y = ym + (m_mapHeight - getWindowHeight() / 32 - m_mapTop.y);

		if (m_currentEditNumber != TRIAL_MOVEMENT) {
			m_travel[onMap.x][onMap.y].costForEdit = m_currentEditNumber;
		} else {
			m_startPoint = findScreenCity(onMap);
		}
	}

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT) && m_currentEditNumber == TRIAL_MOVEMENT) {
		Point mouse;
		input->getMouseXY(&mouse.x, &mouse.y);

		int xm = mouse.x / 32;
		int ym = mouse.y / 32;
		// transfer this into a co-ordinate system
		Point onMap;
		onMap.x = xm;
		onMap.y = ym + (m_mapHeight - getWindowHeight() / 32 - m_mapTop.y);

		m_stopPoint = findScreenCity(onMap);
	}

	// establish the edit number between 0-8, '9' is the game
	for (auto iter = input->getPressedKeys().begin(); iter != input->getPressedKeys().end(); ++iter) {
		if (!input->wasKeyPressed(*iter)) continue;
		if (*iter < '0' || *iter > '9') continue;

		m_currentEditNumber = (editValues) (EDIT_0 + *iter - '0');
		if (m_currentEditNumber == TRIAL_MOVEMENT) {
			setupEdges();
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_DOWN)) {
		static bool doOnce = false;
		if (!doOnce) {
			//doOnce = true;
			int mm = getWindowHeight() / 32 - m_mapHeight;
			m_mapTop.y = std::min((int)(m_mapHeight - getWindowHeight() / 32), m_mapTop.y + 1);
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_UP)) {
		m_mapTop.y = std::max(0, m_mapTop.y - 1);
	}

	if (input->isKeyDown(aie::INPUT_KEY_S) && input->wasKeyPressed(aie::INPUT_KEY_S)) {
		if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL) || input->isKeyDown(aie::INPUT_KEY_RIGHT_CONTROL)) {
			// save the map as a text file
			saveMap();
		}
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GridApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	drawCityPathway(m_2dRenderer);

	// background
	int pictHeight = m_mapTop.y*32 - getWindowHeight() /2;
	m_2dRenderer->drawSprite(m_background, (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, (float)getWindowWidth() , (float)getWindowHeight() , 0, 5.f);

	// output some text, uses the last used colour
	if (m_startPoint == m_nullPoint || m_stopPoint == m_nullPoint)
		m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	else {
		char tempStr[1024];
		sprintf_s(tempStr, "Press ESC to quit. Path cost = %.1f", m_travel[m_stopPoint.x][m_stopPoint.y].costFromStart);
		m_2dRenderer->drawText(m_font, tempStr, 0, 0);
	}

	// done drawing sprites
	m_2dRenderer->end();
}

//void DijkstraApp::setupLinks(SkyrimMap * travelMap)
void GridApp::setupLinks()
{
	m_travel.clear();

	// make the map and then fill it with 'zero' markers 
	m_travel.resize(m_mapWidth);
	// this is supposed to be 'mx' not 'my'
	for (unsigned int x= 0; x<m_mapWidth; ++x) {
		m_travel[x].resize(m_mapHeight);
	}
	// and zero each location
	LocData zeroLoc = {};
	for (unsigned int x = 0; x < m_mapWidth; ++x) {
		for (unsigned int y = 0; y < m_mapHeight; ++y) {
			m_travel[x][y] = zeroLoc;
			m_travel[x][y].costForEdit = 0;
			if (x % 5 == 0 && y % 5 == 0)
				m_travel[x][y].m_color = 0x80000080;
		}
	}
	// and create edge values
	setupEdges();
}

Point GridApp::getEdgePoint(Point p_pt, int p_edge)
{
	int xAdjust[MAX_EDGES] = { 0, +1, +1, +1,  0, -1, -1, -1 };
	int yAdjust[MAX_EDGES] = { +1, +1,  0, -1, -1, -1,  0, +1 };

	int lookXp = p_pt.x + xAdjust[p_edge];
	int lookYp = p_pt.y + yAdjust[p_edge];
	// be careful of the edges of the map
	if (lookXp < 0 || lookYp < 0) return m_nullPoint;
	if (lookXp >= (int)m_mapWidth || lookYp >= (int)m_mapHeight) return m_nullPoint;

	return { lookXp, lookYp };
}

void GridApp::setupEdges()
{
	// x-1 x x+1
	//	7  0  1	y+1
	//  6  *  2 y
	//  5  4  3 y-1
	// modifier
	//	1.4  1.0  1.4	
	//  1.0   *   1.0
	//  1.4  1.0  1.4

	float modifier[MAX_EDGES] = { 1.f, 1.4f, 1.f, 1.4f, 1.f, 1.4f, 1.f, 1.4f };
	for (int x = 0; x < (int)m_mapWidth; ++x) {
		for (int y = 0; y < (int)m_mapHeight; ++y) {

			Point nextPoint;
			for (unsigned int edge = 0; edge < MAX_EDGES; ++edge) {
				// initialize
				m_travel[x][y].edges[edge] = 0;

				if ((nextPoint = getEdgePoint({ x, y }, edge)) == m_nullPoint) continue;
				if (! m_travel[nextPoint.x][nextPoint.y].costForEdit) continue;

				// now look at the actual path values
				m_travel[x][y].edges[edge] = ((m_travel[x][y].costForEdit + m_travel[nextPoint.x][nextPoint.y].costForEdit) / 2.f)*modifier[edge];
			}
		}
	}
}

void GridApp::renderCircle(aie::Renderer2D* p_2dRenderer, Point p_centre, float radius, unsigned int p_color, unsigned int sides)
{
	if (sides == 0)
	{
		sides = (unsigned int)(3.14*radius);
	}
	m_2dRenderer->setRenderColour(p_color);

	float d_a = (float)(3.14 * 2 / (float)sides),
		angle = d_a;

	float startX, startY, endX, endY;
	endX = radius;
	endY = 0.0f;
	endX = endX + p_centre.x;
	endY = endY + p_centre.y;
	for (int i = 0; i != sides; i++)
	{
		startX = endX;
		startY = endY;
		endX = cos(angle) * radius;
		endY = sin(angle) * radius;
		endX = endX + p_centre.x;
		endY = endY + p_centre.y;
		angle += d_a;
		m_2dRenderer->drawLine((float)startX, (float)startY, (float)endX, (float)endY, 2.f, 2.f);
	}
}

#define PRINTOUT_VISITED false

void GridApp::drawCityPathway(aie::Renderer2D* p_2dRenderer)
{
	if (m_currentEditNumber != TRIAL_MOVEMENT) {
		for (int x = 0; x < (int)m_mapWidth; ++x) {
			for (int y = 0; y < (int)m_mapHeight; ++y) {
				//if (!(x == 8 && yp == 1)) continue;
				m_2dRenderer->setRenderColour(m_travel[x][y].m_color);

				if (m_currentEditNumber == (editValues)m_travel[x][y].costForEdit) {
					m_2dRenderer->setRenderColour(0.f, 0.5f, 0.f, 1.f);
				}
				else continue;

				Point pt = { x * 32 + 16, (y - m_mapTop.y) * 32 + 16 };
				pt.y = (y + m_mapTop.y - (getWindowHeight() / 16 - m_mapHeight)) * 32 + 16;
				p_2dRenderer->drawCircle((float)pt.x, (float)pt.y, 7.f, 1.f);
			}
		}
	} else {
		for (int x = 0; x < (int)m_mapWidth; ++x) {
			for (int y = 0; y < (int)m_mapHeight; ++y) {
				if (! m_travel[x][y].visited) continue;

				if (PRINTOUT_VISITED) {
					m_2dRenderer->setRenderColour(0x00ffffff);
					Point pt = { x * 32 + 16, (y - m_mapTop.y) * 32 + 16 };
					pt.y = (y + m_mapTop.y - (getWindowHeight() / 16 - m_mapHeight)) * 32 + 16;
					p_2dRenderer->drawCircle((float)pt.x, (float)pt.y, 7.f, 1.f);
				}

				m_2dRenderer->setRenderColour(0xffff00ff);
				Point pt = { x * 32 + 16, (y - m_mapTop.y) * 32 + 16 };
				pt.y = (y + m_mapTop.y - (getWindowHeight() / 16 - m_mapHeight)) * 32 + 16;
				for (auto it : m_path) {
					if (!(it.x == x && it.y == y)) continue;
					p_2dRenderer->drawCircle((float)pt.x, (float)pt.y, 7.f, 1.f);
					//m_2dRenderer->drawText(m_smallFont, "ok", (float)pt.x - 4, (float)pt.y);
				}
			}
		}
	}

	// draw the locations on the map if they exist
	if (m_startPoint != m_nullPoint) {
		m_2dRenderer->setRenderColour(0xffffffff);
		Point pt = { m_startPoint.x * 32 + 16, (m_startPoint.y - m_mapTop.y) * 32 + 16 };
		pt.y = (m_startPoint.y + m_mapTop.y - (getWindowHeight() / 16 - m_mapHeight)) * 32 + 16;

		renderCircle(p_2dRenderer, { pt.x + 2, pt.y - 2 }, 10, 0x000000ff, 30);
		renderCircle(p_2dRenderer, pt, 10, 0x00ff00ff, 30);
	}
	if (m_stopPoint != m_nullPoint) {
		m_2dRenderer->setRenderColour(0x800000ff);
		Point pt = { m_stopPoint.x * 32 + 16, (m_stopPoint.y - m_mapTop.y) * 32 + 16 };
		pt.y = (m_stopPoint.y + m_mapTop.y - (getWindowHeight() / 16 - m_mapHeight)) * 32 + 16;

		renderCircle(p_2dRenderer, { pt.x + 2, pt.y - 2 }, 10, 0x000000ff, 30);
		renderCircle(p_2dRenderer, pt, 10, 0xff0000ff, 30);
	}

	if (m_startPoint != m_lastStartPoint || m_stopPoint != m_lastStopPoint) {
		// do Dijkstra routine
		findShortestPath();
		m_lastStartPoint = m_startPoint;
		m_lastStopPoint = m_stopPoint;
	}
	// re-establish color
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, 1.0f);
}

void GridApp::saveMap()
{
	std::ofstream myfile;
	myfile.open("outputMap.txt");
	if (!myfile.is_open()) return;

	for (int y = m_mapHeight; y--;) {
		for (int x = 0; x < (int)m_mapWidth; ++x) {

			myfile << m_travel[x][y].costForEdit << " ";
		}
		myfile << endl;
	}

	myfile.close();
}

void GridApp::loadMap()
{
	std::ifstream myfile;
	myfile.open("outputMap.txt");
	if (!myfile.is_open()) return;

	string str;
	int y = m_mapHeight-1;
	while (!myfile.eof()) {
		getline(myfile, str);

		for (int x = 0; x < (int)m_mapWidth; ++x) {
			// as this is a character make adjustments
			unsigned int value = (unsigned int)str[x * 2]-'0';
			m_travel[x][y].costForEdit = value;
		}
		if (--y < 0) break;
	}

	myfile.close();
}

Point GridApp::findScreenCity(Point a_onMap)
{
	// find out what we clicked on
	Point mapPosition = m_nullPoint;

	unsigned int bestDistance = 10000;

	for (int y = m_mapHeight; y--;) {
		for (int x = 0; x < (int)m_mapWidth; ++x) {
			unsigned int dist = (x - a_onMap.x)*(x - a_onMap.x) + (y - a_onMap.y)*(y - a_onMap.y);
			if (!m_travel[x][y].costForEdit) continue;

			if (dist < bestDistance) {
				bestDistance = dist;
				mapPosition = { x, y };
			}
		}
	}

	return mapPosition;
}

// find path through grid
#define PRINTOUT_PATH false

void GridApp::findShortestPath()
{
	//assert(!(m_startPoint == m_nullPoint || m_stopPoint == m_nullPoint) && "Start and stop point not initialized.");
	m_path.clear();
	if (m_startPoint == m_nullPoint || m_stopPoint == m_nullPoint) return;

	// Initialize
	for (int y = m_mapHeight; y--;) {
		for (int x = m_mapWidth; x--;) {
			m_travel[x][y].visited = 0;
				m_travel[x][y].queued = 0;
				m_travel[x][y].costFromStart = 10000.f;
				m_travel[x][y].connectedTo = m_nullPoint;
		}
	}

	// Set up the 'vectors'
	typedef std::pair <Point, float> iPath;	 // Position, value
		vector<Point> explored;	 // Where we have been
		std::list<iPath> connectedQueue;	// What we are currently looking at in terms of a path, always choose smallest first.

											// Deal with starting position
	explored.push_back(m_startPoint);
	m_travel[m_startPoint.x][m_startPoint.y].visited = true;
	m_travel[m_startPoint.x][m_startPoint.y].costFromStart = 0;

	if (PRINTOUT_PATH)
	{
		cout << "Starting Point: ( " << m_startPoint.x << " , " << m_startPoint.y << 
			 " ) Finishing Point: ( " << m_stopPoint.x << " , " << m_stopPoint.y << " ) " << endl;
	}

	Point nextPoint;

	for (unsigned int edge = 0; edge < MAX_EDGES; edge++)
	{
		float edgeCost = m_travel[m_startPoint.x][m_startPoint.y].edges[edge];

		if (!edgeCost) continue;
		if ((nextPoint = getEdgePoint(m_startPoint, edge)) == m_nullPoint) continue;

		m_travel[nextPoint.x][nextPoint.y].costFromStart = edgeCost;
		m_travel[nextPoint.x][nextPoint.y].connectedTo = m_startPoint;

		connectedQueue.push_back({ nextPoint, edgeCost });

		m_travel[nextPoint.x][nextPoint.y].visited = true;

		if (PRINTOUT_PATH)
		{
			cout << "Adding: ( " << nextPoint.x << " , " << nextPoint.y << " ) " << endl;
		}
	}
	connectedQueue.sort([](const iPath &a, const iPath &b) {return a.second < b.second; });

	while (true)
	{
		if (connectedQueue.size() == 0)
		{
			if (PRINTOUT_PATH)
			{
				cout << "No more points ... Finished" << endl;
			}
			makeCityPath();
			return;
		}
		iPath next = connectedQueue.front();
		connectedQueue.pop_front();

		if (PRINTOUT_PATH)
			cout << "Point selected is: ( " <<nextPoint.x << " , " << nextPoint.y << " ) " << endl;

		explored.push_back(next.first);
		m_travel[next.first.x][next.first.y].visited = true;

		if (next.first == m_stopPoint)
		{
			makeCityPath();
			return;
		}

		Point pt = { next.first.x, next.first.y };

		for (unsigned int edge = 0; edge < MAX_EDGES; ++edge)
		{
			float pathCost = m_travel[pt.x][pt.y].edges[edge];

			if (!pathCost) continue;
			if ((nextPoint = getEdgePoint(pt, edge)) == m_nullPoint) continue;
			if (m_travel[nextPoint.x][nextPoint.y].visited) continue;

			float totalCost = m_travel[pt.x][pt.y].costFromStart + pathCost;

			if (totalCost < m_travel[nextPoint.x][nextPoint.y].costFromStart)
			{
				m_travel[nextPoint.x][nextPoint.y].connectedTo = pt;
				m_travel[nextPoint.x][nextPoint.y].costFromStart = totalCost;
				connectedQueue.push_back({ nextPoint,totalCost });

				if (PRINTOUT_PATH)
				{
					cout << "Added: ( " << nextPoint.x << " , " << nextPoint.y << " ) to the queue cost = " << totalCost << endl;
				}
			}
		}
		connectedQueue.sort([](const iPath &a, const iPath &b) {return a.second < b.second; });
	}
}

void GridApp::makeCityPath()
{
	Point current = m_stopPoint;

	while (m_travel[current.x][current.y].connectedTo != m_nullPoint)
	{
		m_path.push_back(current);
		current = m_travel[current.x][current.y].connectedTo;
	}

	if (current == m_startPoint)
	{
		m_path.push_back(current);
		std::reverse(m_path.begin(), m_path.end());
		
		if (PRINTOUT_PATH)
		{
			for (auto pt : m_path)
			{
				cout << "Final Path: " << pt.x << " , " << pt.y << " ) " << endl;
			}
		}
	}
}