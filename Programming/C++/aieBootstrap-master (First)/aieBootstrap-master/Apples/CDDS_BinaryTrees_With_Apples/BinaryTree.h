/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

class TreeNode;

namespace aie {
	class Renderer2D;
}

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	bool isEmpty() const;
	void insert(int a_nValue);
	void remove(int a_nValue);
	TreeNode* find(int a_nValue);

	void printOrdered();
	void printUnordered();

	void draw(aie::Renderer2D* renderer, TreeNode* selected = nullptr);

private:
	//Find the node with the specified value.
	bool findNode(int a_nSearchValue, TreeNode** ppOutNode, TreeNode** ppOutParent);

	//Used to recurse through the nodes in value order and print their values.
	void printOrderedRecurse(TreeNode*);
	void printUnorderedRecurse(TreeNode*);

	void draw(aie::Renderer2D* renderer, TreeNode*, int x, int y, int horizontalSpacing, TreeNode* selected = nullptr);

	//The root node of the tree
	TreeNode* m_pRoot;
};

#endif //_BINARYTREE_H_