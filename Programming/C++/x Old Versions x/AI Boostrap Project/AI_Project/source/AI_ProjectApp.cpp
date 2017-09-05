#include "AI_ProjectApp.h"
#include <Texture.h>
#include <Font.h>
#include <Input.h> 

#include "GameObject.h"
#include "keyboardBehaviour.h"
#include "graph2DRenderer.h"
#include "player.h"
#include "Townspeople.h"
#include "knights.h"

#include "glm\glm.hpp"

AI_ProjectApp::AI_ProjectApp() : m_map(nullptr)
{

}

AI_ProjectApp::~AI_ProjectApp() 
{
	delete m_map;
}

bool AI_ProjectApp::startup() 
{
	m_map = new aie::Texture("./textures/level_test.png");

	setUpGraph();
	setUpEntities();

	return true;
}

void AI_ProjectApp::shutdown() 
{
	delete player;

	m_townsPeople.clear();
	m_knight.clear();

	delete m_font;
	delete m_2dRenderer;
	delete m_graph;
	delete m_graphrenderer;
}

void AI_ProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	int mx, my;
	input->getMouseXY(&mx, &my);
	m_mousePos = glm::vec2(mx, my);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	updateGraph();

	UpdateTownsPeople(deltaTime);
	UpdateKnights(deltaTime);

	const glm::vec2 &playerPos = player->getPosition();

	if (playerPos.x < 0) player->setPosition(glm::vec2(getWindowWidth(), playerPos.y));
	if (playerPos.x > getWindowWidth()) player->setPosition(glm::vec2(0, playerPos.y));
	
	if (playerPos.y < 0) player->setPosition(glm::vec2(playerPos.x, getWindowHeight()));
	if (playerPos.y > getWindowHeight()) player->setPosition(glm::vec2(playerPos.x, 0));
}

void AI_ProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	//player->draw(m_2dRenderer);
	DrawTownsPeople();
	DrawKnights();
	drawMap();

	drawGraph();

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void AI_ProjectApp::setUpGraph()
{
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_graph = new Graph2D();
	m_graphrenderer = new Graph2DRenderer();
	m_graphrenderer->SetGraph(m_graph);

	const int Spacing = 20;
	const int xOffSet = 5;
	const int yOffSet = 5;
	const int numRows =	getWindowHeight();
	const int numColumns = getWindowWidth();

	for (int y = 0; y < 40; y++) {
		for (int x = 0; x < 40; x++) {
			glm::vec2 nodePos = glm::vec2(x * Spacing + xOffSet, getWindowHeight() - y * Spacing + yOffSet);

			// Find current pixel (4 bytes = R, G, B, A)
			//size_t pixelIndex = (x * y)  * 4;
			size_t pixelIndex = (y*m_map->getWidth() + x) * 4;

			// If pixel is black (first 3 bytes are 0)
			if (m_map->getPixels()[pixelIndex + 3] == 0) 
			{
				m_graph->AddNode(nodePos);
			}
			else 
			{

			}
		}
	}

	/*const int numRows = getWindowWidth() / Spacing;
	const int numColumns = getWindowHeight() / Spacing;

	graphToMouseDist = Spacing;

	for (int y = 0; y < numColumns; y++)
	{
		for (int x = 0; x < numRows; x++)
		{
			int xi = x * Spacing + xOffSet;
			int yi = getWindowHeight() - (y * Spacing + yOffSet);
			unsigned char alpha = m_map->getPixels()[(((yi)*m_map->getWidth() + xi))];
			
			if (alpha > 0)
			{
				m_graph->AddNode(glm::vec2(
					x * Spacing + xOffSet,
					y * Spacing + yOffSet
				));
			}
		}
	}*/

	auto &nodes = m_graph->GetNodes();

	for (auto iter1 = nodes.begin(); iter1 != nodes.end(); iter1++)
	{
		Graph2D::Node *nodeA = (*iter1);
		std::vector<Graph2D::Node *> nearbyNodes;
		m_graph->GetNearbyNodes(nodeA->data, 25.0f, nearbyNodes);

		for (auto iter2 = nearbyNodes.begin(); iter2 != nearbyNodes.end(); iter2++)
		{
			Graph2D::Node *nodeB = (*iter2);
			if (nodeA == nodeB)
			{
				continue;
			}

			float distanceBetweenNodes = glm::length(nodeB->data - nodeA->data);
			m_graph->AddEdge(nodeA, nodeB, false, distanceBetweenNodes);
		}
	}

}

void AI_ProjectApp::drawGraph()
{

	m_graphrenderer->Draw(m_2dRenderer);
	//render lines to nodes
	std::vector<Graph2D::Node *> nearbyNodes;
	m_graph->GetNearbyNodes(m_mousePos, 25.0f, nearbyNodes);

	for (auto iter = nearbyNodes.begin(); iter != nearbyNodes.end(); iter++)
	{
		m_2dRenderer->drawLine(m_mousePos.x, m_mousePos.y, (*iter)->data.x, (*iter)->data.y);
	}
}

void AI_ProjectApp::updateGraph()
{
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		std::vector<Graph2D::Node *> nearbyNodes;
		m_graph->GetNearbyNodes(m_mousePos, 25.0f, nearbyNodes);

		auto addedNode = m_graph->AddNode(m_mousePos);

		for (auto iter = nearbyNodes.begin(); iter != nearbyNodes.end(); iter++)
		{
			float dist = glm::length(addedNode->data - (*iter)->data);
			m_graph->AddEdge((*iter), addedNode, true, dist);
		}
	}
}

void AI_ProjectApp::UpdateTownsPeople(float dt)
{
	for (auto iter = m_townsPeople.begin(); iter != m_townsPeople.end(); iter++)
	{
		(*iter)->update(dt);
	}
}

void AI_ProjectApp::DrawTownsPeople()
{
	for (auto iter = m_townsPeople.begin(); iter != m_townsPeople.end(); iter++)
	{
		(*iter)->draw(m_2dRenderer);
	}
}

void AI_ProjectApp::UpdateKnights(float dt)
{
	for (auto iter = m_knight.begin(); iter != m_knight.end(); iter++)
	{
		(*iter)->update(dt);
	}
}

void AI_ProjectApp::DrawKnights()
{
	for (auto iter = m_knight.begin(); iter != m_knight.end(); iter++)
	{
		(*iter)->draw(m_2dRenderer);
	}
}

void AI_ProjectApp::setUpEntities()
{
	player = new Player();
	player->setPosition(glm::vec2(getWindowWidth() / 2, getWindowHeight() / 2));
	player->setGraph(m_graph);

	auto person = new Townspeople();
	person->setPosition(glm::vec2(getWindowWidth() / 2, getWindowHeight() / 2));
	person->setGraph(m_graph);
	person->setObjectType(0);
	m_townsPeople.push_back(person);

	auto knight = new knights();
	knight->setPosition(glm::vec2(getWindowWidth() / 3, getWindowHeight() / 3));
	knight->setGraph(m_graph);
	knight->setObjectType(1);
	m_knight.push_back(knight);
}

void AI_ProjectApp::drawMap()
{
	m_2dRenderer->drawSprite(m_map, (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, (float)getWindowWidth(), (float)getWindowHeight(), 0, 50.f );
}

aie::Texture AI_ProjectApp::getMapTexture()
{
	return *m_map;
}