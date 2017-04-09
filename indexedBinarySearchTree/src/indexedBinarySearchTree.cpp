//============================================================================
// Name        : indexedBinarySearchTree.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "indexedBinarySearchTree.h"

using namespace std;

int main(void)
{
	indexedBinarySearchTree<int, char> y;

	y.insert(pair<int, char>(20, 'd'));
	y.insert(pair<int, char>(15, 'b'));
	y.insert(pair<int, char>(25, 'e'));
	y.insert(pair<int, char>(12, 'a'));
	y.insert(pair<int, char>(18, 'c'));
	y.insert(pair<int, char>(30, 'f'));
	y.inOrderOutput();

	pair<const int, char> *p;
	p = y.get(2);
	if (p)
		cout << p->first << " " << p->second << endl;
	y.indexDelete(2);
	y.inOrderOutput();

	p = y.find(12);
	if (p)
		cout << p->first << " " << p->second << endl;
	y.erase(12);
	y.inOrderOutput();

	return 0;
}
