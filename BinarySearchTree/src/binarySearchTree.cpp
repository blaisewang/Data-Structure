//============================================================================
// Name        : binarySearchTree.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "binarySearchTree.h"

using namespace std;

int *a;
int theCount = 0;

void visit(binaryTreeNode<pair<const int, char> > *thePair)
{
	cout << thePair->element.first << " ";
	a[theCount++] = thePair->element.first;
}

int main()
{
	binarySearchTree<int, char> searchTree1;
	searchTree1.insert(pair<int, char>(68, ' '));
	searchTree1.insert(pair<int, char>(75, ' '));
	searchTree1.insert(pair<int, char>(28, ' '));
	searchTree1.insert(pair<int, char>(11, ' '));
	searchTree1.insert(pair<int, char>(42, ' '));

	a = new int[searchTree1.size()];
	searchTree1.inOrder(visit);
	cout << endl;

	for (int i = 0; i < theCount; i++)
		cout << a[i] << " ";
	cout << endl;

	searchTree1.deleteMax();
	searchTree1.inOrderOutput();

	binarySearchTree<int, char> searchTree2;
	searchTree2.insert(pair<int, char>(1, 'a'));
	searchTree2.insert(pair<int, char>(6, 'c'));
	searchTree2.insert(pair<int, char>(4, 'b'));
	searchTree2.insert(pair<int, char>(8, 'd'));
	cout << "Tree size is " << searchTree2.size() << endl;
	cout << "Elements in ascending order are" << endl;
	searchTree2.ascend();

	pair<const int, char> *s = searchTree2.find(4);
	cout << "Search for 4 succeeds " << endl;
	cout << s->first << ' ' << s->second << endl;
	searchTree2.erase(4);
	cout << "4 deleted " << endl;
	cout << "Tree size is " << searchTree2.size() << endl;
	cout << "Elements in ascending order are" << endl;
	searchTree2.ascend();

	s = searchTree2.find(8);
	cout << "Search for 8 succeeds " << endl;
	cout << s->first << ' ' << s->second << endl;
	searchTree2.erase(8);
	cout << "8 deleted " << endl;
	cout << "Tree size is " << searchTree2.size() << endl;
	cout << "Elements in ascending order are" << endl;
	searchTree2.ascend();

	s = searchTree2.find(6);
	cout << "Search for 6 succeeds " << endl;
	cout << s->first << ' ' << s->second << endl;
	searchTree2.erase(6);
	cout << "6 deleted " << endl;
	cout << "Tree size is " << searchTree2.size() << endl;
	cout << "Elements in ascending order are" << endl;
	searchTree2.ascend();

	s = searchTree2.find(1);
	cout << "Search for 1 succeeds " << endl;
	cout << s->first << ' ' << s->second << endl;
	searchTree2.erase(1);
	cout << "1 deleted " << endl;
	cout << "Tree size is " << searchTree2.size() << endl;
	cout << "Elements in ascending order are" << endl;
	searchTree2.ascend();

	return 0;
}
