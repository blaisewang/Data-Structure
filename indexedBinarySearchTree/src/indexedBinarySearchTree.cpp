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

int main(void) {
    indexedBinarySearchTree<int, char> indexedBinarySearchTree;

    indexedBinarySearchTree.insert(pair<int, char>(20, 'd'));
    indexedBinarySearchTree.insert(pair<int, char>(15, 'b'));
    indexedBinarySearchTree.insert(pair<int, char>(25, 'e'));
    indexedBinarySearchTree.insert(pair<int, char>(12, 'a'));
    indexedBinarySearchTree.insert(pair<int, char>(18, 'c'));
    indexedBinarySearchTree.insert(pair<int, char>(30, 'f'));
    indexedBinarySearchTree.inOrderOutput();

    pair<const int, char> *p;
    p = indexedBinarySearchTree.get(2);
    if (p) {
        cout << p->first << " " << p->second << endl;
    }
    indexedBinarySearchTree.indexDelete(2);
    indexedBinarySearchTree.inOrderOutput();

    p = indexedBinarySearchTree.find(12);
    if (p) {
        cout << p->first << " " << p->second << endl;
    }
    indexedBinarySearchTree.erase(12);
    indexedBinarySearchTree.inOrderOutput();

    return 0;
}
