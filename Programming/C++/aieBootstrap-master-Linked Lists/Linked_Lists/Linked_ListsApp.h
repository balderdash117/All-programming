#pragma once
#include <iostream>
#include "Application.h"
#include "Renderer2D.h"
#include <string>

using std::string;

struct node    //structure of node //
{
	string name;
	string discipline;
	int section;
	node *next;
};

class ListNode {
public:
	ListNode *next;
	ListNode *prev;
	node value;
};

class List {
public:
	List();
	// manipulate functions
	virtual void add();
	virtual void moveCurrentptr(bool right);
protected:
	node displayed_Node;

	ListNode *currentptr;
	ListNode *m_first;
	ListNode *m_last;
};

class Linked_ListsApp : public aie::Application, List {
public:
	enum menuEntry { NAME, DISCIPLINE, SECTION };

	Linked_ListsApp();
	virtual ~Linked_ListsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	virtual void initializeNode();
	virtual void changeMenu(bool up);
	virtual void eraseLinkedList();

protected:
	menuEntry menuItem = NAME;
	bool checkFirst;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};