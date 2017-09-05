
#include "Linked_ListsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

List::List()
{
	m_first = nullptr;
	m_last = nullptr;
	currentptr = nullptr;
}

void Linked_ListsApp::initializeNode()
{
	displayed_Node.name = "_";
	displayed_Node.discipline = "_";
	displayed_Node.section = 0;
	displayed_Node.next = nullptr;

	menuItem = NAME;
}

Linked_ListsApp::Linked_ListsApp() {
	checkFirst = true;
	initializeNode();
}

Linked_ListsApp::~Linked_ListsApp() {

}

bool Linked_ListsApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	return true;
}

void Linked_ListsApp::eraseLinkedList() {
	while (m_first != nullptr) {
		ListNode *temp = m_first;

		if (m_first->next)
			m_first->next->prev = m_first->prev;
		m_first = m_first->next;
		delete temp;
	}
}

void Linked_ListsApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;

	eraseLinkedList();
}

void List::add()    //Adds record of student//
{
	ListNode *p;
	p = new ListNode;

	p->value = displayed_Node;
	p->next = nullptr;

	if (m_first == nullptr) {
		m_first = p;
		m_first->next = nullptr;
		m_first->prev = nullptr;
		m_last = p;
	} else {
		m_last->next = p;
		p->prev = m_last;
		m_last = p;
	}
	currentptr = p;
}

void List::moveCurrentptr(bool right)
{
	if (currentptr == nullptr) return;
	// this is ok
	if (right) {
		if (currentptr->next == nullptr) return;
		currentptr = currentptr->next;
	} else {
		if (currentptr->prev == nullptr) return;
		currentptr = currentptr->prev;
	}

}

void Linked_ListsApp::changeMenu(bool up) 
{
	switch (menuItem) {
	case NAME:
		menuItem = up ? SECTION : DISCIPLINE;
		break;
	case DISCIPLINE:
		menuItem = up ? NAME : SECTION;
		break;
	case SECTION:
		menuItem = up ? DISCIPLINE : NAME;
		break;
	}
}

void Linked_ListsApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	//if (input->wasKeyPressed(aie::INPUT_KEY_A)) {
	//	if (input->isKeyDown(aie::INPUT_KEY_A))
	//		displayed_Node.name += 'A';
	//}

	for (auto iter = input->getPressedKeys().begin(); iter != input->getPressedKeys().end(); ++iter) {
		string *ep = (menuItem == NAME) ? &displayed_Node.name : &displayed_Node.discipline;
		if (menuItem != SECTION && (*iter >= 'a' && *iter <= 'z') || (*iter >= 'A' && *iter <= 'Z') || (*iter == ' ')) {
			// first character
			if ((*ep)[0] == '_')
				*ep = "";
			// enter
			if (input->wasKeyPressed(*iter)) {
				bool upper = input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) || *iter == ' ';
				*ep += *iter + (upper ? 0 : 32);
			}
		}

		if (menuItem == SECTION && (*iter >= '0' && *iter <= '9')) {
			// enter
			if (input->wasKeyPressed(*iter)) {
				displayed_Node.section = 10*displayed_Node.section + (*iter-'0');
			}
		}

		if (*iter == aie::INPUT_KEY_DELETE) {
			switch (menuItem) {
			case NAME:
				displayed_Node.name = '_';
				break;
			case DISCIPLINE:
				displayed_Node.discipline = '_';
				break;
			case SECTION:
				displayed_Node.section = 0;
				break;
			}
		}
		if (*iter == aie::INPUT_KEY_DOWN) {
			changeMenu(false);
		}
		if (*iter == aie::INPUT_KEY_UP) {
			changeMenu(true);
		}

		// functions for the system
		if (*iter == aie::INPUT_KEY_F1) {
			add();
			initializeNode();
		}

		// move
		if (*iter == aie::INPUT_KEY_LEFT) {
			moveCurrentptr(false);
		}
		if (*iter == aie::INPUT_KEY_RIGHT) {
			moveCurrentptr(true);
		}
	}
}

void Linked_ListsApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// how many links?
	int count = 0, upto = 1;
	bool stopCounting = false;
	ListNode *p = m_first;
	while (p != nullptr) {
		if (p == currentptr) stopCounting = true;
		if (!stopCounting) upto++;
		count++;
		p = p->next;
	}
	m_2dRenderer->drawText(m_font, "Count:", 700, 670);
	m_2dRenderer->drawText(m_font, std::to_string(count).c_str(), 850, 670);

	// draw your stuff here!
	// here is the displayed node
	m_2dRenderer->drawText(m_font, "Name:", 20, 670);
	m_2dRenderer->drawText(m_font, displayed_Node.name.c_str(), 250, 670);
	m_2dRenderer->setRenderColour(menuItem == DISCIPLINE ? 0xffffffff : 0xff0000ff);
	m_2dRenderer->drawText(m_font, "Discipline:", 20, 630);
	m_2dRenderer->drawText(m_font, displayed_Node.discipline.c_str(), 250, 630);
	m_2dRenderer->setRenderColour(menuItem == SECTION ? 0xffffffff : 0xff0000ff);
	m_2dRenderer->drawText(m_font, "Section:", 20, 590);
	m_2dRenderer->drawText(m_font, std::to_string(displayed_Node.section).c_str(), 250, 590);
	m_2dRenderer->setRenderColour(0xffffffff);

	if (currentptr) {
		m_2dRenderer->setRenderColour(0x00ffffff);
		m_2dRenderer->drawText(m_font, "Count:", 20, 320);
		string cc = std::to_string(upto).c_str();
		cc += " / ";
		cc+= std::to_string(count).c_str();
		m_2dRenderer->drawText(m_font, cc.c_str(), 250, 320);
		m_2dRenderer->drawText(m_font, "Name:", 20, 270);
		m_2dRenderer->drawText(m_font, currentptr->value.name.c_str(), 250, 270);
		m_2dRenderer->drawText(m_font, "Discipline:", 20, 230);
		m_2dRenderer->drawText(m_font, currentptr->value.discipline.c_str(), 250, 230);
		m_2dRenderer->drawText(m_font, "Section:", 20, 190);
		m_2dRenderer->drawText(m_font, std::to_string(currentptr->value.section).c_str(), 250, 190);
		m_2dRenderer->setRenderColour(0xffffffff);
	}

	m_2dRenderer->drawText(m_font, "Press Del = null line, F1 = Add, <- -> move node up/down change lines", 0, 50);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}


