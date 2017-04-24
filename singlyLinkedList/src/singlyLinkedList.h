// linked implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for chain included

#ifndef singlyLinkedList_h
#define singlyLinkedList_h

#include <iostream>
#include <sstream>
#include <string>
#include "linearList.h"
#include "chainNode.h"
#include "arrayList.h"
#include "myExceptions.h"

using namespace std;

template<class T>
class circularListWithHeader {
public:
    // constructor
    circularListWithHeader();

    ~circularListWithHeader();

    // some methods
    bool empty() const {
        return listSize == 0;
    }

    int size() const {
        return listSize;
    }

    T &get(int theIndex) const;

    int indexOf(const T &theElement) const;

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void output(ostream &out) const;

    void reverse();

    circularListWithHeader<T> &operator=(const circularListWithHeader<T> &x);

    // iterators to start and end of list
    class iterator;

    iterator begin() {
        return iterator(headerNode->next);
    }

    iterator end() {
        return iterator(headerNode);
    }

    // iterator for chain
    class iterator {
    public:
        // typedefs required by C++ for a forward iterator
        typedef forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        // constructor
        iterator(chainNode<T> *theNode = NULL) {
            node = theNode;
        }

        // dereferencing operators
        T &operator*() const {
            return node->element;
        }

        T *operator->() const {
            return &node->element;
        }

        // increment
        iterator &operator++()   // preIncrement
        {
            node = node->next;
            return *this;
        }

        iterator operator++(int) // postIncrement
        {
            iterator old = *this;
            node = node->next;
            return old;
        }

        // equality testing
        bool operator!=(const iterator right) const {
            return node != right.node;
        }

        bool operator==(const iterator right) const {
            return node == right.node;
        }

    protected:
        chainNode<T> *node;
    };  // end of iterator class

protected:
    void checkIndex(int theIndex) const;

    // throw illegalIndex if theIndex invalid
    chainNode<T> *headerNode;  // pointer to header node
    int listSize;              // number of elements in list
};

template<class T>
circularListWithHeader<T>::circularListWithHeader() { // Constructor.
    headerNode = new chainNode<T>();
    headerNode->next = headerNode;
    listSize = 0;
}

template<class T>
circularListWithHeader<T>::~circularListWithHeader() { // Destructor.
    chainNode<T> *nextNode = headerNode->next;
    while (nextNode != headerNode) { // delete firstNode
        headerNode->next = nextNode->next;
        delete nextNode;
        nextNode = headerNode->next;
    }
    delete headerNode;
    listSize = 0;
}

template<class T>
void circularListWithHeader<T>::checkIndex(int theIndex) const {
    // Verify that theIndex is between 0 and listSize - 1.
    if (theIndex < 0 || theIndex >= listSize) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
T &circularListWithHeader<T>::get(int theIndex) const {
    // Return element whose index is theIndex.
    // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

    // move to desired node
    chainNode<T> *currentNode = headerNode;
    for (int i = 0; i <= theIndex; i++) {
        currentNode = currentNode->next;
    }

    return currentNode->element;
}

template<class T>
int circularListWithHeader<T>::indexOf(const T &theElement) const {
    // Return index of first occurrence of theElement.
    // Return -1 if theElement not in list.

    // Put theElement in header node
    headerNode->element = theElement;

    // search the chain for theElement
    chainNode<T> *currentNode = headerNode->next;
    int index = 0;  // index of currentNode
    while (currentNode->element != theElement) {
        // move to next node
        currentNode = currentNode->next;
        index++;
    }

    // make sure we found matching element
    if (currentNode == headerNode) {
        return -1;
    } else {
        return index;
    }
}

template<class T>
void circularListWithHeader<T>::erase(int theIndex) {
    // Delete the element whose index is theIndex.
    // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

    // valid index, locate node with element to delete
    chainNode<T> *deleteNode;
    if (theIndex == 0) { // remove first node from chain
        deleteNode = headerNode->next;
        headerNode->next = headerNode->next->next;

    } else {
        chainNode<T> *p = headerNode->next;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }

        deleteNode = p->next;
        p->next = p->next->next; // remove deleteNode from chain
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void circularListWithHeader<T>::insert(int theIndex, const T &theElement) {
    // Insert theElement so that its index is theIndex.
    if (theIndex < 0 || theIndex > listSize) {  // invalid index
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    // find predecessor of new element
    chainNode<T> *p = headerNode;
    for (int i = 0; i < theIndex; i++) {
        p = p->next;
    }

    // insert after p
    p->next = new chainNode<T>(theElement, p->next);

    listSize++;
}

template<class T>
void circularListWithHeader<T>::output(ostream &out) const {
// Put the list into the stream out.
    for (chainNode<T> *currentNode = headerNode->next; currentNode != headerNode; currentNode = currentNode->next) {
        out << currentNode->element << "  ";
    }
}

// overload <<
template<class T>
ostream &operator<<(ostream &out, const circularListWithHeader<T> &x) {
    x.output(out);
    return out;
}

template<class T>
void circularListWithHeader<T>::reverse() {
    chainNode<T> *lastNode = headerNode->next,  // last node
            *currentNode = lastNode->next,    // current node
            *nextNode = NULL;      // next node

    while (currentNode != headerNode) {
        // change pointer direction
        nextNode = currentNode->next;
        currentNode->next = lastNode;

        // move to next node
        lastNode = currentNode;
        currentNode = nextNode;
    }
    headerNode->next->next = headerNode;
    headerNode->next = lastNode; // new first node
}

template<class T>
circularListWithHeader<T> &circularListWithHeader<T>::operator=(
        const circularListWithHeader<T> &x) {
    if (listSize != 0) { // clear linked list
        chainNode<T> *nextNode = headerNode->next;
        while (nextNode != headerNode) {
            headerNode->next = nextNode->next;
            delete nextNode;
            nextNode = headerNode->next;
        }
        listSize = 0;
    }

    int size = x.size();
    for (int i = 0; i < size; i++)
        insert(i, x.get(i));

    return *this;
}

//template<class T>
//chain<T>& chain<T>::fromList(arrayList<T>& theList)
//{ // Construct a chain from theList
//  first make *this empty
//	if (listSize != 0)
//	{
//		chainNode<T> *nextNode;
//		while (headerNode != NULL)
//		{ // delete firstNode
//			nextNode = headerNode->next;
//			delete headerNode;
//			headerNode = nextNode;
//		}
//	}
//
//	// copy elements from theList
//	int length = theList.size();
//	for (int i = 0; i < length; i++)
//		insert(i, theList.get(i));
//
//	return *this;
//}
//
//template<class T>
//chain<T>& chain<T>::toList(arrayList<T>& theList)
//{
//	if (theList.size() > 0)
//		while (theList.size())
//			theList.erase(theList.size() - 1);
//
//	chainNode<T> *p = headerNode;
//	for (int i = 0; i < listSize; i++)
//	{
//		theList.insert(i, p->element);
//		p = p->next;
//	}
//
//	return *this;
//}


#endif
