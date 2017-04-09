//============================================================================
// Name        : linkedBinaryTree.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "linkedBinaryTree.h"
#include "binaryTreeNode.h"

using namespace std;

int count = 0;

int main(void)
{
	linkedBinaryTree<int> a, b, c, x, y, z;
	y.makeTree(1, a, a);
	z.makeTree(2, a, a);
	x.makeTree(3, y, z);
	b = x;
	z.makeTree(5, a, a);
	y.makeTree(4, x, b);
	c = y;
	z.makeTree(4, y, c);
	c = z;
	y.makeTree(5, c, z);


//	b = y; 		//left subtree only
//	z.makeTree(5, a, a);
//	a.makeTree(6, z, y);	//both left and right
//	z.makeTree(7, y, c); 	//right subtree only
//	c.makeTree(8, y, y);	//root only and y tree is an empty tree
//
//	cout << "empty tree:" << endl;
//	y.preOrderOutput();
//	cout << y.leafNode() << endl;
//	y.invert();
//	y.preOrderOutput();
	y.removeLeftSubtree();

	if (y.isHBLT())
		cout << "1" << endl;
	else
		cout << "0" << endl;

//	y.makeTree(3, a, c);
//
//	y.isHBLT();

//	cout << "root only:" << endl;
//	c.preOrderOutput();
//	cout << c.leafNode() << endl;
//	c.invert();
//	c.preOrderOutput();
//
//	cout << "left subtree only:" << endl;
//	b.preOrderOutput();
//	cout << b.leafNode() << endl;
//	b.invert();
//	b.preOrderOutput();
//
//	cout << "right subtree only:" << endl;
//	z.preOrderOutput();
//	cout << z.leafNode() << endl;
//	z.invert();
//	z.preOrderOutput();
//
//	cout << "binary tree:" << endl;
//	a.preOrderOutput();
//	cout << a.leafNode() << endl;
//	a.invert();
//	a.preOrderOutput();

	return 0;
}
