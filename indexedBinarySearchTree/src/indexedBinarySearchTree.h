#ifndef indexedBinarySearchTree_h
#define indexedBinarySearchTree_h

#include "indexedBSTree.h"
#include "linkedBinaryTree.h"
#include "triple.h"

using namespace std;

template<class K, class E>
class indexedBinarySearchTree: public indexedBSTree<K, E>,
		public linkedBinaryTree<triple<const K, E> >
{
public:
	// methods of dictionary
	bool empty() const
	{
		return this->treeSize == 0;
	}
	int size() const
	{
		return this->treeSize;
	}
	pair<const K, E>* find(const K& theKey) const;
	pair<const K, E>* get(int theIndex) const;
	void insert(const pair<const K, E>& thePair);
	void erase(const K& theKey);
	void indexDelete(int theIndex);
	void ascend()
	{
		this->inOrderOutput();
	}
};

template<class K, class E>
pair<const K, E>* indexedBinarySearchTree<K, E>::find(const K& theKey) const
{ // Return pointer to matching pair.
// Return NULL if no matching pair.
// p starts at the root and moves through
// the tree looking for an element with key theKey
	binaryTreeNode<triple<const K, E> > *p = this->root;
	while (p != NULL)
		// examine p->element
		if (theKey < p->element.thePair.first)
			p = p->leftChild;
		else if (theKey > p->element.thePair.first)
			p = p->rightChild;
		else
			// found matching pair
			return &p->element.thePair;

	// no matching pair
	return NULL;
}

template<class K, class E>
pair<const K, E>* indexedBinarySearchTree<K, E>::get(int theIndex) const
{
	binaryTreeNode<triple<const K, E> > *p = this->root;
	while (p)
	{
		if (theIndex < p->element.leftSize)
		{
			p = p->leftChild;
		}
		else if (theIndex > p->element.leftSize)
		{
			theIndex -= p->element.leftSize + 1;
			p = p->rightChild;
		}
		else
		{
			return &p->element.thePair;
		}
	}

	return NULL;
}

template<class K, class E>
void indexedBinarySearchTree<K, E>::insert(const pair<const K, E>& thePair)
{ // Insert thePair into the tree. Overwrite existing
// pair, if any, with same key.
// find place to insert
	bool isKeyExisted = false;
	if (find(thePair.first))
		isKeyExisted = true;

	binaryTreeNode<triple<const K, E> > *p = this->root, *pp = NULL;
	while (p)
	{   // examine p->element
		pp = p;
		// move p to a child
		if (thePair.first < p->element.thePair.first)
		{
			if (!isKeyExisted)
				p->element.leftSize++;
			p = p->leftChild;
		}
		else if (thePair.first > p->element.thePair.first)
		{
			p = p->rightChild;
		}
		else
		{   // replace old value
			p->element.thePair.second = thePair.second;
			p->element.leftSize = 0;
			return;
		}
	}

	triple<const K, E> theTriple(thePair);

// get a node for thePair and attach to pp
	binaryTreeNode<triple<const K, E> > *newNode = new binaryTreeNode<
			triple<const K, E> >(theTriple);
	if (this->root) // the tree is not empty
		if (thePair.first < pp->element.thePair.first)
		{
			pp->leftChild = newNode;
		}
		else
		{
			pp->rightChild = newNode;
		}
	else
		this->root = newNode; // insertion into empty tree
	this->treeSize++;
}

template<class K, class E>
void indexedBinarySearchTree<K, E>::erase(const K& theKey)
{ // Delete the pair, if any, whose key equals theKey.

// search for node with key theKey
	if (!find(theKey))
		return; // no pair with key theKey

	binaryTreeNode<triple<const K, E> > *p = this->root, *pp = NULL;
	while (p->element.thePair.first != theKey)
	{
		pp = p;
		if (theKey < p->element.thePair.first)
		{
			p->element.leftSize--;
			p = p->leftChild;
		}
		else
		{
			p = p->rightChild;
		}
	}

// restructure tree
// handle case when p has two children
	if (p->leftChild != NULL && p->rightChild != NULL)
	{   // two children
// convert to zero or one child case
// find largest element in left subtree of p
		binaryTreeNode<triple<const K, E> > *s = p->leftChild, *ps = p; // parent of s
		while (s->rightChild != NULL)
		{  // move to larger element
			ps = s;
			s = s->rightChild;
		}

		// move largest from s to p, can't do a simple move
		// p->element = s->element as key is const
		binaryTreeNode<triple<const K, E> > *q = new binaryTreeNode<
				triple<const K, E> >(s->element, p->leftChild, p->rightChild);
		if (pp)
			this->root = q;
		else if (p == pp->leftChild)
			pp->leftChild = q;
		else
			pp->rightChild = q;
		if (ps == p)
			pp = q;
		else
			pp = ps;
		delete p;
		p = s;
	}

// p has at most one child
// save child pointer in c
	binaryTreeNode<triple<const K, E> > *c;
	if (p->leftChild != NULL)
		c = p->leftChild;
	else
		c = p->rightChild;

// delete p
	if (p == this->root)
		this->root = c;
	else
	{   // is p left or right child of pp?
		if (p == pp->leftChild)
			pp->leftChild = c;
		else
			pp->rightChild = c;
	}
	this->treeSize--;
	delete p;
}

template<class K, class E>
void indexedBinarySearchTree<K, E>::indexDelete(int theIndex)
{
	binaryTreeNode<triple<const K, E> > *p = this->root;
	while (p)
	{
		if (theIndex < p->element.leftSize)
		{
			p = p->leftChild;
		}
		else if (theIndex > p->element.leftSize)
		{
			theIndex -= p->element.leftSize + 1;
			p = p->rightChild;
		}
		else
		{
			erase(p->element.thePair.first);
			return;
		}
	}

	return;
}

#endif
