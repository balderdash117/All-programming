/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include <Renderer2D.h>
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while(m_pRoot)
	{
		remove(m_pRoot->getData());
	}
}

// Return whether the tree is empty
bool BinaryTree::isEmpty() const 
{ 
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::insert(int a_nValue)
{
	TreeNode* pParent = nullptr;
    
	// If this is a new tree then store the new root node.
	if(isEmpty())
	{
		m_pRoot = new TreeNode(a_nValue);
	}
	else
	{
		TreeNode* pCurrent = m_pRoot;
        
		// Find the Node's parent
		while(pCurrent)
		{
			pParent = pCurrent;
			if(a_nValue == pCurrent->getData())
				return;
			else if(a_nValue > pCurrent->getData())
				pCurrent = pCurrent->getRight();
			else 
				pCurrent = pCurrent->getLeft();
		}

		if(a_nValue > pParent->getData())
			pParent->setRight(new TreeNode(a_nValue));
		else
			pParent->setLeft(new TreeNode(a_nValue));
	}
}

TreeNode* BinaryTree::find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return findNode(a_nValue, &pCurrent, &pParent) ? pCurrent: nullptr;
}

bool BinaryTree::findNode(int a_nSearchValue, TreeNode** ppOutNode, TreeNode** ppOutParent)
{
	*ppOutNode = nullptr;
	*ppOutParent = nullptr;

	//Locate the element
	if(isEmpty())
	{
		return false;
	}
    
	TreeNode* pCurrent = m_pRoot;
	TreeNode* pParent = nullptr;
    
	while(pCurrent)
	{
		if(a_nSearchValue == pCurrent->getData())
		{
			*ppOutNode = pCurrent;
			*ppOutParent = pParent;
			return true;
		}
		else
		{
			pParent = pCurrent;

			if(a_nSearchValue > pCurrent->getData())
				pCurrent = pCurrent->getRight();
			else
				pCurrent = pCurrent->getLeft();
		}
	}

	return false;
}

void BinaryTree::remove(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	findNode(a_nValue, &pCurrent, &pParent);
	if(!pCurrent)
		return;

	if(pCurrent->hasRight())
	{
		//Find the minimum value node in the right subtree
		TreeNode* pMinNode = pCurrent->getRight();
		TreeNode* pMinParent = pCurrent;
		while(pMinNode->hasLeft())
		{
			pMinParent = pMinNode;
			pMinNode = pMinNode->getLeft();
		}

		pCurrent->setData( pMinNode->getData() );

		if(pMinParent->getLeft() == pMinNode)
			pMinParent->setLeft( pMinNode->getRight() );
		else
			pMinParent->setRight( pMinNode->getRight() );

		delete pMinNode;
	}
	else
	{
		if(pParent)
		{
			if(pParent->getLeft() == pCurrent)
				pParent->setLeft( pCurrent->getLeft() );
			else
				pParent->setRight( pCurrent->getLeft() );
		}
		else
			m_pRoot = pCurrent->getLeft();

		delete pCurrent;
	}
}

void BinaryTree::printOrdered()
{
	printOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::printOrderedRecurse(TreeNode* pNode)
{
    if(pNode)
    {
        if(pNode->hasLeft()) 
			printOrderedRecurse(pNode->getLeft());
        
		cout << " " << pNode->getData() << " ";
        
		if(pNode->hasRight())
			printOrderedRecurse(pNode->getRight());
    }
}

void BinaryTree::printUnordered()
{
    printUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::printUnorderedRecurse(TreeNode* pNode)
{
    if(pNode)
    {
        cout << " " << pNode->getData() << " ";

        if(pNode->hasLeft()) 
			printUnorderedRecurse(pNode->getLeft());

        if(pNode->hasRight()) 
			printUnorderedRecurse(pNode->getRight());
    }
}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, selected);
}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->hasLeft())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine((float)x, (float)y, (float)(x - horizontalSpacing), (float)(y - 80));
			draw(renderer, pNode->getLeft(), x - horizontalSpacing, y - 80, horizontalSpacing, selected);
		}

		if (pNode->hasRight())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine((float)x, (float)y, (float)(x + horizontalSpacing), (float)(y - 80));
			draw(renderer, pNode->getRight(), x + horizontalSpacing, y - 80, horizontalSpacing, selected);
		}

		pNode->draw(renderer, x, y, (selected == pNode));
	}
}
