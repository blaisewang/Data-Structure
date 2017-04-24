// circular array implementation of a queue
// derives from the ADT queue

#ifndef arrayQueue_
#define arrayQueue_

#include "queue.h"
#include "myExceptions.h"
#include <iostream>
#include <sstream>

using namespace std;

template<class T>
class arrayQueue : public queue<T> {
public:
    arrayQueue(int initialCapacity = 10);

    ~arrayQueue() {
        delete[] queue;
    }

    bool empty() const {
        return theFront == theBack;
    }

    int size() const {
        return (theBack - theFront + arrayLength) % arrayLength;
    }

    T &front() { // return front element
        if (theFront == theBack) {
            throw queueEmpty();
        }
        return queue[(theFront + 1) % arrayLength];
    }

    T &back() { // return theBack element
        if (theFront == theBack) {
            throw queueEmpty();
        }
        return queue[theBack];
    }

    void pop() { // remove theFront element
        if (theFront == theBack) {
            throw queueEmpty();
        }
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();  // destructor for T
    }

    void push(const T &theElement);

    arrayQueue<T> &merge(const arrayQueue<T> &A, const arrayQueue<T> &B);

private:
    int theFront;       // 1 counterclockwise from theFront element
    int theBack;        // position of theBack element
    int arrayLength;    // queue capacity
    T *queue;           // element array
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity) {           // Constructor.
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}

template<class T>
void arrayQueue<T>::push(const T &theElement) {           // Add theElement to queue.

    // increase array length if necessary
    if ((theBack + 1) % arrayLength == theFront) {           // double array length
        // allocate a new array
        T *newQueue = new T[2 * arrayLength];

        // copy elements into new array
        int start = (theFront + 1) % arrayLength;
        if (start < 2) {
            // no wrap around
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        } else {  // queue wraps around
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }

        // switch to newQueue and set theFront and theBack
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;   // queue size arrayLength - 1
        arrayLength *= 2;
        queue = newQueue;
    }

    // put theElement at the theBack of the queue
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

template<class T>
arrayQueue<T> &arrayQueue<T>::merge(const arrayQueue<T> &A, const arrayQueue<T> &B) {
    // Alternately combine from A and B to *this.
    // make sure we have enough space
    int sizeA = A.size(), sizeB = B.size(), size = sizeA + sizeB;
    if (size >= arrayLength) {
        cerr << "Not enough room for merge operation." << endl;
        exit(EXIT_FAILURE);
    }

    // move elements
    int thisIndex = 0,        // cursor for *this
            indexA = A.theFront,  // cursor for A
            indexB = B.theFront,  // cursor for B
            lesserLength;         // smaller of sizeA and sizeB
    bool isALonger = true;

    if (sizeA > sizeB) {
        lesserLength = sizeB;
    } else {
        lesserLength = sizeA;
        isALonger = false;
    }
    // alternately copy from A and B
    while (thisIndex < size) {
        if (thisIndex < 2 * lesserLength) {
            // first copy an element from A
            indexA = (indexA + 1) % A.arrayLength;
            queue[thisIndex++] = A.queue[indexA];
            // next copy one from B
            indexB = (indexB + 1) % B.arrayLength;
            queue[thisIndex++] = B.queue[indexB];
        } else {
            if (isALonger) {
                for (int i = sizeB; i < sizeA; i++) {
                    indexA = (indexA + 1) % A.arrayLength;
                    queue[thisIndex++] = A.queue[indexA];
                }
            } else {
                for (int i = sizeA; i < sizeB; i++) {
                    indexB = (indexB + 1) % B.arrayLength;
                    queue[thisIndex++] = B.queue[indexB];
                }
            }
        }
    }

    theFront = arrayLength - 1;
    theBack = size - 1;

    return *this;
}

#endif

