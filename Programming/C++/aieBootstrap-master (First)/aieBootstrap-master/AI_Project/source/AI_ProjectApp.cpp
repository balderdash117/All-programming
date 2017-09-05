#include "AI_ProjectApp.h"
#include <Texture.h>
#include <Font.h>
#include <Input.h> 

#include "GameObject.h"
#include "keyboardBehaviour.h"
#include "graph2DRenderer.h"
#include "player.h"

#include "glm\glm.hpp"

AI_ProjectApp::AI_ProjectApp() 
{

}

AI_ProjectApp::~AI_ProjectApp() 
{

}

bool AI_ProjectApp::startup() 
{
	setUpGraph();
	
	return true;
}

void AI_ProjectApp::shutdown() {

	delete player;
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

	player->update(deltaTime);

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
	player->draw(m_2dRenderer);
	
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

	player = new Player();

	player->setPosition(glm::vec2(getWindowWidth() / 2, getWindowHeight() / 2));

	m_graph = new Graph2D();
	m_graphrenderer = new Graph2DRenderer();
	m_graphrenderer->SetGraph(m_graph);

	const int numRows = 5;
	const int numColumns = 5;
	const int Spacing = 50;
	const int xOffSet = 100;
	const int yOffSet = 100;

	graphToMouseDist = Spacing;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numColumns; x++)
		{
			m_graph->AddNode(glm::vec2(x * Spacing + xOffSet, y * Spacing + yOffSet));
		}
	}

	auto &nodes = m_graph->GetNodes();

	for (auto iter1 = nodes.begin(); iter1 != nodes.end(); iter1++)
	{
		Graph2D::Node *nodeA = (*iter1);
		std::vector<Graph2D::Node *> nearbyNodes;
		m_graph->GetNearbyNodes(nodeA->data, 80.0f, nearbyNodes);

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
	m_graph->GetNearbyNodes(m_mousePos, 80.0f, nearbyNodes);

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
		m_graph->GetNearbyNodes(m_mousePos, 80.0f, nearbyNodes);

		auto addedNode = m_graph->AddNode(m_mousePos);

		for (auto iter = nearbyNodes.begin(); iter != nearbyNodes.end(); iter++)
		{
			float dist = glm::length(addedNode->data - (*iter)->data);
			m_graph->AddEdge((*iter), addedNode, dist, true);
		}
	}
}
